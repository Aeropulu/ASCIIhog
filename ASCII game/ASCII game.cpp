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

const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 40;


#ifndef __NY_TIMER__
#define __NY_TIMER__

#include <windows.h>
#include "Wall.h"

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
    

    std::vector<Wall*> walls;
    Wall* wall1 = new Wall(buffer, 60, 35, 110, 4);
    walls.push_back(wall1);
    Wall* wall2 = new Wall(buffer, 10, 24, 30, 4);
    walls.push_back(wall2);
    Wall* wall3 = new Wall(buffer, 115, 24, 40, 4);
    walls.push_back(wall3);
    Wall* wall4 = new Wall(buffer, 60, 15, 40, 4);
    walls.push_back(wall4);

    //InputScheme* input = new KeyboardScheme();

    NYTimer timer = NYTimer();
    timer.start();
    unsigned long ms = 0;
    bool isRunning = true;
    unsigned long msperframe = 8;


    NYTimer timerReset = NYTimer(); //timer before reset
    bool isReseting = false; //countdown to reset is engaged
    unsigned long resetDelay = 2000;
    

    WORD color = FOREGROUND_RED;
    std::map<char, WORD>& redscheme = *new std::map<char, WORD>{ {'%', color},{'@', color}, {'#', color | FOREGROUND_INTENSITY}, {'&', color | FOREGROUND_INTENSITY}, {',', FOREGROUND_INTENSITY} };
    color = FOREGROUND_BLUE;
    std::map<char, WORD>& bluescheme = *new std::map<char, WORD>{ {'%', color},{'@', color}, {'#', color | FOREGROUND_INTENSITY}, {'&', color | FOREGROUND_INTENSITY}, {',', FOREGROUND_INTENSITY} };
    Sprite* sprites_red[12];
    Sprite* sprites_blue[12];
    std::vector<Sprite *> filesprites_red = Sprite::FromFile("run.txt", redscheme);
    std::vector<Sprite*> filesprites_blue = Sprite::FromFile("run.txt", bluescheme);

    for (int i = 0; i < 12; i++)
    {
        sprites_red[i] = filesprites_red[i];
        sprites_blue[i] = filesprites_blue[i];
    }

    std::vector<Player> players;
    Player player = Player(buffer, sprites_red, 10, 5);
    players.push_back(player);
    InputScheme* input2 = new KeyboardScheme('Z', 'S', 'Q', 'D');
    Player player2 = Player(buffer, sprites_blue, 110, 10, input2);
    players.push_back(player2);

    
    

    while(isRunning)
    {
        buffer.Clear();
        for (Wall *w : walls)
        {
            (*w).Draw();
        }

        
        players[0].flipped = players[0].x > players[1].x;
        players[1].flipped = !players[0].flipped;

        for (Player& p : players)
        {
            p.ProcessInput();
            p.ProcessState();
            p.ProcessNextPos();
            p.onGround = false;
            for (Wall* w : walls)
            {
                p.ProcessCollision(*w);
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

    //free the memory, not sure how to make it do it 
    for (Wall* w : walls)
    {
        delete (w);
    }

    for (Sprite* s : sprites_red)
    {
        free(s->c);
    }
    for (Sprite* s : sprites_red)
    {
        delete (s);
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
