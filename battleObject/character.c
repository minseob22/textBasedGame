#include <stdio.h>
#include <string.h>
#include "../include/character.h"

void initialize_characters(Character characters[], int count) {
    for (int i = 0; i < count; i++) {
        snprintf(characters[i].name, sizeof(characters[i].name), "Character %d", i + 1);
        characters[i].health = 100;
        characters[i].attack = 20;
        characters[i].magic = 10;
        characters[i].speed = 10 + i * 2; // 속도를 다르게 설정
        characters[i].gauge = 0;
        strcpy(characters[i].job, "Warrior");
        characters[i].critical_rate = 10;
        characters[i].dodge_rate = 5;
    }
}

void display_character(const Character *character) {
    printf("캐릭터: %s, 체력: %d, 공격력: %d, 속도: %d\n", 
           character->name, character->health, character->attack, character->speed);
}
