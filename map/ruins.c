#include <stdio.h>
#include <stdlib.h>
#include "../include/dungeon.h"
#include "../include/battleScene.h"
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"

// 이벤트 상수 정의
#define EVENT_NOWAY 0
#define EVENT_PATH 1
#define EVENT_ENEMY 2
#define EVENT_CHEST 3
#define EVENT_PUZZLE 4
#define EVENT_RELIC 5

typedef struct Position {
    int x, y;
} Position;

typedef struct Map {
    int **map;
    Enemy ***enemies;
    int **enemy_counts;
    int rows, cols;
    Position start, exit;
} Map;

typedef struct Dungeon {
    Map currentMap;
    Position playerPos;
} Dungeon;

Map ruins_map;

// 유적 맵 초기화
void initialize_ruins_map(Map *map) {
    map->rows = 4;  // 맵 크기: 4x4
    map->cols = 4;

    map->map = (int **)malloc(map->rows * sizeof(int *));
    map->enemies = (Enemy ***)malloc(map->rows * sizeof(Enemy **));
    map->enemy_counts = (int **)malloc(map->rows * sizeof(int *));

    for (int i = 0; i < map->rows; i++) {
        map->map[i] = (int *)malloc(map->cols * sizeof(int));
        map->enemies[i] = (Enemy **)malloc(map->cols * sizeof(Enemy *));
        map->enemy_counts[i] = (int *)malloc(map->cols * sizeof(int));

        for (int j = 0; j < map->cols; j++) {
            map->map[i][j] = EVENT_NOWAY;  // 기본적으로 벽으로 설정
            map->enemies[i][j] = NULL;     // 적 없음
            map->enemy_counts[i][j] = 0;   // 적 수 0
        }
    }

    // 맵의 주요 위치 설정 (출구, 시작점 등)
    map->start = (Position){0, 1};  // 시작점 (0, 1) 위치
    map->exit = (Position){3, 3};   // 출구 (3, 3) 위치

    // 유적 맵 구성
    int tempMap[4][4] = {
        {1, 1, 1, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 1}
    };

    // 맵에 이벤트 설정
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            switch (tempMap[i][j]) {
                case 1:
                    map->map[i][j] = EVENT_PATH;  // 길
                    break;
                case 0:
                    map->map[i][j] = EVENT_NOWAY;  // 벽
                    break;
            }
        }
    }

    // 전사(1, 1)와 궁수(2, 2) 캐릭터 설정
    // 전사 배치 (1, 1)
    map->map[1][1] = EVENT_ENEMY;  
    map->enemy_counts[1][1] = 1;
    map->enemies[1][1] = malloc(sizeof(Enemy));
    initialize_warrior(&map->enemies[1][1][0]);

    // 궁수 배치 (2, 2)
    map->map[2][2] = EVENT_ENEMY;  
    map->enemy_counts[2][2] = 1;
    map->enemies[2][2] = malloc(sizeof(Enemy));
    initialize_archer(&map->enemies[2][2][0]);
}

// 전사 초기화 함수
void initialize_warrior(Enemy *warrior) {
    warrior->type = "Warrior";
    warrior->hp = 100;
    warrior->attack = 10;
    warrior->defense = 5;
}

// 궁수 초기화 함수
void initialize_archer(Enemy *archer) {
    archer->type = "Archer";
    archer->hp = 70;
    archer->attack = 15;
    archer->defense = 3;
}

// 유적 맵 출력
void printMap(Map *map, Position playerPos) {
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (i == playerPos.y && j == playerPos.x)
                printf("[P] ");  // 플레이어 위치
            else if (i == map->exit.y && j == map->exit.x)
                printf("[E] ");  // 출구
            else if (map->map[i][j] == EVENT_ENEMY)
                printf("[EN]");  // 적
            else if (map->map[i][j] == EVENT_CHEST)
                printf("[CH]");  // 보물
            else
                printf("[-] ");  // 벽
        }
        printf("\n");
    }
}

// 플레이어 이동
void movePlayer(Dungeon *dungeon, int dx, int dy) {
    int newX = dungeon->playerPos.x + dx;
    int newY = dungeon->playerPos.y + dy;

    if (newX >= 0 && newX < dungeon->currentMap.cols && newY >= 0 && newY < dungeon->currentMap.rows && dungeon->currentMap.map[newY][newX] != EVENT_NOWAY) {
        dungeon->playerPos.x = newX;
        dungeon->playerPos.y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);
    } else {
        printf("Invalid move.\n");
    }
}

// 던전 실행
void run_dungeon(Dungeon *dungeon) {
    printf("\n--- Entering the Ruins ---\n");
    printMap(&dungeon->currentMap, dungeon->playerPos);

    while (1) {
        printf("\nChoose direction (N: North, S: South, E: East, W: West, 0: Exit Dungeon): ");
        char direction;
        scanf(" %c", &direction);

        if (direction == '0') {
            printf("Exiting the ruins.\n");
            break;
        }

        switch (direction) {
            case 'N': case 'n': movePlayer(dungeon, 0, -1); break;
            case 'S': case 's': movePlayer(dungeon, 0, 1); break;
            case 'E': case 'e': movePlayer(dungeon, 1, 0); break;
            case 'W': case 'w': movePlayer(dungeon, -1, 0); break;
            default: printf("Invalid direction.\n"); break;
        }

        printMap(&dungeon->currentMap, dungeon->playerPos);

        if (dungeon->playerPos.x == dungeon->currentMap.exit.x && dungeon->playerPos.y == dungeon->currentMap.exit.y) {
            printf("You have reached the exit!\n");
            break;
        }
    }
}

int main() {
    Dungeon dungeon;
    dungeon.currentMap = ruins_map;
    dungeon.playerPos = dungeon.currentMap.start;

    // 유적 맵 초기화
    initialize_ruins_map(&dungeon.currentMap);

    // 던전 실행
    run_dungeon(&dungeon);

    return 0;
}
