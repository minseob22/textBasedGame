#ifndef DAMAGE_CALCULATOR_H
#define DAMAGE_CALCULATOR_H

#include "../include/character.h"
#include "../include/enemy.h"

int calculate_damage(int base_attack, int critical_rate, int dodge_rate);
void attack(Character *attacker, Enemy *defender);

#endif // DAMAGE_CALCULATOR_H
