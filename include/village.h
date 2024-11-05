#ifndef VILLAGE_H
#define VILLAGE_H

#include "../include/npc.h"

#define MAX_NPCS 10

typedef struct {
    NPC npcs[MAX_NPCS];
    int npc_count;
} Village;

void initialize_village(Village *village);
void village_menu(Village *village);

#endif // VILLAGE_H
