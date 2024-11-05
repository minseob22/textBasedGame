#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "../include/character.h"
#include "../include/enemy.h"

void initialize_battle_scene(Character characters[], int char_count, Enemy enemies[], int enemy_count);
void start_battle(Character characters[], int char_count, Enemy enemies[], int enemy_count);

#endif // BATTLE_SCENE_H
