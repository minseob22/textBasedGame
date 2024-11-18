#include <stdio.h>
#include <stdlib.h>
#include "../include/dungeon.h"
#include "../include/battleScene.h"
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"

#define N 4
#define M 4

// 여러 맵을 저장할 배열
Map all_maps[MAX_MAPS];

// 전체 맵들을 초기화
void initialize_all_maps() {
    initialize_map_1(&all_maps[0]);
    initialize_map_2(&all_maps[1]);
    // 추가 맵이 있다면 여기서 초기화
}

// 특정 맵을 로드하여 던전에 적용
void load_map(Dungeon *dungeon, Map *map) {
    dungeon->playerPos = map->start;  // 시작 위치 로드
    dungeon->currentMap = *map;       // 현재 맵 정보 로드
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dungeon->currentMap.map[i][j] = map->map[i][j];
            dungeon->currentMap.enemies[i][j] = map->enemies[i][j];
        }
    }
}

// 던전 시작 시 맵 로드
void start_new_dungeon(Dungeon *dungeon, int map_index) {
    if (map_index >= 0 && map_index < MAX_MAPS) {
        load_map(dungeon, &all_maps[map_index]);
    } else {
        printf("Invalid map index.\n");
    }
}

// 첫 번째 맵 초기화
void initialize_map_1(Map *map) {
    map->start = (Position){0, 0};
    map->exit = (Position){3, 3};

    int tempMap[N][M] = {
        {1, 1, 1, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map->map[i][j] = (tempMap[i][j] == 1) ? EVENT_PATH : EVENT_NOWAY;
        }
    }

    map->enemy_counts[1][1] = 4; // 4명의 적
    map->enemies[1][1] = malloc(sizeof(Enemy) * 4);
    initialize_goblin(&map->enemies[1][1][0], 0); // 첫 번째 고블린
    initialize_goblin(&map->enemies[1][1][1], 1); // 두 번째 고블린
    initialize_orc(&map->enemies[1][1][2], 0);    // 첫 번째 오크
    initialize_orc(&map->enemies[1][1][3], 1);    // 두 번째 오크
}

// 두 번째 맵 초기화
void initialize_map_2(Map *map) {
    map->start = (Position){0, 0};
    map->exit = (Position){3, 3};

    int tempMap[N][M] = {
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 1},
        {1, 1, 0, 1}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map->map[i][j] = (tempMap[i][j] == 1) ? EVENT_PATH : EVENT_NOWAY;
            map->enemies[i][j] = NULL; // 초기화
            map->enemy_counts[i][j] = 0;
        }
    }

    // (1,2)에 적 2명 배치
    map->map[1][2] = EVENT_ENEMY;
    map->enemy_counts[1][2] = 2;
    map->enemies[1][2] = malloc(sizeof(Enemy) * 2);
    initialize_orc(&map->enemies[1][2][0], 0); // 첫 번째 오크
    initialize_orc(&map->enemies[1][2][1], 1); // 두 번째 오크
}

// 플레이어 이동
void move_party(Dungeon *dungeon, char direction, Character characters[], int char_count) {
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
    movePlayer(dungeon, dx, dy, characters, char_count);
    printf("Current position: (%d, %d)\n", dungeon->playerPos.x, dungeon->playerPos.y);
    printMap(dungeon);
}

// 맵을 출력
void printMap(Dungeon *dungeon) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == dungeon->playerPos.y && j == dungeon->playerPos.x)
                printf("[P] ");
            else if (i == dungeon->currentMap.exit.y && j == dungeon->currentMap.exit.x)
                printf("[E] ");
            else if (dungeon->currentMap.map[i][j] == EVENT_ENEMY)
                printf("[EN]");
            else if (dungeon->currentMap.map[i][j] == EVENT_CHEST)
                printf("[CH]");
            else if (dungeon->currentMap.map[i][j] == EVENT_NOWAY)
                printf("[-] ");
            else if (dungeon->currentMap.map[i][j] == EVENT_PATH)
                printf("[ ] ");
        }
        printf("\n");
    }
}

// 플레이어 위치 이동
void movePlayer(Dungeon *dungeon, int dx, int dy, Character characters[], int char_count) {
    int newX = dungeon->playerPos.x + dx;
    int newY = dungeon->playerPos.y + dy;

    if (newX >= 0 && newX < N && newY >= 0 && newY < M && dungeon->currentMap.map[newY][newX] != EVENT_NOWAY) {
        dungeon->playerPos.x = newX;
        dungeon->playerPos.y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);

        if (newX == dungeon->currentMap.exit.x && newY == dungeon->currentMap.exit.y) {
            printf("Exit found! Dungeon cleared!\n");
        } else if (!handle_event(dungeon, characters, char_count)) {
            printf("There is nothing here.\n");
        }
    } else {
        printf("Cannot move to (%d, %d)\n", newX, newY);
    }
}

// 이벤트 처리
int handle_event(Dungeon *dungeon, Character characters[], int char_count) {
    int x = dungeon->playerPos.x;
    int y = dungeon->playerPos.y;
    int event = dungeon->currentMap.map[y][x];
    
    switch (event) {
        case EVENT_NONE:
            return 0;
        case EVENT_ENEMY: {
            printf("You encountered enemies! Starting battle with all enemies at this location.\n");

            int enemy_count = dungeon->currentMap.enemy_counts[y][x];
            Enemy *encounter_enemies = dungeon->currentMap.enemies[y][x];

            initialize_battle_scene(characters, char_count, encounter_enemies, enemy_count);
            start_battle(characters, char_count, encounter_enemies, enemy_count);
            break;
        }
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            break;
    }

    if (event != EVENT_NONE) {
        dungeon->currentMap.map[y][x] = EVENT_PATH;
    }
    return event != EVENT_NONE;
}

