#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/utility.h"  
#include "../include/battleScene.h"
#include "../include/dungeon.h"
#include "../include/damageCalculator.h"
#include "../include/attacker.h"


// 현재 턴을 진행할 공격자를 추적
int current_turn_index = -1;
bool is_turn_active = false;

void reset_gauge(Attacker *attacker) {
    attacker->gauge = attacker->overflow; // 초과 게이지를 다음 턴에 반영
    attacker->overflow = 0;               // 초과 게이지 초기화
    is_turn_active = false;               // 턴 활성화 상태 해제
}

// 게이지를 업데이트하는 함수
void update_gauges(Attacker *all_attackers[], int total_count) {
    for (int i = 0; i < total_count; i++) {
        if (all_attackers[i]->health <= 0) {
            continue; // 체력이 0인 경우 게이지를 증가시키지 않음
        }
        all_attackers[i]->gauge += all_attackers[i]->speed; // 속도에 비례하여 게이지 증가
        if (all_attackers[i]->gauge >= 1000) {
            int overflow = all_attackers[i]->gauge - 1000; // 초과된 게이지 계산
            all_attackers[i]->gauge = 1000;                // 현재 게이지를 최대값으로 설정
            all_attackers[i]->overflow = overflow;         // 초과분을 저장
        }
    }
}

int find_next_attacker(Attacker *all_attackers[], int total_count) {
    int max_gauge = -1;
    int attacker_index = -1;

    // 가장 높은 게이지를 가진 공격자를 찾음
    for (int i = 0; i < total_count; i++) {
        if (all_attackers[i]->health <= 0) {
            continue; // 체력이 0인 경우 건너뜀
        }
        if (all_attackers[i]->gauge >= 1000 && all_attackers[i]->gauge > max_gauge) {
            max_gauge = all_attackers[i]->gauge;
            attacker_index = i;
        }
    }

    return attacker_index; // 공격자 인덱스 반환
}



int is_battle_over(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    // 전투 종료 여부 판단 로직 구현
    int all_characters_defeated = 1;
    for (int i = 0; i < char_count; i++) {
        if (characters[i].attacker.health > 0) {
            all_characters_defeated = 0;
            break;
        }
    }

    int all_enemies_defeated = 1;
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].attacker.health > 0) {
            all_enemies_defeated = 0;
            break;
        }
    }

    return all_characters_defeated || all_enemies_defeated;
}


void start_battle(Character characters[], int char_count, Enemy enemies[], int enemy_count, int center_x, int center_y) {
    // 화면 초기화
    initialize_screen();

    // 위치 설정
    int gauge_start_x = center_x - 50;
    int gauge_start_y = center_y - 14;

    int names_start_x = center_x - 50;
    int names_start_y = gauge_start_y + 3;

    int allies_status_x = center_x - 40;
    int allies_status_y = center_y - 5;

    int enemies_status_x = center_x + 20;
    int enemies_status_y = center_y - 5;

    int choices_start_x = center_x - 20;
    int choices_start_y = center_y + 5;

    int message_x = center_x - 70; // 메시지 출력 위치 (중앙 아래)
    int message_y = center_y + 10;

    int total_count = char_count + enemy_count;
    Attacker *all_attackers[total_count];

    for (int i = 0; i < char_count; i++) {
        all_attackers[i] = &characters[i].attacker;
    }
    for (int i = 0; i < enemy_count; i++) {
        all_attackers[char_count + i] = &enemies[i].attacker;
    }

    while (1) {
        // 게이지 업데이트
        update_gauges(all_attackers, total_count);

        /* 게이지 상태 출력
        move_cursor(gauge_start_x, gauge_start_y);
        printf("[Gauge Status]");
        move_cursor(gauge_start_x, gauge_start_y + 1);
        printf("100%%================================================================================0%%");


        move_cursor(names_start_x, names_start_y);
        printf("                                                     "); // 이전 내용을 지우기 위해 공백 출력

        // Order 출력
        move_cursor(names_start_x, names_start_y);
        printf("Order: ");
        for (int i = 0; i < total_count; i++) {
            printf("[%s] ", all_attackers[i]->name);
        }*/

       print_gauge_bar(all_attackers, total_count, gauge_start_x, gauge_start_y);

        // 행동 가능한 캐릭터 찾기
        int attacker_index = find_next_attacker(all_attackers, total_count);

        if (attacker_index != -1) {
            Attacker *attacker = all_attackers[attacker_index];

            // 아군 상태 출력
            move_cursor(allies_status_x, allies_status_y);
            printf("Allies:");
            for (int i = 0; i < char_count; i++) {
                move_cursor(allies_status_x, allies_status_y + i + 1);
                printf("%s (HP: %d)", characters[i].attacker.name, characters[i].attacker.health);
            }

            // 적 상태 출력
            move_cursor(enemies_status_x, enemies_status_y);
            printf("Enemies:");
            for (int i = 0; i < enemy_count; i++) {
                move_cursor(enemies_status_x, enemies_status_y + i + 1);
                printf("%s (HP: %d)", enemies[i].attacker.name, enemies[i].attacker.health);
            }

            if (attacker_index < char_count) { // 아군의 턴
                move_cursor(choices_start_x, choices_start_y);
                printf("Choose your target:");
                for (int i = 0; i < enemy_count; i++) {
                    if (enemies[i].attacker.health > 0) {
                        move_cursor(choices_start_x, choices_start_y + i + 1);
                        printf("%d: %s (Health: %d)", i, enemies[i].attacker.name, enemies[i].attacker.health);
                    }
                }

                move_cursor(choices_start_x, choices_start_y + enemy_count + 1);
                printf("Enter the target index: ");
                int target_index;
                scanf("%d", &target_index);

                if (target_index < 0 || target_index >= enemy_count || enemies[target_index].attacker.health <= 0) {
                    move_cursor(choices_start_x, choices_start_y + enemy_count + 2);
                    printf("Invalid target. Please choose again.");
                    continue;
                }

                // 아군의 공격 수행
                attack(attacker, &enemies[target_index].attacker, message_x, message_y);

            } else { // 적의 턴
                int target_index;
                int attempts = 0; // 무한 루프 방지를 위한 시도 횟수 제한
                const int MAX_ATTEMPTS = 100;

                // 아군 중 공격 가능한 대상 찾기
                do {
                    target_index = rand() % char_count;
                    attempts++;
                    if (attempts >= MAX_ATTEMPTS) {
                        // 모든 아군이 체력이 0 이하인 경우
                        move_cursor(message_x, message_y + 1);
                        printf("No valid targets for enemy to attack.");
                        return;
                    }
                } while (characters[target_index].attacker.health <= 0);

                // 적의 공격 수행
                move_cursor(message_x, message_y); // 메시지 출력 위치로 이동
                attack(attacker, &characters[target_index].attacker, message_x, message_y);
}
            reset_gauge(attacker);

            // 전투 종료 조건 확인
            int all_enemies_defeated = 1;
            for (int i = 0; i < enemy_count; i++) {
                if (enemies[i].attacker.health > 0) {
                    all_enemies_defeated = 0;
                    break;
                }
            }
            if (all_enemies_defeated) {
                move_cursor(center_x - 10, center_y);
                printf("All enemies defeated! Victory!");
                getchar(); // 대기
                break;
            }

            int all_allies_defeated = 1;
            for (int i = 0; i < char_count; i++) {
                if (characters[i].attacker.health > 0) {
                    all_allies_defeated = 0;
                    break;
                }
            }
            if (all_allies_defeated) {
                move_cursor(center_x - 10, center_y);
                printf("All allies defeated. Game Over.");
                getchar(); // 대기
                break;
            }
        }
    }
    initialize_screen(); // 화면 초기화
}



void attack(Attacker *attacker, Attacker *defender, int message_x, int message_y) {
    int damage = calculate_damage(attacker->attack, attacker->critical_rate, defender->dodge_rate);
    defender->health -= damage;

    // 메시지 출력 위치로 이동
    move_cursor(message_x, message_y);
    printf("                                                   "); // 이전 메시지 지우기
    move_cursor(message_x, message_y);

    if (damage > 0) {
        printf("%s attacked %s for %d damage.", attacker->name, defender->name, damage);
    } else {
        printf("%s's attack missed!", attacker->name);
    }
}

// 턴이 끝나고 게이지를 다시 업데이트
void end_turn(Attacker *attacker) {
    printf("%s has finished their turn!\n", attacker->name);
    attacker->overflow = 0;               // 초과 게이지 초기화
    is_turn_active = false;               // 턴 활성화 상태 해제
    current_turn_index = -1;              // 현재 턴 인덱스 초기화
}


void print_gauge_bar(Attacker *all_attackers[], int total_count, int gauge_start_x, int gauge_start_y) {
    // 게이지 상태 출력
    move_cursor(gauge_start_x, gauge_start_y);
    printf("[Gauge Status]");
    move_cursor(gauge_start_x, gauge_start_y + 1);
    printf("100%%========================================0%%");

    // 순서 출력 (게이지 아래 한 줄)
    move_cursor(gauge_start_x, gauge_start_y + 2);
    printf("Order: ");
    for (int i = 0; i < total_count; i++) {
        if (all_attackers[i]->health > 0) {
            printf("[%s] ", all_attackers[i]->name);
        }
    }

    // 현재 턴인 캐릭터 출력
    if (current_turn_index != -1 && all_attackers[current_turn_index]->health > 0) {
        move_cursor(gauge_start_x, gauge_start_y + 3); // 게이지 아래 추가 라인
        printf("Current Turn: [%s]", all_attackers[current_turn_index]->name);
    }
}
