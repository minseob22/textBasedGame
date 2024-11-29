#ifndef VILLAGE_H
#define VILLAGE_H

#include "character.h" // Character 관련 선언 포함
#include "npc.h"       // NPC 관련 선언 포함
#include "dungeon.h"   // Dungeon 관련 선언 포함
#include "windows.h"


#define MAX_NPCS 10



extern Character party[MAX_PARTY_SIZE];
extern int current_party_size;

extern Character protagonist[MAX_PROTAGONIST_COUNT];


typedef struct {
    NPC npcs[MAX_NPCS];
    int npc_count;
} Village;

void initialize_village(Village *village);
void village_menu(Village *village);
void manage_party();
void rest_party();
#endif // VILLAGE_H
