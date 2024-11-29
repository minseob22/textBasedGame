#include <stdio.h>
#include <string.h>
#include <stdbool.h> // for bool type
#include "../include/speedCalculator.h"
#include "../include/character.h"
#include "../include/enemy.h"
#include "../include/attacker.h"











// 게이지가 100%인 다음 공격자를 찾는 함수




// 전투 루프에서 게이지 업데이트와 턴 종료 처리
/*void handle_turn(Character characters[], int char_count, Enemy enemies[], int enemy_count) {
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
}*/
