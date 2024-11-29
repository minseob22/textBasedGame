#ifndef NPC_H
#define NPC_H

#include "character.h" 
#include "windows.h"


typedef struct {
    char name[20];
    char type[20]; // NPC 유형 (장비 상인, 물약 상인, 암상인, 퀘스트 NPC 등)
} NPC;

void interact_with_npc(NPC *npc);


#endif // NPC_H
