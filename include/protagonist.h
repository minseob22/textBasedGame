#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include "character.h"

// 주인공 캐릭터 배열과 함수 선언
extern Character protagonist[];
int get_protagonist_count();
void set_protagonist_name(const char *name);
void display_protagonist(const Character *character);

#endif // PROTAGONIST_H
