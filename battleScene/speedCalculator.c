#include <stdio.h>
#include "../include/speedCalculator.h"
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"

// 모든 캐릭터 및 적의 게이지를 업데이트하는 함수
void update_gauges(Attacker *all_attackers[], int total_count) {
    for (int i = 0; i < total_count; i++) {
        all_attackers[i]->gauge += all_attackers[i]->speed;
        if (all_attackers[i]->gauge > 100) {
            all_attackers[i]->gauge = 100; // 게이지를 100으로 제한
        }
    }
}

/*
void update_gauges(Attacker *all_attackers[], int total_count) {
    for (int i = 0; i < total_count; i++) {
        all_attackers[i]->gauge += all_attackers[i]->speed; // 속도에 비례하여 게이지 증가
        if (all_attackers[i]->gauge > 100) {
            all_attackers[i]->gauge = 100; // 최대 게이지 제한
        }
    }
}*/

// 게이지가 가장 높은 다음 공격자를 찾는 함수
int find_next_attacker(Attacker *all_attackers[], int total_count) {
    int max_gauge = -1;
    int attacker_index = -1;

    for (int i = 0; i < total_count; i++) {
        if (all_attackers[i]->gauge >= 100 && all_attackers[i]->gauge > max_gauge) {
            max_gauge = all_attackers[i]->gauge;
            attacker_index = i;
        }
    }
    return attacker_index;  // 가장 높은 게이지의 공격자 인덱스 반환, 없으면 -1
}

/*int find_next_attacker(Attacker *all_attackers[], int total_count) {
    for (int i = 0; i < total_count; i++) {
        if (all_attackers[i]->gauge >= 100) {
            return i; // 게이지가 100 이상인 첫 번째 공격자 인덱스를 반환
        }
    }
    return -1; // 행동할 수 있는 공격자가 없으면 -1 반환
}*/


// 전투 루프에서 가장 높은 게이지의 공격자가 우선적으로 턴을 가지도록 처리하는 함수
void handle_turn(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    int total_count = char_count + enemy_count;
    Attacker *all_attackers[total_count];

    // 캐릭터와 적을 하나의 배열로 병합
    for (int i = 0; i < char_count; i++) {
        all_attackers[i] = &characters[i].attacker;
    }
    for (int i = 0; i < enemy_count; i++) {
        all_attackers[char_count + i] = &enemies[i].attacker;
    }

    // 전투 루프
    while (!is_battle_over(characters, char_count, enemies, enemy_count)) {
        // 모든 캐릭터와 적의 게이지 업데이트
        update_gauges(all_attackers, total_count);

        // 가장 높은 게이지를 가진 다음 공격자를 선택
        int attacker_index = find_next_attacker(all_attackers, total_count);

        if (attacker_index != -1) {
            Attacker *attacker = all_attackers[attacker_index];

            // 여기서 공격 로직을 추가합니다. 예: 적 또는 캐릭터 중 하나를 타겟팅하여 공격 수행
            printf("%s's turn!\n", attacker->name);
            // 공격 후 게이지 초기화
            attacker->gauge = 0;
        }
    }
}

// 전투 종료 여부를 확인하는 함수
int is_battle_over(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    int characters_alive = 0;
    int enemies_alive = 0;
    
    // 살아 있는 캐릭터 수 확인
    for (int i = 0; i < char_count; i++) {
        if (characters[i].attacker.health > 0) characters_alive++;
    }
    
    // 살아 있는 적 수 확인
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].attacker.health > 0) enemies_alive++;
    }

    // 캐릭터나 적이 전부 사망했을 경우 전투 종료
    return (characters_alive == 0 || enemies_alive == 0);
}
