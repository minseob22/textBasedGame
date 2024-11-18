#include <stdio.h>
#include <string.h>
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

// 주인공 이름 설정 함수
void set_protagonist_name_prompt() {
    char name[20];
    printf("Enter the name of the protagonist: ");
    scanf("%19s", name); // 주인공 이름을 최대 19자까지 입력받음
    set_protagonist_name(name); // 이름 설정 함수 호출
    printf("Welcome, %s!\n", name);
}

// Game loop function
void start_game() {
    int choice;
    main_menu();
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Game Start 선택 시
            play_prologue();            // 프롤로그 스토리 진행
            set_protagonist_name_prompt();  // 주인공 이름 설정
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

    Village village;
    Dungeon dungeon;

    initialize_village(&village);
    initialize_dungeon(&dungeon);

    while (1) {
        main_menu();
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                village_menu(&village);
                break;
            case 2:
                printf("\n--- Entering the Dungeon ---\n");
                while (1) {
                    printf("Choose direction (N: North, S: South, E: East, W: West, 0: Exit Dungeon): ");
                    char direction;
                    scanf(" %c", &direction);
                    
                    if (direction == '0') {
                        printf("Exiting the dungeon.\n");
                        break;
                    }

                    move_party(&dungeon, direction, characters, 4);
                }
                break;
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
