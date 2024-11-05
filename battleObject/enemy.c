#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"

void initialize_enemies(Enemy enemies[], int count) {
    for (int i = 0; i < count; i++) {
        snprintf(enemies[i].name, sizeof(enemies[i].name), "Enemy %d", i + 1);
        enemies[i].health = 80;
        enemies[i].attack = 15;
        enemies[i].magic = 5;
        enemies[i].speed = 8 + i * 2;
        enemies[i].gauge = 0;
        strcpy(enemies[i].species, "Goblin");
        enemies[i].critical_rate = 5;
        enemies[i].dodge_rate = 10;
    }
}

void display_enemy(const Enemy *enemy) {
    printf("적: %s, 체력: %d, 공격력: %d, 속도: %d\n", 
           enemy->name, enemy->health, enemy->attack, enemy->speed);
}
