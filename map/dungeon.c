#include <stdio.h>
#include <stdlib.h>
#include "../include/utility.h"
#include "../include/dungeon.h"
#include "../include/battleScene.h"
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"


// 여러 맵을 저장할 배열
Map all_maps[MAX_MAPS];

// 특정 맵을 로드하여 던전에 적용
void load_map(Dungeon *dungeon, Map *map) {
    dungeon->playerPos = map->start;
    dungeon->currentMap = *map;
}

// 던전 시작 시 맵 로드
void start_new_dungeon(Dungeon *dungeon, int map_index) {
    // 맵 초기화 함수 포인터 배열
    void (*map_initializers[MAX_MAPS])(Map *) = {
        initialize_map_1,
        initialize_map_2,
        initialize_map_3
    };

    if (map_index >= 0 && map_index < MAX_MAPS && map_initializers[map_index] != NULL) {
        // 선택된 맵 초기화
        Map selected_map;
        map_initializers[map_index](&selected_map);

        // 던전에 로드
        load_map(dungeon, &selected_map);

        printf("Loaded map %d into the dungeon.\n", map_index);
    } else {
        printf("Invalid map index or uninitialized map.\n");
    }
}

void initialize_map(Map *map, int rows, int cols) {
    map->rows = rows;
    map->cols = cols;

    // 맵 배열 동적 할당
    map->map = (int **)malloc(rows * sizeof(int *));
    map->enemies = (Enemy ***)malloc(rows * sizeof(Enemy **));
    map->enemy_counts = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        map->map[i] = (int *)malloc(cols * sizeof(int));
        map->enemies[i] = (Enemy **)malloc(cols * sizeof(Enemy *));
        map->enemy_counts[i] = (int *)malloc(cols * sizeof(int));

        for (int j = 0; j < cols; j++) {
            map->map[i][j] = EVENT_NOWAY;  // 기본 값 설정
            map->enemies[i][j] = NULL;    // 적 초기화
            map->enemy_counts[i][j] = 0;  // 적 수 초기화
        }
    }
}

// 첫 번째 맵 초기화
void initialize_map_1(Map *map) {
    initialize_map(map, 2, 2); // 2x2 크기의 맵

    map->start = (Position){0, 0};
    map->exit = (Position){1, 1};

    int tempMap[2][2] = {
        {1, 0},
        {1, 1}
    };

    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            map->map[i][j] = (tempMap[i][j] == 1) ? EVENT_PATH : EVENT_NOWAY;
        }
    }
    map->map[1][0] = EVENT_ENEMY;
    map->enemy_counts[1][0] = 4; // 4명의 적
    map->enemies[1][0] = malloc(sizeof(Enemy) * 4);
    initialize_goblin(&map->enemies[1][0][0], 0);
    initialize_goblin(&map->enemies[1][0][1], 1);
    initialize_orc(&map->enemies[1][0][2], 0);
    initialize_orc(&map->enemies[1][0][3], 1);
}
// 두 번째 맵 초기화
void initialize_map_2(Map *map) {
    initialize_map(map, 4, 4); // 4x4 크기의 맵

    map->start = (Position){0, 0};
    map->exit = (Position){3, 3};

    int tempMap[4][4] = {
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 1},
        {1, 1, 0, 1}
    };

    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            map->map[i][j] = (tempMap[i][j] == 1) ? EVENT_PATH : EVENT_NOWAY;
        }
    }

    map->map[1][2] = EVENT_ENEMY;
    map->enemy_counts[1][2] = 2;
    map->enemies[1][2] = malloc(sizeof(Enemy) * 2);
    initialize_orc(&map->enemies[1][2][0], 0);
    initialize_orc(&map->enemies[1][2][1], 1);
}



void initialize_map_3(Map *map) {
    // 맵 크기 초기화
    initialize_map(map, 5, 5); // 5x5 크기의 맵

    // 시작 위치와 출구 설정
    map->start = (Position){2, 2};
    map->exit = (Position){4, 4};

    // 맵 데이터 정의
    int tempMap[5][5] = {
        {1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1}
    };

    // 맵 데이터 복사
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            map->map[i][j] = (tempMap[i][j] == 1) ? EVENT_PATH : EVENT_NOWAY;
        }
    }

    // 적 초기화
    map->map[1][1] = EVENT_ENEMY;
    map->enemy_counts[1][1] = 4; // 4명의 적
    map->enemies[1][1] = malloc(sizeof(Enemy) * 4);
    initialize_goblin(&map->enemies[1][1][0], 0); // 첫 번째 고블린
    initialize_goblin(&map->enemies[1][1][1], 1); // 두 번째 고블린
    initialize_orc(&map->enemies[1][1][2], 0);    // 첫 번째 오크
    initialize_orc(&map->enemies[1][1][3], 1);    // 두 번째 오크
}


// 플레이어 이동
void move_party(Dungeon *dungeon, char direction, Character characters[], int char_count, int center_x, int center_y) {
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
    movePlayer(dungeon, dx, dy, characters, char_count, center_x, center_y);
    printf("Current position: (%d, %d)\n", dungeon->playerPos.x, dungeon->playerPos.y);
    printMap(dungeon, center_x, center_y);
}

// 맵을 출력
void printMap(Dungeon *dungeon, int center_x, int center_y) {
    int map_start_x = center_x - (dungeon->currentMap.cols * 3 / 2);
    int map_start_y = center_y - dungeon->currentMap.rows;

    for (int i = 0; i < dungeon->currentMap.rows; i++) {
        move_cursor(map_start_x, map_start_y + i);
        for (int j = 0; j < dungeon->currentMap.cols; j++) {
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

    // 안내 메시지 출력
    move_cursor(center_x - 40, center_y + dungeon->currentMap.rows + 2);
    printf("Choose direction (N: North, S: South, E: East, W: West, 0: Exit Dungeon):");
}


// 플레이어 위치 이동
void movePlayer(Dungeon *dungeon, int dx, int dy, Character characters[], int char_count, int center_x, int center_y) {
    int newX = dungeon->playerPos.x + dx;
    int newY = dungeon->playerPos.y + dy;

    // 맵 크기를 가져옵니다.
    int rows = dungeon->currentMap.rows;
    int cols = dungeon->currentMap.cols;

    // 새로운 위치가 맵의 범위 안에 있는지 확인하고 이동
    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && dungeon->currentMap.map[newY][newX] != EVENT_NOWAY) {
        dungeon->playerPos.x = newX;
        dungeon->playerPos.y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);

        // 새로운 위치가 출구인지 확인
        if (newX == dungeon->currentMap.exit.x && newY == dungeon->currentMap.exit.y) {
            printf("Exit found! Dungeon cleared!\n");
        } else if (!handle_event(dungeon, characters, char_count, center_x, center_y)) {
            printf("There is nothing here.\n");
        }
    } else {
        printf("Cannot move to (%d, %d)\n", newX, newY);
    }
}


// 이벤트 처리
int handle_event(Dungeon *dungeon, Character characters[], int char_count, int center_x, int center_y) {
    int x = dungeon->playerPos.x;
    int y = dungeon->playerPos.y;
    int event = dungeon->currentMap.map[y][x];

    switch (event) {
        case EVENT_NONE:
            return 0; // 아무 일도 없음
        case EVENT_ENEMY: {
            printf("You encountered enemies! Starting battle with all enemies at this location.\n");

            // 적 배열 및 개수를 가져옴
            int enemy_count = dungeon->currentMap.enemy_counts[y][x];
            Enemy *encounter_enemies = dungeon->currentMap.enemies[y][x];

            if (enemy_count > 0 && encounter_enemies != NULL) {
                // 전투 시작
                start_battle(characters, char_count, encounter_enemies, enemy_count, center_x, center_y);
                printMap(dungeon, center_x, center_y);
            } else {
                printf("No enemies found here. Event type might be incorrect.\n");
            }

            // 이벤트 완료 후 맵을 PATH로 변경
            dungeon->currentMap.map[y][x] = EVENT_PATH;
            return 1;
        }
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            return 1;
        default:
            return 0;
    }
}


void run_dungeon(Dungeon *dungeon, Character characters[], int char_count, int center_x, int center_y) {
    // 초기 맵 출력
    printMap(dungeon, center_x, center_y);

    while (1) {
        // 기존 입력 지우기
        move_cursor(center_x - 20, center_y + dungeon->currentMap.rows + 4);
        printf("                                                   ");

        // 입력 요청
        move_cursor(center_x - 20, center_y + dungeon->currentMap.rows + 4);
        char direction;
        scanf(" %c", &direction);

        if (direction == '0') { // 던전 종료
            move_cursor(center_x - 15, center_y + dungeon->currentMap.rows + 6);
            printf("Exiting the dungeon...");
            break;
        }

        // 플레이어 이동
        move_party(dungeon, direction, characters, char_count, center_x, center_y);

        // 맵 재출력
        printMap(dungeon, center_x, center_y);

        // 출구 도달 확인
        if (dungeon->playerPos.x == dungeon->currentMap.exit.x &&
            dungeon->playerPos.y == dungeon->currentMap.exit.y) {
            move_cursor(center_x - 20, center_y + dungeon->currentMap.rows + 6);
            printf("Congratulations! You cleared the dungeon!");
            break;
        }
    }
}

void free_map(Map *map) {
    for (int i = 0; i < map->rows; i++) {
        free(map->map[i]);
        free(map->enemies[i]);
        free(map->enemy_counts[i]);
    }
    free(map->map);
    free(map->enemies);
    free(map->enemy_counts);
}
