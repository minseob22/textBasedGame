// utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// 콘솔 커서를 이동시키는 함수
void move_cursor(int x, int y);

// 콘솔 화면을 지우는 함수
void clear_console();

void initialize_screen();

// 콘솔 커서를 숨기거나 표시하는 함수
void hide_cursor(bool hide);

// 콘솔 크기를 설정하는 함수
void set_console_size(int width, int height);

COORD get_console_size();

#endif // UTILITY_H