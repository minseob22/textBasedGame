#ifndef DUNGEON_H
#define DUNGEON_H

#include "attacker.h"

#define N 4
#define M 4

// 이벤트 타입 정의
#define EVENT_NONE 0
#define EVENT_ENEMY 1
#define EVENT_CHEST 2

typedef struct {
    int map[N][M];
    int x; // 플레이어의 x 좌표
    int y; // 플레이어의 y 좌표
} Dungeon;

void initialize_dungeon(Dungeon *dungeon);
void printMap(Dungeon *dungeon);
void move_party(Dungeon *dungeon, char direction);
void movePlayer(Dungeon *dungeon, int dx, int dy);
void handle_event(Dungeon *dungeon);

#endif