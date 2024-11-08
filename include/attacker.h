#ifndef ATTACKER_H
#define ATTACKER_H

#include "attacker.h"

typedef struct {
    char name[20];
    int health;
    int attack;
    int speed;
    int gauge;
    int critical_rate;
    int dodge_rate;
} Attacker;

#endif // ATTACKER_H