#include <stdio.h>
#include "village.h"
#include "dungeon.h"
#include "npc.h"
#include "character.h"
#include "enemy.h"
#include "battleScene.h"
#include "attacker.h"
#include "story.h"

// 전역 캐릭터 배열
Character characters[4];

// Main game menu
void main_menu() {
    printf("\n--- Text-Based RPG Game ---\n");
    printf("1. Game Start\n");
    printf("2. Continue\n");
    printf("3. Exit\n");
    printf("Choice: ");
}

// Game loop function
void start_game() {
    int choice;
    main_menu();
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Game Start 선택 시
            play_prologue(); // story.c에서 처리
            break;
        case 2:
            printf("Continue is not implemented yet.\n");
            return;
        case 3:
            printf("Exiting the game.\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            start_game();
            return;
    }

    // 마을 및 던전 초기화
    Village village;
    initialize_village(&village);

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Enter Village\n");
        printf("2. Enter Dungeon\n");
        printf("3. Exit Game\n");
        printf("Choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                village_menu(&village);
                break;
            case 2: {
                printf("\n--- Select Dungeon Map ---\n");
                printf("1. Map 1\n");
                printf("2. Map 2\n");
                printf("3. Map 3\n");
                printf("Choice: ");
                
                int map_choice;
                scanf("%d", &map_choice);

                Dungeon dungeon;
                if (map_choice >= 1 && map_choice <= 3) {
                    start_new_dungeon(&dungeon, map_choice - 1); // 던전 초기화
                    run_dungeon(&dungeon, characters, 4); // 던전 실행
                } else {
                    printf("Invalid dungeon choice. Returning to main menu.\n");
                }
                break;
            }
            case 3:
                printf("Exiting the game.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

int main() {
    start_game();
    return 0;
}
