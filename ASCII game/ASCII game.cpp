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
    


    
    CHAR_INFO frame1[4];
    frame1[0].Char.UnicodeChar = 'H';
    frame1[0].Attributes = 0x01;
    frame1[1].Char.UnicodeChar = 'i';
    frame1[1].Attributes = 0x01;
    frame1[2].Char.UnicodeChar = '!';
    frame1[2].Attributes = 0x01;
    frame1[3].Char.UnicodeChar = '!';
    frame1[3].Attributes = 0x01;
    Sprite* sprite1 = new Sprite(frame1, 2, 2);
    CHAR_INFO frame2[4];
    frame2[0].Char.UnicodeChar = 'H';
    frame2[0].Attributes = 0x02;
    frame2[1].Char.UnicodeChar = 'i';
    frame2[1].Attributes = 0x02;
    frame2[2].Char.UnicodeChar = '!';
    frame2[2].Attributes = 0x02;
    frame2[3].Char.UnicodeChar = '!';
    frame2[3].Attributes = 0x02;
    Sprite* sprite2 = new Sprite(frame2, 2, 2);
    CHAR_INFO frame3[4];
    frame3[0].Char.UnicodeChar = 'H';
    frame3[0].Attributes = 0x03;
    frame3[1].Char.UnicodeChar = 'i';
    frame3[1].Attributes = 0x03;
    frame3[2].Char.UnicodeChar = '!';
    frame3[2].Attributes = 0x03;
    frame3[3].Char.UnicodeChar = '!';
    frame3[3].Attributes = 0x03;
    Sprite* sprite3 = new Sprite(frame3, 2, 2);
    CHAR_INFO frame4[4];
    frame4[0].Char.UnicodeChar = 'H';
    frame4[0].Attributes = 0x04;
    frame4[1].Char.UnicodeChar = 'i';
    frame4[1].Attributes = 0x04;
    frame4[2].Char.UnicodeChar = '!';
    frame4[2].Attributes = 0x04;
    frame4[3].Char.UnicodeChar = '!';
    frame4[3].Attributes = 0x04;
    Sprite* sprite4 = new Sprite(frame4, 2, 2);
    CHAR_INFO frame5[4];
    frame5[0].Char.UnicodeChar = 'H';
    frame5[0].Attributes = 0x05;
    frame5[1].Char.UnicodeChar = 'i';
    frame5[1].Attributes = 0x05;
    frame5[2].Char.UnicodeChar = '!';
    frame5[2].Attributes = 0x05;
    frame5[3].Char.UnicodeChar = '!';
    frame5[3].Attributes = 0x05;
    Sprite* sprite5 = new Sprite(frame5, 2, 2);
    CHAR_INFO frame6[4];
    frame6[0].Char.UnicodeChar = 'H';
    frame6[0].Attributes = 0x06;
    frame6[1].Char.UnicodeChar = 'i';
    frame6[1].Attributes = 0x06;
    frame6[2].Char.UnicodeChar = '!';
    frame6[2].Attributes = 0x06;
    frame6[3].Char.UnicodeChar = '!';
    frame6[3].Attributes = 0x06;
    Sprite* sprite6 = new Sprite(frame6, 2, 2);
    CHAR_INFO frame7[4];
    frame7[0].Char.UnicodeChar = 'H';
    frame7[0].Attributes = 0x07;
    frame7[1].Char.UnicodeChar = 'i';
    frame7[1].Attributes = 0x07;
    frame7[2].Char.UnicodeChar = '!';
    frame7[2].Attributes = 0x07;
    frame7[3].Char.UnicodeChar = '!';
    frame7[3].Attributes = 0x07;
    Sprite* sprite7 = new Sprite(frame7, 2, 2);

    Sprite* sprites[7];
    sprites[0] = sprite1;
    sprites[1] = sprite2;
    sprites[2] = sprite3;
    sprites[3] = sprite4;
    sprites[4] = sprite5;
    sprites[5] = sprite6;
    sprites[6] = sprite7;

    std::vector<Player> players;
    Player player = Player(buffer, sprites, 10, 5);
    players.push_back(player);
    InputScheme *input2 = new KeyboardScheme('Z', 'S', 'Q', 'D');
    Player player2 = Player(buffer, sprites, 40, 20, input2);
    players.push_back(player2);


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
    
    std::vector<Sprite *> filesprites = Sprite::FromFile("run.txt");

    for (int i = 0; i < 9; i++)
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
            p.Draw(p.sprites[0]->c[0]);
        }

        WriteConsoleOutput(hOutput, buffer.buffer, dwBufferSize,
            dwBufferCoord, &rcRegion);
        ms = timer.getElapsedMs(true);
        if (ms < msperframe)
        {
            Sleep(msperframe - ms);
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
