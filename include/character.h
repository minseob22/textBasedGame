#ifndef CHARACTER_H
#define CHARACTER_H

#define MAX_PARTY_SIZE 4

typedef struct {
    char name[20];
    int health;
    int attack;
    int magic;
    int speed;
    int gauge;
    char job[20];
    int critical_rate;
    int dodge_rate;
} Character;

void initialize_characters(Character characters[], int count);
void display_character(const Character *character);

#endif // CHARACTER_H
