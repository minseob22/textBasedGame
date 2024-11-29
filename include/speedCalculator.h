#ifndef SPEEDCALCULATOR_H
#define SPEEDCALCULATOR_H

#include "attacker.h"
#include "character.h"  // Character 타입 선언 포함
#include "enemy.h"

void update_gauges(Attacker *all_attackers[], int total_count);
int find_next_attacker(Attacker *all_attackers[], int total_count);
//void handle_turn(Character characters[], int char_count, Enemy enemies[], int enemy_count);
int is_battle_over(Character characters[], int char_count, Enemy enemies[], int enemy_count);


#endif // SPEEDCALCULATOR_H