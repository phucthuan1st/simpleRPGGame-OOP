#include "Game.h"

class Screen {
private:
    HANDLE handler;
    SMALL_RECT *windowSize;
    HWND hWnd;
    HMENU hMenu;
public:
    //init screen
    Screen() {
        SetConsoleTitle(L"Rouge Adventure");
        handler = GetStdHandle(STD_OUTPUT_HANDLE);
        hWnd = GetConsoleWindow();
        hMenu = GetSystemMenu(hWnd, false);
        
        //init screen in full_screen mode
        COORD screen_buffer_info = GetLargestConsoleWindowSize(handler);
        windowSize->Left = 0;
        windowSize->Top = 0;
        windowSize->Right = screen_buffer_info.X;
        windowSize->Bottom = screen_buffer_info.Y;

        SetConsoleWindowInfo(handler, 1, windowSize);
        SetConsoleOutputCP(65001);
        
        //disable auto resize
        SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
        
        //disable resize buttons
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);

        //disable cursor 
        showCursor(false);

        //disable select
        SetConsoleMode(handler, ~ENABLE_QUICK_EDIT_MODE);
    }

    void gotoXY(SHORT x, SHORT y) {
        COORD rect = {x, y};
        SetConsoleCursorPosition(handler, rect);
    }

    void showCursor(bool Visibility) {
        CONSOLE_CURSOR_INFO *cursor;
        cursor->bVisible = Visibility;
        cursor->dwSize = 10;
        
        SetConsoleCursorInfo(handler, cursor);
    }

    //resize windows
    void SetWindowSize(SHORT width, SHORT height) {

        SMALL_RECT *windowSize;
        windowSize->Top = 0;
        windowSize->Left = 0;
        windowSize->Right = width;
        windowSize->Bottom = height;
    
        SetConsoleWindowInfo(handler, 1, windowSize);
    }

    void setTextColor(int backgroundColor, int foregroundColor) {
        int color_code = backgroundColor * 16 + foregroundColor;
        SetConsoleTextAttribute(handler, color_code);
    }

    void drawText(int x, int y, const char* text, int backgroundColor, int foregroundColor) {
        setTextColor(backgroundColor, foregroundColor);
        gotoXY(x,y);
        std::cout << text;
    }    

    void DrawBackground() {
        SHORT baseX = windowSize->Left + 5, baseY = windowSize->Top + 5;

        //top line
        for (DWORD i = baseX; i < windowSize->Right - 4; i++) 
            drawText(i, baseY, "=", Black, White);
        
        //bottom line
        for (DWORD i = baseX; i < windowSize->Right - 4; i++) 
		    drawText(i, windowSize->Bottom - 2, "=", Black, White);

        //left line
        for (DWORD j = baseY + 1; j < windowSize->Bottom - 2; j++) 
		    drawText(baseX, j, "||", Black, White);
	
        //right line
        for (DWORD j = baseY + 1; j < windowSize->Bottom - 2; j++) 
		    drawText(windowSize->Right - 6, j, "||", Black, White);

    }

};
