#ifndef CHARACTER_H
#define CHARACTER_H

#include "attacker.h"

// 최대 파티 크기
#define MAX_PARTY_SIZE 4

// 주인공 캐릭터 구조체 정의
typedef struct {
    char name[20];     // 캐릭터 이름
    char job[20];      // 캐릭터 직업
    Attacker attacker; // 캐릭터 스탯 (체력, 공격력 등)
} Character;

// 함수 선언
void set_protagonist_name(const char *name);        // 주인공 이름 설정 함수
int get_protagonist_count();                        // 파티 내 캐릭터 수 반환 함수
void display_protagonist(const Character *character); // 캐릭터 정보 출력 함수

#endif // CHARACTER_H
