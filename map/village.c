#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "../include/utility.h"
#include "../include/village.h"
#include "../include/character.h"
#include "../include/npc.h"

void initialize_village(Village *village) {
    village->npc_count = 5;

    snprintf(village->npcs[0].name, sizeof(village->npcs[0].name), "Equipment Merchant");
    snprintf(village->npcs[0].type, sizeof(village->npcs[0].type), "Equipment");

    snprintf(village->npcs[1].name, sizeof(village->npcs[1].name), "Potion Merchant");
    snprintf(village->npcs[1].type, sizeof(village->npcs[1].type), "Potions");

    snprintf(village->npcs[2].name, sizeof(village->npcs[2].name), "Quest Giver");
    snprintf(village->npcs[2].type, sizeof(village->npcs[2].type), "Quests");

    snprintf(village->npcs[3].name, sizeof(village->npcs[3].name), "Innkeeper");
    snprintf(village->npcs[3].type, sizeof(village->npcs[3].type), "Rest");

    snprintf(village->npcs[4].name, sizeof(village->npcs[4].name), "Party Manager");
    snprintf(village->npcs[4].type, sizeof(village->npcs[4].type), "Party");
}


void village_menu(Village *village) {
    int keep_running = 1; // 메뉴 반복 여부를 제어하는 변수

    while (keep_running) {
        // 화면 초기화
        initialize_screen();

        // 콘솔 크기 가져오기
        COORD console_size = get_console_size();
        int center_x = console_size.X / 2;
        int center_y = console_size.Y / 2;

        // 메뉴 출력 위치 설정
        int menu_start_x = center_x - 20;
        int menu_start_y = center_y - 5;

        // 메뉴 출력
        move_cursor(menu_start_x, menu_start_y);
        printf("Welcome to the village! What would you like to do?");
        for (int i = 0; i < village->npc_count; i++) {
            move_cursor(menu_start_x, menu_start_y + i + 2);
            printf("%d. %s", i + 1, village->npcs[i].name);
        }
        move_cursor(menu_start_x, menu_start_y + village->npc_count + 2);
        printf("%d. Leave Village", village->npc_count + 1);

        // 사용자 입력 받기
        int choice;
        move_cursor(menu_start_x, menu_start_y + village->npc_count + 4);
        printf("Choice: ");
        scanf("%d", &choice);

        // 선택 처리
        if (choice >= 1 && choice <= village->npc_count) {
            interact_with_npc(&village->npcs[choice - 1]);
        } else if (choice == village->npc_count + 1) {
            printf("Leaving the village...\n");
            keep_running = 0; // 루프 종료
        } else {
            printf("Invalid choice. Try again.");
        }
    }
}

/*
void interact_with_npc(NPC *npc) {
    if (strcmp(npc->type, "Equipment") == 0) {
        printf("Equipment Merchant: \"Would you like to buy some powerful gear?\"\n");
        printf("1. Buy Equipment\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("You bought some equipment!\n");
        } else {
            printf("Come back anytime!\n");
        }
    } else if (strcmp(npc->type, "Potions") == 0) {
        printf("Potion Merchant: \"I have potions to help you on your journey. Would you like to buy?\"\n");
        printf("1. Buy Potions\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("You bought some potions!\n");
        } else {
            printf("See you next time!\n");
        }
    } else if (strcmp(npc->type, "Quests") == 0) {
        printf("Quest Giver: \"I have tasks for you. Can you help?\"\n");
        printf("1. Accept Quest\n");
        printf("2. Leave\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Quest accepted! Check the quest menu for details.\n");
        } else {
            printf("Come back if you need work.\n");
        }
    } else if (strcmp(npc->type, "Rest") == 0) {
        rest_party(); // 파티 HP 복구
    } else if (strcmp(npc->type, "Party") == 0) {
        manage_party(); // 파티 관리
    } else {
        printf("%s: \"You can't talk to this NPC.\"\n", npc->name);
    }

    // NPC와 상호작용 후에는 마을 메뉴로 돌아가야 함.
    printf("Returning to the village menu...\n");
    getchar(); // Enter 키 대기
}*/

void manage_party() {
    initialize_screen();

    // 콘솔 크기 가져오기
    COORD console_size = get_console_size();
    int center_x = console_size.X / 2;
    int center_y = console_size.Y / 2;

    int menu_start_x = center_x - 30;
    int menu_start_y = center_y - 10;

    // 현재 파티 출력
    move_cursor(menu_start_x, menu_start_y);
    printf("--- Manage Party ---");
    move_cursor(menu_start_x, menu_start_y + 2);
    printf("Current Party:");
    for (int i = 0; i < current_party_size; i++) {
        move_cursor(menu_start_x, menu_start_y + 3 + i);
        printf("%d. %s (%s)", i + 1, party[i].attacker.name, party[i].job);
    }

    // 메뉴 옵션 출력
    move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 1);
    printf("1. Add Member to Party");
    move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 2);
    printf("2. Remove Member from Party");
    move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 3);
    printf("3. Return to Village");

    // 사용자 입력 받기
    int choice;
    move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 5);
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // 파티에 추가 가능한 캐릭터 출력
        initialize_screen();
        move_cursor(menu_start_x, menu_start_y);
        printf("--- Add Member to Party ---");
        move_cursor(menu_start_x, menu_start_y + 2);
        printf("Available Members:");

        int protagonist_count = sizeof(protagonist) / sizeof(protagonist[0]);
        int displayed = 0;

        for (int i = 0; i < protagonist_count; i++) {
            // 이미 파티에 있는 멤버는 제외
            int is_in_party = 0;
            for (int j = 0; j < current_party_size; j++) {
                if (strcmp(protagonist[i].attacker.name, party[j].attacker.name) == 0) {
                    is_in_party = 1;
                    break;
                }
            }
            if (!is_in_party) {
                move_cursor(menu_start_x, menu_start_y + 3 + displayed);
                printf("%d. %s (%s)", i + 1, protagonist[i].attacker.name, protagonist[i].job);
                displayed++;
            }
        }

        if (displayed == 0) {
            move_cursor(menu_start_x, menu_start_y + 3 + displayed);
            printf("No members available to add.");
            getchar(); // 잠시 대기
            manage_party();
            return;
        }

        move_cursor(menu_start_x, menu_start_y + 3 + displayed + 2);
        printf("Choose a member to add: ");
        int index;
        scanf("%d", &index);

        if (index >= 1 && index <= protagonist_count) {
            add_to_party(index - 1);
        } else {
            move_cursor(menu_start_x, menu_start_y + 3 + displayed + 3);
            printf("Invalid choice. Returning to menu.");
        }
    } else if (choice == 2) {
        // 파티에서 제거 가능한 캐릭터 출력
        initialize_screen();
        move_cursor(menu_start_x, menu_start_y);
        printf("--- Remove Member from Party ---");
        move_cursor(menu_start_x, menu_start_y + 2);
        printf("Current Party:");
        for (int i = 0; i < current_party_size; i++) {
            move_cursor(menu_start_x, menu_start_y + 3 + i);
            printf("%d. %s (%s)", i + 1, party[i].attacker.name, party[i].job);
        }

        move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 1);
        printf("Choose a member to remove: ");
        int index;
        scanf("%d", &index);

        if (index >= 1 && index <= current_party_size) {
            remove_from_party(index - 1);
        } else {
            move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 2);
            printf("Invalid choice. Returning to menu.");
        }
    } else if (choice == 3) {
        return; // 마을 메뉴로 돌아감
    } else {
        move_cursor(menu_start_x, menu_start_y + 3 + current_party_size + 4);
        printf("Invalid choice. Returning to menu.");
    }

    manage_party();
}

void rest_party() {
    printf("\nThe party takes a rest. Everyone's HP has been restored!\n");
    for (int i = 0; i < current_party_size; i++) {
        party[i].attacker.health = party[i].attacker.max_health; // HP를 최대치로 복구
        printf("%s's HP: %d/%d\n", party[i].attacker.name, party[i].attacker.health, party[i].attacker.max_health);
    }
}
