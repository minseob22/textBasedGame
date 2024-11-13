#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 4

// 던전 맵의 이벤트 타입 정의
#define EVENT_NOWAY 1  // 벽 (이동 불가)
#define EVENT_ENEMY 2  // 몬스터
#define EVENT_CHEST 3  // 보물 상자
#define EVENT_PATH 0   // 경로

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int map[N][M];
    int x;
    int y;
} Dungeon;

Position playerPos = {0, 0};
Position exitPos = {3, 3};

// 던전 초기화 함수
void initialize_dungeon(Dungeon *dungeon) {
    dungeon->x = 0;
    dungeon->y = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dungeon->map[i][j] = EVENT_PATH;  // 기본적으로 경로로 설정
        }
    }
}

// 던전 파일로부터 초기화하는 함수
void initialize_dungeon_from_file(Dungeon *dungeon, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open dungeon file.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(file, "%d", &dungeon->map[i][j]);
        }
    }

    fclose(file);
}

// 던전 맵 출력 함수
void printMap(Dungeon *dungeon) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == dungeon->y && j == dungeon->x)
                printf("[P] ");  // 플레이어 위치
            else if (i == exitPos.y && j == exitPos.x)
                printf("[E] ");  // 출구 위치
            else if (dungeon->map[i][j] == EVENT_NOWAY)
                printf("[-] ");  // 벽
            else if (dungeon->map[i][j] == EVENT_ENEMY)
                printf("[EN]");  // 몬스터
            else if (dungeon->map[i][j] == EVENT_CHEST)
                printf("[CH]");  // 보물 상자
            else
                printf("[ ] ");  // 경로
        }
        printf("\n");
    }
}

// 플레이어 이동 함수
void moveParty(Dungeon *dungeon, char direction) {
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

// 플레이어 실제 이동 함수
void movePlayer(Dungeon *dungeon, int dx, int dy) {
    int newX = dungeon->x + dx;
    int newY = dungeon->y + dy;

    if (newX >= 0 && newX < M && newY >= 0 && newY < N && dungeon->map[newY][newX] != EVENT_NOWAY) {
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

// 이벤트 처리 함수 (적 또는 보물 상자 등)
void handle_event(Dungeon *dungeon) {
    int event = dungeon->map[dungeon->y][dungeon->x];
    
    switch (event) {
        case EVENT_ENEMY:
            printf("You encountered enemies! Prepare for battle.\n");
            break;
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            break;
        case EVENT_PATH:
        case EVENT_NOWAY:
            printf("Nothing here.\n");
            break;
    }

    // 이벤트 발생 후 해당 위치는 경로로 변경
    if (event != EVENT_PATH) {
        dungeon->map[dungeon->y][dungeon->x] = EVENT_PATH;
    }
}

int main() {
    Dungeon dungeon;
    initialize_dungeon(&dungeon);
    initialize_dungeon_from_file(&dungeon, "dungeon_map.txt");

    printMap(&dungeon);

    char direction;
    while (1) {
        printf("Enter direction (N/S/E/W): ");
        scanf(" %c", &direction);
        moveParty(&dungeon, direction);
    }

    return 0;
}
