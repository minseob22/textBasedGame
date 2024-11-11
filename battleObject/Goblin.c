#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"
#include "../include/attacker.h"

// Goblin 종류의 적을 미리 정의
const Enemy goblin_types[] = {
    {"Goblin", {"Goblin Warrior", 100, 15, 50, 0, 15, 5}},
    {"Goblin", {"Goblin Archer", 75, 20, 60, 0, 20, 5}},
    {"Goblin", {"Goblin Wizard", 60, 30, 30, 0, 15, 5}},
    {"Goblin", {"Goblin Shaman", 60, 20, 50, 0, 15, 5}},
};

// Goblin 적의 개수를 반환하는 함수
int get_goblin_count() {
    return sizeof(goblin_types) / sizeof(goblin_types[0]);
}

// 주어진 인덱스에 따라 Goblin을 초기화
void initialize_goblin(Enemy *enemy, int type_index) {
    if (type_index < get_goblin_count()) {
        *enemy = goblin_types[type_index];
    } else {
        printf("Invalid Goblin type index\n");
    }
}