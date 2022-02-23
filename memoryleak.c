#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MAP_X_MAX 49
#define MAP_Y_MAX 17
 
char mapData[MAP_X_MAX * MAP_Y_MAX];
 
void InitializeConsole() 
{
    
    system("title Memory Leak");
    system("mode con:cols=49 lines=17");
    
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
    
    COORD Pos = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
 
void InitializeMap() 
{
    
    for (int i = 0; i < MAP_X_MAX * MAP_Y_MAX; i++)
        mapData[i] = ' ';
}
 
int main(int argc, char** argv) 
{
    
    InitializeConsole();
    InitializeMap();
 
    int characterX = MAP_X_MAX / 2 + 1;
    int characterY = MAP_Y_MAX / 2 + 1;
    
    while(1) 
    {
        mapData[(characterY - 1) * MAP_X_MAX + characterX - 1] = ' ';
        
        if(GetAsyncKeyState(0x41) != 0 && characterX > 1)
            characterX -= 1;
            
        if(GetAsyncKeyState(0x44) != 0 && characterX < MAP_X_MAX)
            characterX += 1;
            
        if(GetAsyncKeyState(0x57) != 0 && characterY > 1)
            characterY -= 1;
            
        if(GetAsyncKeyState(0x53) != 0 && characterY < MAP_Y_MAX)
            characterY += 1;
            
        mapData[(characterY - 1) * MAP_X_MAX + characterX - 1] = '@';
            
        printf("%s", mapData);
        Sleep(30);
    }
}
