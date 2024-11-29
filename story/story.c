#include <stdio.h>
#include "character.h"
#include "enemy.h"
#include "dungeon.h"
#include "utility.h"

// 함수 선언
void play_prologue();
void play_tutorial();

extern Character party[MAX_PARTY_SIZE];
extern Character protagonist[MAX_PROTAGONIST_COUNT];
extern int current_party_size;

// 프롤로그 진행 함수
void play_prologue() {
    // 화면 초기화 및 프레임 출력
    initialize_screen();

    // 화면 크기 가져오기
    COORD console_size = get_console_size();
    int center_x = console_size.X / 2;
    int center_y = console_size.Y / 2;

    // 중앙에 텍스트를 출력하도록 설정
    move_cursor(center_x - 10, center_y - 3);
    printf("--- Prologue ---");
    move_cursor(center_x - 30, center_y - 2);
    printf("Once upon a time, in a distant land...");
    move_cursor(center_x - 25, center_y - 1);
    printf("The hero embarks on a great journey.");

    // 주인공 이름 입력
    char name[20];
    move_cursor(center_x - 20, center_y + 1);
    printf("Enter your hero's name: ");
    scanf("%s", name);

    // 주인공 이름 설정
    set_protagonist_name(name);

    // 환영 메시지 출력
    move_cursor(center_x - 20, center_y + 3);
    printf("Welcome, %s! Your journey begins...", name);

    // 다음으로 진행
    move_cursor(center_x - 15, center_y + 5);
    printf("Press Enter to continue...");
    getchar(); // 입력 대기
    getchar(); // 두 번째 입력 대기 (버퍼 클리어)

    // 튜토리얼 맵 진입
    play_tutorial();
}

// 튜토리얼 맵 진행 함수
void play_tutorial() {
    // 화면 초기화 및 프레임 출력
    initialize_screen();

    // 화면 크기 가져오기
    COORD console_size = get_console_size();
    int center_x = console_size.X / 2;
    int center_y = console_size.Y / 2;

    move_cursor(center_x - 10, center_y - 3);
    printf("--- Tutorial Dungeon ---");

    Dungeon tutorial_dungeon;
    Map tutorial_map;

    // 튜토리얼 맵 초기화
    initialize_map_1(&tutorial_map);

    // 던전에 튜토리얼 맵 로드
    load_map(&tutorial_dungeon, &tutorial_map);

    // 던전 실행
    run_dungeon(&tutorial_dungeon, party, current_party_size, center_x, center_y);

    // 동적 메모리 해제
    free_map(&tutorial_map);

    // 클리어 메시지 출력
    initialize_screen(); // 화면 초기화
    move_cursor(center_x - 15, center_y);
    printf("Tutorial completed successfully!");

    move_cursor(center_x - 20, center_y + 2);
    printf("Press Enter to return to the main menu...");
    getchar(); // 입력 대기
    getchar(); // 버퍼 클리어
}
