#include <stdio.h>
#include "../include/dungeon.h"
#include "../include/battleScene.h"  // 전투 관련 함수 포함

#define N 4
#define M 4

typedef struct {
    int x;
    int y;
} Position;

Position playerPos = {0, 0};  // 시작 위치
Position exitPos = {3, 3};    // 출구 위치

void initialize_dungeon(Dungeon *dungeon) {
    dungeon->x = 0;
    dungeon->y = 0;

    // 모든 위치를 EVENT_NOWAY로 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dungeon->map[i][j] = EVENT_NOWAY;
        }
    }

    // 이동 가능한 경로 설정
    int tempMap[N][M] = {
        {1, 1, 1, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (tempMap[i][j] == 1) {
                dungeon->map[i][j] = EVENT_PATH;
            }
        }
    }

    // 이벤트 위치 지정
    dungeon->map[1][1] = EVENT_ENEMY;
    dungeon->map[2][2] = EVENT_CHEST;
}

void move_party(Dungeon *dungeon, char direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'N': case 'n': dy = -1; break;
        case 'S': case 's': dy = 1; break;
        case 'E': case 'e': dx = 1; break;
        case 'W': case 'w': dx = -1; break;
        default: 
            printf("Invalid direction.\n");
            return;
    }
    movePlayer(dungeon, dx, dy);
    printf("Current position: (%d, %d)\n", dungeon->x, dungeon->y);
    printMap(dungeon);
}

void printMap(Dungeon *dungeon) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == dungeon->y && j == dungeon->x)
                printf("[P] ");
            else if (i == exitPos.y && j == exitPos.x)
                printf("[E] ");
            else if (dungeon->map[i][j] == EVENT_ENEMY)
                printf("[EN]");
            else if (dungeon->map[i][j] == EVENT_CHEST)
                printf("[CH]");
            else if (dungeon->map[i][j] == EVENT_NOWAY)
                printf("[-] ");
            else if (dungeon->map[i][j] == EVENT_PATH)
                printf("[ ] ");
        }
        printf("\n");
    }
}

void movePlayer(Dungeon *dungeon, int dx, int dy) {
    int newX = dungeon->x + dx;
    int newY = dungeon->y + dy;

    if (newX >= 0 && newX < N && newY >= 0 && newY < M && dungeon->map[newY][newX] != EVENT_NOWAY) {
        dungeon->x = newX;
        dungeon->y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);

        if (newX == exitPos.x && newY == exitPos.y) {
            printf("Exit found! Dungeon cleared!\n");
        } else if (!handle_event(dungeon)) {
            printf("There is nothing here.\n");
        }
    } else {
        printf("Cannot move to (%d, %d)\n", newX, newY);
    }
}

int handle_event(Dungeon *dungeon) {
    int event = dungeon->map[dungeon->y][dungeon->x];
    switch (event) {
        case EVENT_NONE:
            return 0;
        case EVENT_ENEMY:
            printf("You encountered an enemy! Starting battle.\n");
            Character characters[4];
            Enemy enemies[4];
            initialize_battle_scene(characters, 4, enemies, 4); // 초기 전투 설정
            start_battle(characters, 4, enemies, 4);            // 전투 시작
            break;
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            break;
    }

    if (event != EVENT_NONE) {
        dungeon->map[dungeon->y][dungeon->x] = EVENT_PATH;
    }
    return event != EVENT_NONE;
}
