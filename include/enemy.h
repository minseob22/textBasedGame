#ifndef ENEMY_H
#define ENEMY_H

#include "attacker.h"

// 적 최대 개수 정의
#define MAX_ENEMY_SIZE 6

// 적 구조체 정의
typedef struct {
    char species[20];   // 적의 종족 또는 종류
    Attacker attacker;  // 적의 스탯을 포함한 Attacker 구조체
} Enemy;

// Goblin 관련 함수
int get_goblin_count();
void initialize_goblin(Enemy *enemy, int type_index);

// Mimic 관련 함수
int get_mimic_count();
void initialize_mimic(Enemy *enemy, int type_index);

// Orc 관련 함수
int get_orc_count();
void initialize_orc(Enemy *enemy, int type_index);

// 적의 정보를 출력하는 함수
void display_enemy(const Enemy *enemy);

#endif // ENEMY_H
