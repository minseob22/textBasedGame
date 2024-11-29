#ifndef ATTACKER_H
#define ATTACKER_H

#include "attacker.h"

typedef struct Attacker{
    char name[20];
    int health;
    int max_health;     // 최대 체력
    int attack;
    int speed;
    int gauge;
    int critical_rate;
    int dodge_rate;
    int overflow; // 게이지 초과분 저장
} Attacker;

#endif // ATTACKER_H