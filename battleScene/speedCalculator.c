#include <stdio.h>
#include "../include/speedCalculator.h"

void update_turn_gauge(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    for (int i = 0; i < char_count; i++) {
        characters[i].gauge += characters[i].speed;
        if (characters[i].gauge >= 100) {
            characters[i].gauge = 0;
            printf("%s의 턴입니다!\n", characters[i].name);
        }
    }

    for (int i = 0; i < enemy_count; i++) {
        enemies[i].gauge += enemies[i].speed;
        if (enemies[i].gauge >= 100) {
            enemies[i].gauge = 0;
            printf("%s의 턴입니다!\n", enemies[i].name);
        }
    }
}

int is_battle_over(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    int characters_alive = 0;
    int enemies_alive = 0;
    
    for (int i = 0; i < char_count; i++) {
        if (characters[i].health > 0) characters_alive++;
    }
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].health > 0) enemies_alive++;
    }
    return (characters_alive == 0 || enemies_alive == 0);
}
