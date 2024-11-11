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

    // 이벤트 타입 정의
    #define EVENT_NOWAY 0
    #define EVENT_PATH 1
    #define EVENT_NONE 2
    #define EVENT_ENEMY 3
    #define EVENT_CHEST 4

    typedef struct {
        int x; // 플레이어의 x 좌표
        int y; // 플레이어의 y 좌표
        int map[N][M]; // 맵 배열
        Enemy enemies[N][M];
    } Dungeon;

    void initialize_dungeon(Dungeon *dungeon);
    void move_party(Dungeon *dungeon, char direction, Character characters[], int char_count);
    void printMap(Dungeon *dungeon);
    void movePlayer(Dungeon *dungeon, int dx, int dy, Character characters[], int char_count);
    int handle_event(Dungeon *dungeon, Character characters[], int char_count);

    #endif // DUNGEON_H