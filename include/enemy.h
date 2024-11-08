#ifndef ENEMY_H
#define ENEMY_H

#include "attacker.h"

#define MAX_ENEMY_SIZE 6

typedef struct {
    char species[20];
    Attacker attacker;
} Enemy;

void initialize_enemies(Enemy enemies[], int count);
void display_enemy(const Enemy *enemy);

#endif // ENEMY_H
