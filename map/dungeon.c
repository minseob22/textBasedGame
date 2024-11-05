#include <stdio.h>
#include "../include/dungeon.h"

void initialize_dungeon(Dungeon *dungeon) {
    dungeon->x = 0;
    dungeon->y = 0;

    // 이벤트 초기화 예시
    dungeon->map[1][1] = EVENT_ENEMY;
    dungeon->map[2][2] = EVENT_CHEST;
}

void move_party(Dungeon *dungeon, char direction) {
    switch (direction) {
        case 'N': if (dungeon->y > 0) dungeon->y--; break;
        case 'S': if (dungeon->y < DUNGEON_SIZE - 1) dungeon->y++; break;
        case 'E': if (dungeon->x < DUNGEON_SIZE - 1) dungeon->x++; break;
        case 'W': if (dungeon->x > 0) dungeon->x--; break;
        default: printf("잘못된 방향입니다.\n"); return;
    }
    printf("파티가 (%d, %d) 위치로 이동했습니다.\n", dungeon->x, dungeon->y);
}

void handle_event(Dungeon *dungeon) {
    int event = dungeon->map[dungeon->y][dungeon->x];
    switch (event) {
        case EVENT_NONE:
            printf("이곳에는 아무것도 없습니다.\n");
            break;
        case EVENT_ENEMY:
            printf("적을 만났습니다! 전투를 시작합니다.\n");
            // 전투 시작 코드 (start_battle 함수 호출)
            break;
        case EVENT_CHEST:
            printf("보물 상자를 발견했습니다!\n");
            // 보물 획득 코드
            break;
    }
}
