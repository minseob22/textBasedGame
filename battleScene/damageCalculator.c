#include <stdio.h>
#include <stdlib.h>
#include "../include/damageCalculator.h"

int calculate_damage(int base_attack, int critical_rate, int dodge_rate) {
    int is_critical = (rand() % 100) < critical_rate;
    int is_dodge = (rand() % 100) < dodge_rate;

    if (is_dodge) return 0; // 공격이 빗나감
    return is_critical ? base_attack * 2 : base_attack;
}

void attack(Character *attacker, Enemy *defender) {
    int damage = calculate_damage(attacker->attack, attacker->critical_rate, defender->dodge_rate);
    defender->health -= damage;
    if (damage > 0) {
        printf("%s가 %s에게 %d의 데미지를 입혔습니다.\n", attacker->name, defender->name, damage);
    } else {
        printf("%s의 공격이 빗나갔습니다!\n", attacker->name);
    }
}
