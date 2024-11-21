#include <stdio.h>
#include <string.h>
#include "../include/character.h"
#include "../include/attacker.h"

#define MAX_PARTY_SIZE 4

Character party[MAX_PARTY_SIZE]; // 파티 캐릭터 배열
int current_party_size = 0;      // 현재 파티에 포함된 캐릭터 수

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


void add_to_party(int index) {
    if (current_party_size >= MAX_PARTY_SIZE) {
        printf("Party is full! Cannot add more members.\n");
        return;
    }

    // 중복 확인
    for (int i = 0; i < current_party_size; i++) {
        if (strcmp(party[i].attacker.name, protagonist[index].attacker.name) == 0) {
            printf("Character %s is already in the party.\n", protagonist[index].attacker.name);
            return;
        }
    }

    // 파티에 추가
    party[current_party_size++] = protagonist[index];
    printf("Added %s to the party.\n", protagonist[index].attacker.name);
}

void remove_from_party(int index) {
    if (current_party_size <= 0) {
        printf("Party is empty! Cannot remove a character.\n");
        return;
    }

    if (index < 0 || index >= current_party_size) {
        printf("Invalid index! Please provide a valid index between 0 and %d.\n", current_party_size - 1);
        return;
    }

    // 제거된 캐릭터 출력
    printf("Removed %s from the party.\n", party[index].attacker.name);

    // 나머지 캐릭터를 한 칸 앞으로 이동
    for (int i = index; i < current_party_size - 1; i++) {
        party[i] = party[i + 1];
    }

    // 파티 크기 감소
    current_party_size--;
}