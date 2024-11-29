#ifndef CHARACTER_H
#define CHARACTER_H

#include "attacker.h"

// 최대 파티 크기
#define MAX_PARTY_SIZE 4
#define MAX_PROTAGONIST_COUNT 4



int get_protagonist_count();

// 주인공 캐릭터 구조체 정의
typedef struct Character{
    char job[20];      // 캐릭터 직업
    Attacker attacker; // 캐릭터 스탯 (체력, 공격력 등)
} Character;


extern Character party[MAX_PARTY_SIZE];
extern int current_party_size;
extern Character protagonist[MAX_PROTAGONIST_COUNT];

// 함수 선언
void set_protagonist_name(const char *name);        // 주인공 이름 설정 함수
int get_protagonist_count();                        // 파티 내 캐릭터 수 반환 함수
void display_protagonist(const Character *character); // 캐릭터 정보 출력 함수
void add_to_party(int index);
void remove_from_party(int index);

#endif // CHARACTER_H
