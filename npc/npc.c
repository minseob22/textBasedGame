#include <stdio.h>
#include <string.h>

#include "../include/utility.h"
#include "../include/npc.h"
#include "../include/village.h"
#include "../include/character.h"

// NPC와 상호작용 함수
void interact_with_npc(NPC *npc) {
    if (strcmp(npc->type, "Equipment") == 0) {
        printf("%s: \"I have the finest equipment. Would you like to buy something?\"\n", npc->name);
        printf("1. Buy equipment\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("You purchased equipment!\n");
        } else {
            printf("Come back anytime.\n");
        }
    } else if (strcmp(npc->type, "Potions") == 0) {
        printf("%s: \"I sell potions that will aid you on your journey. Interested?\"\n", npc->name);
        printf("1. Buy potions\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("You purchased potions!\n");
        } else {
            printf("Come again soon!\n");
        }
    } else if (strcmp(npc->type, "Quests") == 0) {
        printf("%s: \"I have tasks that need to be done. Can you help?\"\n", npc->name);
        printf("1. Accept quest\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("You accepted a quest! Check the quest menu for details.\n");
        } else {
            printf("Let me know if you change your mind.\n");
        }
    } else if (strcmp(npc->type, "Rest") == 0) {
        printf("%s: \"Would you like to rest and recover?\"\n", npc->name);
        printf("1. Rest\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("You and your party have rested and recovered all health!\n");
            rest_party(); // 파티 체력 복구
        } else {
            printf("Safe travels!\n");
        }
    } else if (strcmp(npc->type, "Party") == 0) {
        printf("%s: \"Would you like to manage your party?\"\n", npc->name);
        printf("1. Manage Party\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            manage_party(); // 파티 관리
        } else {
            printf("Let me know if you need to make changes to your party.\n");
        }
    } else {
        printf("%s: \"I can't help you right now.\"\n", npc->name);
    }

    // NPC와의 상호작용 후, 마을 메뉴로 돌아가기 전에 잠시 대기
    printf("Press Enter to return to the village menu...\n");
    getchar(); // 사용자 입력 대기
    getchar(); // 두 번 호출하여 잔여 개행 처리
}
