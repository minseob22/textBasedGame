#include <stdio.h>
#include <string.h>
#include "npc.h"

void interact_with_npc(NPC *npc) {
    if (strcmp(npc->type, "장비 상인") == 0) {
        printf("장비 상인: \"강력한 장비가 많이 준비되어 있지. 구매할 건가?\"\n");
        printf("1. 장비 구매\n");
        printf("2. 나가기\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("장비를 구매했습니다!\n");
        } else {
            printf("다음에 또 찾아오게나.\n");
        }
    } 
    else if (strcmp(npc->type, "물약 상인") == 0) {
        printf("물약 상인: \"여행 중에 필요한 물약이 준비되어 있어요. 구매하실래요?\"\n");
        printf("1. 물약 구매\n");
        printf("2. 나가기\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("물약을 구매했습니다!\n");
        } else {
            printf("언제든지 다시 오세요!\n");
        }
    } 
    else if (strcmp(npc->type, "암상인") == 0) {
        printf("암상인: \"희귀한 아이템을 가지고 있지. 필요하다면 가격은 비싸지만 팔아주지.\"\n");
        printf("1. 희귀 아이템 구매\n");
        printf("2. 나가기\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("희귀 아이템을 구매했습니다!\n");
        } else {
            printf("다음에 또 와.\n");
        }
    } 
    else if (strcmp(npc->type, "퀘스트 NPC") == 0) {
        printf("퀘스트 NPC: \"이곳에서 할 일이 많지. 도움을 줄 수 있겠나?\"\n");
        printf("1. 퀘스트 수락\n");
        printf("2. 나가기\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            printf("퀘스트를 수락했습니다! 자세한 사항은 퀘스트 메뉴에서 확인하세요.\n");
        } else {
            printf("언제든지 도움이 필요하면 오게나.\n");
        }
    } 
    else {
        printf("%s: \"대화할 수 없는 NPC입니다.\"\n", npc->name);
    }
}
