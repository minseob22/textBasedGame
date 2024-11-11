#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"
#include "../include/attacker.h"

// Orc 종류의 적을 미리 정의
const Enemy orc_types[] = {
    {"Orc", {"Orc Warrior", 120, 25, 40, 0, 10, 8}},
    {"Orc", {"Orc Berserker", 150, 35, 30, 0, 5, 5}},
    {"Orc", {"Orc Shaman", 80, 20, 50, 0, 10, 7}},
};

// Orc 적의 개수를 반환하는 함수
int get_orc_count() {
    return sizeof(orc_types) / sizeof(orc_types[0]);
}

// 주어진 인덱스에 따라 Orc를 초기화
void initialize_orc(Enemy *enemy, int type_index) {
    if (type_index < get_orc_count()) {
        *enemy = orc_types[type_index];
    } else {
        printf("Invalid Orc type index\n");
    }
}
