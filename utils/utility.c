#include "../include/utility.h"
#include <stdio.h>
#include <stdbool.h>

void move_cursor(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
    COORD position = {x, y};
    SetConsoleCursorPosition(console, position);
}

// 콘솔 화면 초기화 및 프레임 그리기 함수
void initialize_screen() {
    system("cls"); // 화면 초기화 (콘솔 창 지우기)

    // 콘솔 크기를 가져오기
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // 위쪽 가로선 출력
    move_cursor(0, 0);
    for (int i = 0; i < width; i++) {
        printf("-");
    }

    // 양쪽 세로선 출력
    for (int i = 1; i < height - 1; i++) {
        move_cursor(0, i);
        printf("|");
        move_cursor(width - 1, i);
        printf("|");
    }

    // 아래쪽 가로선 출력
    move_cursor(0, height - 1);
    for (int i = 0; i < width; i++) {
        printf("-");
    }
}

// 콘솔 크기를 가져오는 함수
COORD get_console_size() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    // 콘솔 정보 가져오기
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
        COORD size;
        size.X = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1; // 가로 크기
        size.Y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1; // 세로 크기
        return size;
    }

    // 기본 값 반환 (오류 발생 시)
    COORD defaultSize = {80, 25}; // 기본 콘솔 크기
    return defaultSize;
}



void clear_console() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = {0, 0};
    DWORD written, consoleSize;
    CONSOLE_SCREEN_BUFFER_INFO screen;

    GetConsoleScreenBufferInfo(console, &screen);
    consoleSize = screen.dwSize.X * screen.dwSize.Y;

    FillConsoleOutputCharacter(console, ' ', consoleSize, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void hide_cursor(bool hide) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = !hide; // TRUE면 보이고 FALSE면 숨김
    SetConsoleCursorInfo(console, &cursorInfo);
}

void set_console_size(int width, int height) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {width, height};
    SetConsoleScreenBufferSize(console, bufferSize);
}
