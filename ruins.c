#include <stdio.h>
#include <stdlib.h>

#define RUINS_N 4
#define RUINS_M 4

// 유적 맵 이벤트 타입 정의
#define EVENT_NOWAY 1    // 벽 (이동 불가)
#define EVENT_ENEMY 2    // 적
#define EVENT_CHEST 3    // 보물 상자
#define EVENT_PATH 0     // 경로
#define EVENT_PUZZLE 4   // 퍼즐
#define EVENT_RELIC 5    // 유물

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int map[RUINS_N][RUINS_M];
    int x;
    int y;
} Ruins;

Position relicPos = {3, 3};

// 유적 초기화 함수
void initialize_ruins(Ruins *ruins) {
    // 초기 플레이어 위치
    ruins->x = 0;
    ruins->y = 0;

    // 유적 맵 구성
    int tempMap[RUINS_N][RUINS_M] = {
        {0, 1, 2, 1},
        {0, 4, 0, 1},
        {0, 0, 0, 1},
        {1, 1, 0, 5}  // 유물이 있는 위치
    };

    // 맵 복사
    for (int i = 0; i < RUINS_N; i++) {
        for (int j = 0; j < RUINS_M; j++) {
            ruins->map[i][j] = tempMap[i][j];
        }
    }
}

// 유적 맵 출력 함수
void printRuinsMap(Ruins *ruins) {
    for (int i = 0; i < RUINS_N; i++) {
        for (int j = 0; j < RUINS_M; j++) {
            if (i == ruins->y && j == ruins->x)
                printf("[P] ");  // 플레이어 위치
            else if (i == relicPos.y && j == relicPos.x)
                printf("[R] ");  // 유물 위치
            else if (ruins->map[i][j] == EVENT_NOWAY)
                printf("[-] ");
            else if (ruins->map[i][j] == EVENT_ENEMY)
                printf("[E] ");
            else if (ruins->map[i][j] == EVENT_CHEST)
                printf("[CH]");
            else if (ruins->map[i][j] == EVENT_PUZZLE)
                printf("[PU]");
            else if (ruins->map[i][j] == EVENT_RELIC)
                printf("[RE]");
            else
                printf("[ ] ");
        }
        printf("\n");
    }
}

// 유적 이벤트 처리 함수
void handle_ruins_event(Ruins *ruins) {
    int event = ruins->map[ruins->y][ruins->x];

    switch (event) {
        case EVENT_ENEMY:
            printf("An enemy appears! Prepare for battle!\n");
            // 적 전투 로직 추가
            break;
        case EVENT_CHEST:
            printf("You found a treasure chest! It contains gold.\n");
            // 아이템 획득 로직 추가
            break;
        case EVENT_PUZZLE:
            printf("A mysterious puzzle blocks your way.\n");
            // 퍼즐 로직 추가 (예: 간단한 퀴즈 또는 선택지 제공)
            printf("Solve the puzzle to proceed.\n");
            ruins->map[ruins->y][ruins->x] = EVENT_PATH;  // 퍼즐 해결 후 경로로 변경
            break;
        case EVENT_RELIC:
            printf("You discovered an ancient relic! It radiates power.\n");
            // 유물 획득 로직 추가
            ruins->map[ruins->y][ruins->x] = EVENT_PATH;  // 유물 획득 후 경로로 변경
            break;
        case EVENT_PATH:
            printf("You walk through the ruins.\n");
            break;
        default:
            printf("Nothing here.\n");
            break;
    }
}

// 플레이어 이동 함수
void moveRuinsPlayer(Ruins *ruins, char direction) {
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

    int newX = ruins->x + dx;
    int newY = ruins->y + dy;

    if (newX >= 0 && newX < RUINS_M && newY >= 0 && newY < RUINS_N && ruins->map[newY][newX] != EVENT_NOWAY) {
        ruins->x = newX;
        ruins->y = newY;
        printf("Moved to (%d, %d)\n", newX, newY);
        handle_ruins_event(ruins);
    } else {
        printf("Cannot move to (%d, %d)\n", newX, newY);
    }
    printRuinsMap(ruins);
}

// 메인 함수
int main() {
    Ruins ruins;
    initialize_ruins(&ruins);

    printf("Welcome to the Ancient Ruins.\n");
    printRuinsMap(&ruins);

    char direction;
    while (1) {
        printf("Enter direction (N/S/E/W): ");
        scanf(" %c", &direction);
        moveRuinsPlayer(&ruins, direction);
    }

    return 0;
}
