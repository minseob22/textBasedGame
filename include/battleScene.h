#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "character.h"
#include "enemy.h"
#include "windows.h"
#include "../include/utility.h"  
#include "damageCalculator.h"

// 함수 인자 타입을 Character 및 Enemy로 수정
void reset_gauge(Attacker *attacker);
void update_gauges(Attacker *all_attackers[], int total_count);
int find_next_attacker(Attacker *all_attackers[], int total_count);
int is_battle_over(Character characters[], int char_count, Enemy enemies[], int enemy_count);

void start_battle(Character characters[], int char_count, Enemy enemies[], int enemy_count, int center_x, int center_y);

void attack(Attacker *attacker, Attacker *defender,int message_x, int message_y);
void end_turn(Attacker *attacker);
void print_gauge_bar(Attacker *all_attackers[], int total_count, int gauge_start_x, int gauge_start_y);
#endif // BATTLE_SCENE_H