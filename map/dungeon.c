#include <stdio.h>
#include "../include/dungeon.h"
#include "../include/battleScene.h"
#define N 4
#define M 4

int map[N][M] = {
    {1, 1, 1, 1},
    {0, 1, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 1}
};

typedef struct {
    int x;
    int y;
} Position;

Position playerPos = {0, 0};  // 시작 위치
Position exitPos = {3, 3};    // 출구 위치

void initialize_dungeon(Dungeon *dungeon) {
    dungeon->x = 0;
    dungeon->y = 0;

    // 초기 이벤트 설정
    dungeon->map[1][1] = EVENT_ENEMY;
    dungeon->map[2][2] = EVENT_CHEST;

    // 이동 가능 경로 설정 (1: 이동 가능, 0: 이동 불가)
    int tempMap[N][M] = {
        {1, 1, 1, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dungeon->map[i][j] = tempMap[i][j] == 1 ? dungeon->map[i][j] : EVENT_NONE;
        }
    }
}

void move_party(Dungeon *dungeon, char direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'N': dy = -1; break;
        case 'S': dy = 1; break;
        case 'E': dx = 1; break;
        case 'W': dx = -1; break;
        default: 
            printf("Invalid direction.\n");
            return;
    }
    movePlayer(dungeon, dx, dy);
}



void printMap(Dungeon *dungeon) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == dungeon->y && j == dungeon->x) // 플레이어 위치
                printf("[P] ");
            else if (i == exitPos.y && j == exitPos.x) // 출구 위치
                printf("[E] ");
            else if (map[i][j] == 1)  // 이동 가능한 위치
                printf("[ ] ");
            else  // 이동 불가능한 위치
                printf("[-] ");
        }
        printf("\n");
    }
}

void movePlayer(Dungeon *dungeon, int dx, int dy) {
    int newX = dungeon->x + dx;
    int newY = dungeon->y + dy;

    if (newX >= 0 && newX < N && newY >= 0 && newY < M && dungeon->map[newY][newX] != 0) {
        dungeon->x = newX;
        dungeon->y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);

        if (newX == exitPos.x && newY == exitPos.y) {
            printf("Exit found! Dungeon cleared!\n");
        } else {
            handle_event(dungeon);
        }
    } else {
        printf("Cannot move to (%d, %d)\n", newX, newY);
    }
}

void handle_event(Dungeon *dungeon) {
    int event = dungeon->map[dungeon->y][dungeon->x];
    switch (event) {
        case EVENT_NONE:
            printf("There is nothing here.\n");
            break;
        case EVENT_ENEMY:
            printf("You encountered an enemy! Starting battle.\n");
            // 전투 시작 코드 추가
            break;
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            // 보물 획득 코드 추가
            break;
    }
}