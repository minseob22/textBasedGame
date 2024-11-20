#include <stdio.h>
#include "../include/battleScene.h"
#include "../include/damageCalculator.h"
#include "../include/attacker.h"
#include "../include/speedCalculator.h" 


void reset_gauge(Attacker *attacker) {
    attacker->gauge = 0; // 턴이 끝난 후 게이지를 초기화
}


void start_battle(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
    int total_count = char_count + enemy_count;
    Attacker *all_attackers[total_count];
    
    // 캐릭터와 적을 하나의 배열로 병합
    for (int i = 0; i < char_count; i++) {
        all_attackers[i] = &characters[i].attacker;
    }
    for (int i = 0; i < enemy_count; i++) {
        all_attackers[char_count + i] = &enemies[i].attacker;
    }

    printf("Battle started!\n");

    while (1) {
        // 행동 게이지 업데이트
        update_gauges(all_attackers, total_count);

        // 행동 가능한 캐릭터 찾기
        int attacker_index = find_next_attacker(all_attackers, total_count);
        
        if (attacker_index != -1) {
            Attacker *attacker = all_attackers[attacker_index];

            // 공격 수행
            if (attacker_index < char_count) {
                // 캐릭터가 공격
                printf("Choose your target:\n");
                for (int i = 0; i < enemy_count; i++) {
                    if (enemies[i].attacker.health > 0) {
                        printf("%d: %s (Health: %d)\n", i, enemies[i].attacker.name, enemies[i].attacker.health);
                    }
                }

                int target_index;
                do {
                    printf("Enter the target index: ");
                    scanf("%d", &target_index);
                    if (target_index < 0 || target_index >= enemy_count || enemies[target_index].attacker.health <= 0) {
                        printf("Invalid target. Please choose a valid target.\n");
                    }
                } while (target_index < 0 || target_index >= enemy_count || enemies[target_index].attacker.health <= 0);

                attack(attacker, &enemies[target_index].attacker);
            } else {
                // 적이 공격
                int target_index;
                do {
                    target_index = rand() % char_count; // 적은 랜덤으로 타겟 선택
                } while (characters[target_index].attacker.health <= 0);

                attack(attacker, &characters[target_index].attacker);
            }


            // 공격 후 게이지 초기화
            reset_gauge(attacker);

            // 전투 종료 조건 (예: 모든 적 처치 시 종료)
            int all_enemies_defeated = 1;
            for (int i = 0; i < enemy_count; i++) {
                if (enemies[i].attacker.health > 0) {
                    all_enemies_defeated = 0;
                    break;
                }
            }
            if (all_enemies_defeated) {
                printf("All enemies have been defeated!\n");
                break;
            }

            // 모든 캐릭터가 처치되면 전투 종료
            int all_characters_defeated = 1;
            for (int i = 0; i < char_count; i++) {
                if (characters[i].attacker.health > 0) {
                    all_characters_defeated = 0;
                    break;
                }
            }
            if (all_characters_defeated) {
                printf("All characters have been defeated. Game Over!\n");
                break;
            }
        }
    }
}

void attack(Attacker *attacker, Attacker *defender) {
    int damage = calculate_damage(attacker->attack, attacker->critical_rate, defender->dodge_rate);
    defender->health -= damage;
    if (damage > 0) {
        printf("%s attacked %s for %d damage.\n", attacker->name, defender->name, damage);
    } else {
        printf("%s's attack missed!\n", attacker->name);
    }
}
