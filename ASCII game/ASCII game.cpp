// ASCII game.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <WinUser.h>
#include "ConsoleBuffer.h"

void sayHi(CHAR_INFO* buffer, int x, int y);
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 40;

int main()
{
    HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    

    COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    COORD dwBufferCoord = { 0, 0 };
    SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(hOutput, &cursor);
    cursor.bVisible = false;
    SetConsoleCursorInfo(hOutput, &cursor);

    CHAR_INFO initBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    ReadConsoleOutput(hOutput, (CHAR_INFO*)initBuffer, dwBufferSize,
        dwBufferCoord, &rcRegion);
    ConsoleBuffer buffer = ConsoleBuffer((CHAR_INFO*)initBuffer, SCREEN_HEIGHT, SCREEN_WIDTH);
    

    float x = 0.0;
    float y = 0.0;
    float radius = 7.0;
    float cx = 10.0;
    float cy = 10.0;
    float period = 100.0;

    int frame = 0;
    CHAR_INFO sprite[3];
    sprite[0].Char.UnicodeChar = 'H';
    sprite[0].Attributes = 0x0E;
    sprite[1].Char.UnicodeChar = 'i';
    sprite[1].Attributes = 0x0B;
    sprite[2].Char.UnicodeChar = '!';
    sprite[2].Attributes = 0x0A;


    bool isRunning = true;
    while(isRunning)
    {

        
        buffer.Clear();

        if (GetKeyState(VK_RIGHT))
        {
            x += 0.01;
        }
        /*
        x = cx + sin(frame / period) * radius;
        y = cy + cos(frame / period) * radius;*/

        //sayHi((CHAR_INFO*)buffer, x, y);
        
        buffer.Draw(x, y, 3, 1, sprite);

        WriteConsoleOutput(hOutput, buffer.buffer, dwBufferSize,
            dwBufferCoord, &rcRegion);

        frame++;
    }
}

void sayHi(CHAR_INFO* buffer, int x, int y)
{
    int offset = x + y * SCREEN_WIDTH;
    buffer[offset].Char.AsciiChar = 'H';
    buffer[offset].Attributes = 0x0E;
    offset++;
    buffer[offset].Char.AsciiChar = 'i';
    buffer[offset].Attributes = 0x0B;
    offset++;
    buffer[offset].Char.AsciiChar = '!';
    buffer[offset].Attributes = 0x0A;
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
