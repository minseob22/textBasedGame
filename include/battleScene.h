#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "../include/character.h"
#include "../include/enemy.h"
#include "attacker.h"

void initialize_battle_scene(Character characters[], int char_count, Enemy enemies[], int enemy_count);
void reset_gauge(Attacker *attacker);
void start_battle(Attacker characters[], int char_count, Attacker enemies[], int enemy_count);
int speed_gague(Character character[], int char_count, Enemy enemy[], int enmey_count);
void attack(Attacker *attacker, Attacker *defender);



#endif // BATTLE_SCENE_H
