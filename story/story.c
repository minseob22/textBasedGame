#include <stdio.h>
#include "protagonist.h"
#include "dungeon.h"

void play_prologue();
void play_tutorial();

// 프롤로그 진행 함수
void play_prologue() {
    printf("\n--- Prologue ---\n");
    printf("Once upon a time, in a distant land...\n");
    printf("The hero embarks on a great journey.\n");

    // 주인공 이름 입력
    char name[20];
    printf("Enter your hero's name: ");
    scanf("%s", name);
    set_protagonist_name(name); // 주인공 이름 설정

    printf("\nWelcome, %s! Your journey begins...\n", name);

    // 튜토리얼 맵 진입
    play_tutorial();
}

// 튜토리얼 맵 진행 함수
void play_tutorial() {
    printf("\n--- Tutorial Dungeon ---\n");

    Dungeon tutorial_dungeon;
    Map tutorial_map;

    // 튜토리얼 맵 초기화 (initialize_map_2 사용)
    initialize_map_2(&tutorial_map);

    // 던전에 튜토리얼 맵 로드
    load_map(&tutorial_dungeon, &tutorial_map);

    // 튜토리얼 맵 플레이
    run_dungeon(&tutorial_dungeon);

    printf("Congratulations! You have completed the tutorial.\n");
}