#include <stdio.h>
#include <string.h>
#include "../include/enemy.h"
#include "../include/attacker.h"

// Mimic 종류의 적을 미리 정의
const Enemy mimic_types[] = {
    {"Mimic", {"Mimic Chest", 50, 40, 30, 0, 25, 10}},
    {"Mimic", {"Mimic Treasure", 70, 50, 25, 0, 20, 12}},
};

// Mimic 적의 개수를 반환하는 함수
int get_mimic_count() {
    return sizeof(mimic_types) / sizeof(mimic_types[0]);
}

// 주어진 인덱스에 따라 Mimic을 초기화
void initialize_mimic(Enemy *enemy, int type_index) {
    if (type_index < get_mimic_count()) {
        *enemy = mimic_types[type_index];
    } else {
        printf("Invalid Mimic type index\n");
    }
}
