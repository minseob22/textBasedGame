#ifndef DAMAGE_CALCULATOR_H
#define DAMAGE_CALCULATOR_H

#include "attacker.h"

#include "../include/character.h"
#include "../include/enemy.h"

int calculate_damage(int base_attack, int critical_rate, int dodge_rate);


#endif // DAMAGE_CALCULATOR_H
