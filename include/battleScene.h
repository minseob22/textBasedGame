#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "character.h"
#include "enemy.h"

// 함수 인자 타입을 Character 및 Enemy로 수정
void initialize_battle_scene(Character characters[], int char_count, Enemy enemies[], int enemy_count);
void start_battle(Character characters[], int char_count, Enemy enemies[], int enemy_count);
void reset_gauge(Attacker *attacker);
int speed_gague(Character character[], int char_count, Enemy enemy[], int enemy_count);
void attack(Attacker *attacker, Attacker *defender);

#endif // BATTLE_SCENE_H