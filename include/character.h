#ifndef CHARACTER_H
#define CHARACTER_H

#include "attacker.h"

#define MAX_PARTY_SIZE 4

typedef struct {
    char name[20];
    char job[20];
    Attacker attacker;
} Character;

void initialize_characters(Character characters[], int count);
void display_character(const Character *character);

#endif // CHARACTER_H
