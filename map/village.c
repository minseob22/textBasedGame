#include <stdio.h>
#include "../include/village.h"

void initialize_village(Village *village) {
    village->npc_count = 3;
    snprintf(village->npcs[0].name, sizeof(village->npcs[0].name), "장비 상인");
    snprintf(village->npcs[1].name, sizeof(village->npcs[1].name), "물약 상인");
    snprintf(village->npcs[2].name, sizeof(village->npcs[2].name), "퀘스트 NPC");
}

void village_menu(Village *village) {
    printf("마을에 도착했습니다. 무엇을 하시겠습니까?\n");
    for (int i = 0; i < village->npc_count; i++) {
        printf("%d. %s\n", i + 1, village->npcs[i].name);
    }
    int choice;
    scanf("%d", &choice);
    if (choice >= 1 && choice <= village->npc_count) {
        interact_with_npc(&village->npcs[choice - 1]);
    } else {
        printf("잘못된 선택입니다.\n");
    }
}
