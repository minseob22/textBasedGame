#ifndef SPEED_CALCULATOR_H
#define SPEED_CALCULATOR_H

#include "../include/character.h"
#include "../include/enemy.h"

void update_turn_gauge(Character characters[], int char_count, Enemy enemies[], int enemy_count);
int is_battle_over(Character characters[], int char_count, Enemy enemies[], int enemy_count);

#endif // SPEED_CALCULATOR_H
