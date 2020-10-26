// ASCII game.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <Windows.h>
#include <math.h>
#include <WinUser.h>
#include <sstream>
#include "ConsoleBuffer.h"
#include "Player.h"
#include "KeyboardScheme.h"

void sayHi(CHAR_INFO* buffer, int x, int y);
const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 40;


#ifndef __NY_TIMER__
#define __NY_TIMER__

#include <windows.h>
#include "Wall.h"
#include "ASCII game.h"

class NYTimer
{
public:
    LARGE_INTEGER lastUpdateTime;
    LONGLONG freq;

    NYTimer()
    {
        QueryPerformanceCounter(&lastUpdateTime);
        LARGE_INTEGER li_freq;
        QueryPerformanceFrequency(&li_freq);
        freq = li_freq.QuadPart;
        freq /= 1000;
    }

    void start(void)
    {
        QueryPerformanceCounter(&lastUpdateTime);
    }

    float getElapsedSeconds(bool restart = false)
    {
        LARGE_INTEGER timeNow;
        QueryPerformanceCounter(&timeNow);
        LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;

        float elapsed = (float)((float)elapsedLong / (float)freq);
        elapsed /= 1000.0f;

        if (restart)
            lastUpdateTime = timeNow;

        return elapsed;
    }

    unsigned long getElapsedMs(bool restart = false)
    {
        LARGE_INTEGER timeNow;
        QueryPerformanceCounter(&timeNow);
        LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;

        unsigned long elapsed = (unsigned long)((float)elapsedLong / (float)freq);
        if (restart)
            lastUpdateTime = timeNow;
        return elapsed;
    }
};

#endif

void ResetPlayers(std::vector<Player>* playerVector) {
    std::vector<Player>& players = *playerVector;
    players[0].Reset();
    players[1].Reset();
}

bool DrawPlayers(std::vector<Player>* playerVector) {
    std::vector<Player> &players = *playerVector;
    players[0].Draw(players[0].sprites[0]->c[0]);
    std::pair<bool, bool> collisions = players[1].Draw(players[0].sprites[0]->c[0], true);

    if (collisions.first)
        players[1].Die();
    if (collisions.second)
        players[0].Die();

    if (collisions.first || collisions.second) {
        return true;
    }
    return false;
}

int main()
{
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    SetConsoleWindowInfo(hOutput, true, &rcRegion);
    SetConsoleScreenBufferSize(hOutput, dwBufferSize);

    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(hOutput, &cursor);
    cursor.bVisible = false;
    SetConsoleCursorInfo(hOutput, &cursor);

    CHAR_INFO initBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    ReadConsoleOutput(hOutput, (CHAR_INFO*)initBuffer, dwBufferSize,
        dwBufferCoord, &rcRegion);
    ConsoleBuffer buffer = ConsoleBuffer((CHAR_INFO*)initBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    

    std::vector<Wall> walls;
    Wall wall1 = Wall(buffer, 20, 20, 30, 4);
    walls.push_back(wall1);
    Wall wall2 = Wall(buffer, 80, 10, 30, 8);
    walls.push_back(wall2);
    Wall wall3 = Wall(buffer, 50, 30, 50, 4);
    walls.push_back(wall3);
    walls.size();

    //InputScheme* input = new KeyboardScheme();

    NYTimer timer = NYTimer();
    timer.start();
    unsigned long ms = 0;
    bool isRunning = true;
    unsigned long msperframe = 8;


    NYTimer timerReset = NYTimer(); //timer before reset
    bool isReseting = false; //countdown to reset is engaged
    unsigned long resetDelay = 2000;
    

    Sprite* sprites[12];
    std::vector<Sprite *> filesprites = Sprite::FromFile("run.txt");


    std::vector<Player> players;
    Player player = Player(buffer, sprites, 10, 5);
    players.push_back(player);
    InputScheme* input2 = new KeyboardScheme('Z', 'S', 'Q', 'D');
    Player player2 = Player(buffer, sprites, 40, 20, input2);
    players.push_back(player2);

    for (int i = 0; i < 12; i++)
    {
        sprites[i] = filesprites[i];
    }
    

    while(isRunning)
    {
        buffer.Clear();
        for (Wall& w : walls)
        {
            w.Draw();
        }

        
        players[0].flipped = players[0].x > players[1].x;
        players[1].flipped = !players[0].flipped;

        for (Player& p : players)
        {
            p.ProcessInput();
            p.ProcessState();
            p.ProcessNextPos();
            p.onGround = false;
            for (Wall& w : walls)
            {
                p.ProcessCollision(w);
            }
            p.UpdatePos();
        }

        // if one player died
        if (DrawPlayers(&players)) {
            //start the reset countdown
            isReseting = true;
            timerReset.start();
        }

        WriteConsoleOutput(hOutput, buffer.buffer, dwBufferSize,
            dwBufferCoord, &rcRegion);
        ms = timer.getElapsedMs(true);
        if (ms < msperframe)
        {
            Sleep(msperframe - ms);
        }

        if (isReseting) 
        {
            if (timerReset.getElapsedMs() > resetDelay) 
            {
                ResetPlayers(&players);
                isReseting = false;
            }
        }
    }



}



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
