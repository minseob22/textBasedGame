#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "village.h"
#include "dungeon.h"
#include "npc.h"
#include "character.h"
#include "enemy.h"
#include "battleScene.h"
#include "attacker.h"
#include "story.h"
#include "./include/utility.h"

// 전역 캐릭터 배열
extern Character party[MAX_PARTY_SIZE];
extern Character protagonist[MAX_PROTAGONIST_COUNT];
extern int current_party_size;


// 창 크기 변경 감지 및 프레임 재설정
void check_and_reset_frame() {
    static COORD prev_size = {0, 0};
    COORD current_size = get_console_size();

    // 창 크기가 변경되었을 때 프레임 재설정
    if (current_size.X != prev_size.X || current_size.Y != prev_size.Y) {
        prev_size = current_size;
        initialize_screen(); // 화면 재설정
    }
}


// Main game menu
void main_menu() {
        initialize_screen(); // 화면 초기화 및 프레임 출력

        // 화면 크기 가져오기
        COORD console_size = get_console_size();

    // 메뉴 텍스트를 출력할 위치 계산
    int center_x = console_size.X / 2;
    int center_y = console_size.Y / 2;

    // 메뉴 출력
    move_cursor(center_x - 10, center_y - 2); // 제목 출력 위치
    printf("--- Text-Based RPG Game ---");

    move_cursor(center_x - 10, center_y); // 메뉴 선택지 출력
    printf("1. Game Start");
    move_cursor(center_x - 10, center_y + 1);
    printf("2. Continue");
    move_cursor(center_x - 10, center_y + 2);
    printf("3. Exit");

    move_cursor(center_x - 10, center_y + 4); // 입력 대기 위치
    printf("Choice: ");
}

// Game loop function
void start_game() {
    while (1) {
        initialize_screen(); // 화면 초기화 및 프레임 출력

        // 화면 크기 가져오기
        COORD console_size = get_console_size();
        int center_x = console_size.X / 2;
        int center_y = console_size.Y / 2;
        main_menu();

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Game Start 선택 시
                system("cls");
                play_prologue(); // 프롤로그 실행
                break;

            case 2: // Continue 선택 시 (구현되지 않음)
                system("cls");
                move_cursor(50, 10);
                printf("Continue is not implemented yet.\n");
                Sleep(2000); // 2초 대기
                break;

            case 3: // Exit 선택 시
                system("cls");
                move_cursor(50, 10);
                printf("Exiting the game...\n");
                Sleep(2000); // 2초 대기
                return;

            default: // 잘못된 입력 처리
                system("cls");
                move_cursor(50, 10);
                printf("Invalid choice. Please try again.\n");
                Sleep(2000); // 2초 대기
                break;
        }

        // 마을 및 던전 초기화
        Village village;
        initialize_village(&village);

        while (1) {
            system("cls");
            initialize_screen();
            move_cursor(50, 8);
            printf("--- Main Menu ---\n");
            move_cursor(50, 10);
            printf("1. Enter Village\n");
            move_cursor(50, 11);
            printf("2. Enter Dungeon\n");
            move_cursor(50, 12);
            printf("3. Exit Game\n");
            move_cursor(50, 14);
            printf("Choice: ");

            int choice;
            scanf("%d", &choice);

            switch (choice) {
                case 1: // 마을 진입
                    village_menu(&village);
                    break;

                case 2: { // 던전 진입
                    system("cls");
                    initialize_screen();
                    move_cursor(50, 10);
                    printf("--- Select Dungeon Map ---\n");
                    move_cursor(50, 12);
                    printf("1. Map 1\n");
                    move_cursor(50, 13);
                    printf("2. Map 2\n");
                    move_cursor(50, 14);
                    printf("3. Map 3\n");
                    move_cursor(50, 16);
                    printf("Choice: ");

                    int map_choice;
                    scanf("%d", &map_choice);

                    Dungeon dungeon;
                    if (map_choice >= 1 && map_choice <= 3) {
                        start_new_dungeon(&dungeon, map_choice - 1); // 던전 초기화
                        run_dungeon(&dungeon, party, current_party_size, center_x, center_y); // 던전 실행
                    } else {
                        system("cls");
                        move_cursor(50, 10);
                        printf("Invalid dungeon choice. Returning to main menu.\n");
                        Sleep(2000); // 2초 대기
                    }
                    break;
                }

                case 3: // 게임 종료
                    system("cls");
                    move_cursor(50, 10);
                    printf("Exiting the game...\n");
                    Sleep(2000); // 2초 대기
                    return;

                default: // 잘못된 입력 처리
                    system("cls");
                    move_cursor(50, 10);
                    printf("Invalid choice. Please try again.\n");
                    Sleep(2000); // 2초 대기
                    break;
            }
        }
    }
}

int main() {
    initialize_screen(); // 화면 초기화
    start_game();        // 게임 시작
    return 0;
}
