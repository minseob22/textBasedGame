#include <stdio.h>
#include "../include/dungeon.h"

void initialize_dungeon(Dungeon *dungeon) {
    dungeon->x = 0;
    dungeon->y = 0;

    // Initialize events (example)
    dungeon->map[1][1] = EVENT_ENEMY;
    dungeon->map[2][2] = EVENT_CHEST;
}

void move_party(Dungeon *dungeon, char direction) {
    switch (direction) {
        case 'N': if (dungeon->y > 0) dungeon->y--; break;
        case 'S': if (dungeon->y < DUNGEON_SIZE - 1) dungeon->y++; break;
        case 'E': if (dungeon->x < DUNGEON_SIZE - 1) dungeon->x++; break;
        case 'W': if (dungeon->x > 0) dungeon->x--; break;
        default: printf("Invalid direction.\n"); return;
    }
    printf("The party moved to position (%d, %d).\n", dungeon->x, dungeon->y);
}

void handle_event(Dungeon *dungeon) {
    int event = dungeon->map[dungeon->y][dungeon->x];
    switch (event) {
        case EVENT_NONE:
            printf("There is nothing here.\n");
            break;
        case EVENT_ENEMY:
            printf("You encountered an enemy! Starting battle.\n");
            // Code to start battle (call start_battle function)
            break;
        case EVENT_CHEST:
            printf("You found a treasure chest!\n");
            // Code to obtain treasure
            break;
    }
}
