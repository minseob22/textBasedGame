#include <stdio.h>
#include <string.h>
#include "../include/character.h"
#include "../include/attacker.h"

// 주인공 캐릭터들 초기화
Character protagonist[] = {
    {
        .job = "Warrior",
        .attacker = { .name = "Default Hero 1", .health = 120, .attack = 30, .speed = 60, .gauge = 0, .critical_rate = 15, .dodge_rate = 10 }
    },
    {
        .job = "Mage",
        .attacker = { .name = "Stella", .health = 100, .attack = 40, .speed = 50, .gauge = 0, .critical_rate = 10, .dodge_rate = 7 }
    },
    {
        .job = "Archer",
        .attacker = { .name = "Ingi", .health = 90, .attack = 20, .speed = 70, .gauge = 0, .critical_rate = 30, .dodge_rate = 10 }
    },
    {
        .job = "Rogue",
        .attacker = { .name = "Khan", .health = 100, .attack = 25, .speed = 70, .gauge = 0, .critical_rate = 20, .dodge_rate = 15 }
    }
};

// 주인공 캐릭터 수 반환 함수
int get_protagonist_count() {
    return sizeof(protagonist) / sizeof(protagonist[0]);
}

// 주인공 캐릭터 이름 설정 함수 (Default Hero 1만 변경 가능)
void set_protagonist_name(const char *name) {
    snprintf(protagonist[0].attacker.name, sizeof(protagonist[0].attacker.name), "%s", name);
}

// 주인공 캐릭터 정보 출력 함수 (모든 정보)
void display_protagonist(const Character *character) {
    printf("name: %s\njob: %s\nhealth: %d\nattack: %d\nspeed: %d\n",
           character->attacker.name, character->job, character->attacker.health, character->attacker.attack, character->attacker.speed);
}
