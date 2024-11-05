#ifndef DUNGEON_H
#define DUNGEON_H

#define DUNGEON_SIZE 5 // 던전 맵의 크기 (5x5 예시)
#define EVENT_NONE 0
#define EVENT_ENEMY 1
#define EVENT_CHEST 2

typedef struct {
    int x, y; // 현재 파티 위치
    int map[DUNGEON_SIZE][DUNGEON_SIZE]; // 각 칸의 이벤트 (적, 보물 등)
} Dungeon;

void initialize_dungeon(Dungeon *dungeon);
void move_party(Dungeon *dungeon, char direction);
void handle_event(Dungeon *dungeon);

#endif // DUNGEON_H
