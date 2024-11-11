#include <stdio.h>
#include <stdlib.h>
#include "../include/dungeon.h"
#include "../include/battleScene.h"  // 전투 관련 함수 포함
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"

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
    dungeon->map[2][2] = EVENT_CHEST;

    // 특정 위치에 적 배치 (예: [1][1]에 고블린 2명,오크 2명,미믹 2명)
    dungeon->map[1][1] = EVENT_ENEMY;
    initialize_goblin(&dungeon->enemies[1][1], 0);  // 첫 번째 고블린
    initialize_goblin(&dungeon->enemies[1][2], 1);  // 두 번째 고블린
    initialize_orc(&dungeon->enemies[2][2], 0);     // 첫 번째 오크
    initialize_orc(&dungeon->enemies[2][3], 1);     // 두 번째 오크
    initialize_mimic(&dungeon->enemies[3][3], 0);   // 첫 번째 미믹
    initialize_mimic(&dungeon->enemies[3][2], 1);   // 두 번째 미믹
}

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

void movePlayer(Dungeon *dungeon, int dx, int dy, Character characters[], int char_count) {
    int newX = dungeon->x + dx;
    int newY = dungeon->y + dy;

    if (newX >= 0 && newX < N && newY >= 0 && newY < M && dungeon->map[newY][newX] != EVENT_NOWAY) {
        dungeon->x = newX;
        dungeon->y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);

        if (newX == exitPos.x && newY == exitPos.y) {
            printf("Exit found! Dungeon cleared!\n");
        } else if (!handle_event(dungeon, characters, char_count)) {
            printf("There is nothing here.\n");
        }
    } else {
        printf("Cannot move to (%d, %d)\n", newX, newY);
    }
}

int handle_event(Dungeon *dungeon, Character characters[], int char_count) {
    int event = dungeon->map[dungeon->y][dungeon->x];
    
    switch (event) {
        case EVENT_NONE:
            return 0;
        case EVENT_ENEMY: {
            printf("You encountered enemies! Starting battle with all enemies at this location.\n");

            // 현재 위치의 모든 적을 모아서 전투에 참여시키기
            Enemy encounter_enemies[6];
            int enemy_count = 0;

            // 최대 6명의 적을 탐색하여 encounter_enemies 배열에 추가
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (enemy_count < 6 && dungeon->map[dungeon->y][dungeon->x] == EVENT_ENEMY && dungeon->enemies[dungeon->y][dungeon->x].attacker.health > 0) {
                        encounter_enemies[enemy_count] = dungeon->enemies[dungeon->y][dungeon->x];
                        enemy_count++;
                    }
                }
            }

            initialize_battle_scene(characters, char_count, encounter_enemies, enemy_count);  // 전투 초기화
            start_battle(characters, char_count, encounter_enemies, enemy_count);             // 전투 시작
            break;
        }
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            break;
    }

    if (event != EVENT_NONE) {
        dungeon->map[dungeon->y][dungeon->x] = EVENT_PATH;
    }
    return event != EVENT_NONE;
}





// 다양한 적을 랜덤으로 배치하기 위해 사용하는 함수
void initialize_random_enemy(Enemy *enemy) {
    int enemy_type = rand() % 3;  // 3가지 유형의 적 중 하나 선택

    switch (enemy_type) {
        case 0:  // Goblin
            initialize_goblin(enemy, rand() % get_goblin_count());
            break;
        case 1:  // Orc
            initialize_orc(enemy, rand() % get_orc_count());
            break;
        case 2:  // Mimic
            initialize_mimic(enemy, rand() % get_mimic_count());
            break;
    }
}