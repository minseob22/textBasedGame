#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"
#include "../include/attacker.h"

// 적의 종류와 스탯을 미리 정의한 배열
const Enemy predefined_enemies[] = {
    {"Goblin", {"goblin_warrior", 100, 15, 50, 0, 15, 5}},
    {"Goblin", {"goblin_archer", 75, 20, 60, 0, 20, 5}},
    {"Goblin", {"goblin_wizard", 60, 30, 30, 0, 15, 5}},
    {"Goblin", {"goblin_shaman", 60, 20, 50, 0, 15, 5}},
};

// 배열의 크기 계산
int get_predefined_enemy_count() {
    return sizeof(predefined_enemies) / sizeof(predefined_enemies[0]);
}


// 주어진 인덱스에 해당하는 적을 초기화하여 enemies 배열에 설정하는 함수
void initialize_enemies(Enemy enemies[], int enemy_count) {
    int predefined_enemy_count = get_predefined_enemy_count();  // 함수 호출로 개수 가져오기
    for (int i = 0; i < enemy_count; i++) {
        int type_index = i % predefined_enemy_count;
        enemies[i] = predefined_enemies[type_index];
        snprintf(enemies[i].attacker.name, sizeof(enemies[i].attacker.name), "%s %d", predefined_enemies[type_index].species, i + 1);
    }
}

// 적의 정보를 출력하는 함수
void display_enemy(const Enemy *enemy) {
    printf("enemy spieces: %s\nhealth: %d\nattack: %d\nspeed: %d\n",
           enemy->attacker.name, enemy->attacker.health, enemy->attacker.attack, enemy->attacker.speed);
}