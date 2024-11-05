#ifndef ENEMY_H
#define ENEMY_H

#define MAX_ENEMY_SIZE 6

typedef struct {
    char name[20];
    int health;
    int attack;
    int magic;
    int speed;
    int gauge;
    char species[20];
    int critical_rate;
    int dodge_rate;
} Enemy;

void initialize_enemies(Enemy enemies[], int count);
void display_enemy(const Enemy *enemy);

#endif // ENEMY_H
