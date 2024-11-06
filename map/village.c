#include <stdio.h>
#include "../include/village.h"

void initialize_village(Village *village) {
    village->npc_count = 3;
    snprintf(village->npcs[0].name, sizeof(village->npcs[0].name), "Equipment Merchant");
    snprintf(village->npcs[1].name, sizeof(village->npcs[1].name), "Potion Merchant");
    snprintf(village->npcs[2].name, sizeof(village->npcs[2].name), "Quest NPC");
}

void village_menu(Village *village) {
    printf("You have arrived in the village. What would you like to do?\n");
    for (int i = 0; i < village->npc_count; i++) {
        printf("%d. %s\n", i + 1, village->npcs[i].name);
    }
    int choice;
    scanf("%d", &choice);
    if (choice >= 1 && choice <= village->npc_count) {
        interact_with_npc(&village->npcs[choice - 1]);
    } else {
        printf("Invalid choice.\n");
    }
}
