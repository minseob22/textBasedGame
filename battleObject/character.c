#include <stdio.h>
#include <string.h>
#include "../include/character.h"
#include "../include/attacker.h"

void initialize_characters(Character characters[], int count) {
    for (int i = 0; i < count; i++) {
        snprintf(characters[i].name, sizeof(characters[i].name), "Character %d", i + 1);
        characters[i].attacker.health = 100;
        characters[i].attacker.attack = 20;
        characters[i].attacker.speed = 10 + i * 2; // 속도를 다르게 설정
        characters[i].attacker.gauge = 0;
        strcpy(characters[i].job, "Warrior");
        characters[i].attacker.critical_rate = 10;
        characters[i].attacker.dodge_rate = 5;
    }
}

void display_character(const Character *character) {
    printf("캐릭터: %s\n체력: %d\n공격력: %d\n 속도: %d\n", 
           character->name, character->attacker.health, character->attacker.attack, character->attacker.speed);
}
