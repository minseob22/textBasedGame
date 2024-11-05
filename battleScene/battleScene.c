#include <stdio.h>
#include "../include/battleScene.h"

void initialize_battle_scene(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    printf("전투가 시작되었습니다!\n");
    for (int i = 0; i < char_count; i++) {
        printf("아군 %d: %s\n", i + 1, characters[i].name);
    }
    for (int i = 0; i < enemy_count; i++) {
        printf("적 %d: %s\n", i + 1, enemies[i].name);
    }
}

void start_battle(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    initialize_battle_scene(characters, char_count, enemies, enemy_count);
    // 여기서 전투 턴 루프와 게이지 시스템을 구현
}
