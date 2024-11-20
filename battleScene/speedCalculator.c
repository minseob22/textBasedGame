#include <stdio.h>
#include <string.h>
#include <stdbool.h> // for bool type
#include "../include/speedCalculator.h"
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"


// 현재 턴을 진행할 공격자를 추적
int current_turn_index = -1;
bool is_turn_active = false;

// 게이지를 업데이트하는 함수
void update_gauges(Attacker *all_attackers[], int total_count) {
    if (!is_turn_active) { // 현재 턴이 진행 중이지 않을 때만 게이지 업데이트
        for (int i = 0; i < total_count; i++) {
            all_attackers[i]->gauge += all_attackers[i]->speed; // 속도에 비례하여 게이지 증가
            if (all_attackers[i]->gauge > 1000) {
                int overflow = all_attackers[i]->gauge - 1000; // 초과된 게이지 계산
                all_attackers[i]->gauge = 1000;                // 현재 게이지를 최대값으로 설정
                all_attackers[i]->overflow = overflow;         // 초과분을 저장
            }
        }
    }
}
// 턴이 끝나고 게이지를 다시 업데이트
void end_turn(Attacker *attacker) {
    printf("%s has finished their turn!\n", attacker->name);
    attacker->gauge = attacker->overflow; // 초과 게이지를 다음 턴에 반영
    attacker->overflow = 0;               // 초과 게이지 초기화
    is_turn_active = false;               // 턴 활성화 상태 해제
    current_turn_index = -1;              // 현재 턴 인덱스 초기화
}


// 게이지가 100%인 다음 공격자를 찾는 함수
int find_next_attacker(Attacker *all_attackers[], int total_count) {
    if (is_turn_active && current_turn_index != -1) {
        // 이미 턴을 진행 중인 경우 현재 턴의 공격자를 유지
        return current_turn_index;
    }

    // 가장 높은 게이지를 가진 공격자를 찾음
    int max_gauge = -1;
    int attacker_index = -1;
    for (int i = 0; i < total_count; i++) {
        if (all_attackers[i]->gauge >= 1000 && all_attackers[i]->gauge > max_gauge) {
            max_gauge = all_attackers[i]->gauge;
            attacker_index = i;
        }
    }

    if (attacker_index != -1) {
        // 턴 활성화 상태로 설정
        is_turn_active = true;
        current_turn_index = attacker_index;
    }

    return attacker_index; // 공격자 인덱스 반환 (없으면 -1)
}

// 전투 루프에서 게이지 업데이트와 턴 종료 처리
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

    while (!is_battle_over(characters, char_count, enemies, enemy_count)) {
        update_gauges(all_attackers, total_count);

        int attacker_index = find_next_attacker(all_attackers, total_count);
        if (attacker_index != -1) {
            Attacker *attacker = all_attackers[attacker_index];
            printf("\n%s's turn!\n", attacker->name);

            // 공격 로직 추가
            printf("%s attacks!\n", attacker->name);

            // 턴 종료 후 게이지 업데이트 재개
            end_turn(attacker);
        }
    }
}
