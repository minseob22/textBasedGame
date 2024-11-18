#ifndef DUNGEON_H
#define DUNGEON_H

#include "attacker.h"
#include "character.h"
#include "enemy.h"
#include "../include/goblin.h"
#include "../include/orc.h"
#include "../include/mimic.h"

#define N 4
#define M 4
#define MAX_MAPS 3  // 여러 맵을 지원하는 최대 맵 수

// 이벤트 타입 정의
#define EVENT_NOWAY 0
#define EVENT_PATH 1
#define EVENT_NONE 2
#define EVENT_ENEMY 3
#define EVENT_CHEST 4

typedef struct {
    int x; // 플레이어의 x 좌표
    int y; // 플레이어의 y 좌표
} Position;

typedef struct {
    int map[N][M];           // 맵 배열
    Position start;          // 시작 위치
    Position exit;           // 출구 위치
    Enemy *enemies[N][M];    // 각 위치에서의 적 배열
    int enemy_counts[N][M];  // 각 위치의 적 수
} Map;

typedef struct {
    Position playerPos;       // 플레이어의 현재 위치
    Map currentMap;           // 현재 던전의 맵 정보
} Dungeon;

// 여러 맵 초기화 및 선택을 위한 함수 선언
void initialize_dungeon(Dungeon *dungeon);
void initialize_all_maps();
void load_map(Dungeon *dungeon, Map *map);
void start_new_dungeon(Dungeon *dungeon, int map_index);
void initialize_map_1(Map *map);
void initialize_map_2(Map *map);

void move_party(Dungeon *dungeon, char direction, Character characters[], int char_count);
void printMap(Dungeon *dungeon);
void movePlayer(Dungeon *dungeon, int dx, int dy, Character characters[], int char_count);
int handle_event(Dungeon *dungeon, Character characters[], int char_count);

#endif // DUNGEON_H
