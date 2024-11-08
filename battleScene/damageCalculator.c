#include <stdio.h>
#include <stdlib.h>
#include "../include/damageCalculator.h"
#include "../include/character.h"
#include "../include/attacker.h"

int calculate_damage(int base_attack, int critical_rate, int dodge_rate) {
    int is_critical = (rand() % 100) < critical_rate;
    int is_dodge = (rand() % 100) < dodge_rate;

    if (is_dodge) return 0; // 공격이 빗나감
    return is_critical ? base_attack * 2 : base_attack;
}


