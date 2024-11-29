#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"
#include "../include/attacker.h"

// Goblin 종류의 적 정의
const Enemy goblin_types[] = {
    {"Goblin", {"Goblin Warrior", 100, 100, 15, 100, 0, 15, 5}},
    {"Goblin", {"Goblin Archer", 75, 75, 20, 60, 0, 20, 5}},
    {"Goblin", {"Goblin Wizard", 60, 60 ,30, 30, 0, 15, 5}},
    {"Goblin", {"Goblin Shaman", 60, 60, 20, 50, 0, 15, 5}},
};

// Mimic 종류의 적 정의
const Enemy mimic_types[] = {
    {"Mimic", {"Mimic Chest", 50, 50, 40, 30, 0, 25, 10}},
    {"Mimic", {"Mimic Treasure", 70, 70, 50, 25, 0, 20, 12}},
};

// Orc 종류의 적 정의
const Enemy orc_types[] = {
    {"Orc", {"Orc Warrior", 120, 120, 25, 90, 0, 10, 8}},
    {"Orc", {"Orc Berserker", 150, 150, 35, 50, 0, 5, 5}},
    {"Orc", {"Orc Shaman", 80, 80, 20, 50, 0, 10, 7}},
};

// Goblin 적의 개수 반환
int get_goblin_count() {
    return sizeof(goblin_types) / sizeof(goblin_types[0]);
}

// Mimic 적의 개수 반환
int get_mimic_count() {
    return sizeof(mimic_types) / sizeof(mimic_types[0]);
}

// Orc 적의 개수 반환
int get_orc_count() {
    return sizeof(orc_types) / sizeof(orc_types[0]);
}

// 주어진 인덱스에 따라 Goblin 초기화
void initialize_goblin(Enemy *enemy, int type_index) {
    if (type_index < get_goblin_count()) {
        *enemy = goblin_types[type_index];
    } else {
        printf("Invalid Goblin type index\n");
    }
}

// 주어진 인덱스에 따라 Mimic 초기화
void initialize_mimic(Enemy *enemy, int type_index) {
    if (type_index < get_mimic_count()) {
        *enemy = mimic_types[type_index];
    } else {
        printf("Invalid Mimic type index\n");
    }
}

// 주어진 인덱스에 따라 Orc 초기화
void initialize_orc(Enemy *enemy, int type_index) {
    if (type_index < get_orc_count()) {
        *enemy = orc_types[type_index];
    } else {
        printf("Invalid Orc type index\n");
    }
}

// 적의 정보를 출력하는 함수
void display_enemy(const Enemy *enemy) {    
    printf("Enemy Species: %s\nName: %s\nHealth: %d\nAttack: %d\nSpeed: %d\n",
           enemy->species, enemy->attacker.name, enemy->attacker.health, enemy->attacker.attack, enemy->attacker.speed);
}
