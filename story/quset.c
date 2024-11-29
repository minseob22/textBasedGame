#include <stdio.h>
#include <string.h>
#include "../include/quest.h"

// 화면 너비를 설정
#define FRAME_WIDTH 50


void initialize_quests(Quest quests[], int *quest_count) {
    static Dialogue quest1_dialogues[] = {
        {"Villager", "Please help us! Monsters are attacking from the ruins."},
        {"Warrior", "We'll take care of it. Don't worry."}
    };
    quests[0] = (Quest){
        .quest_id = 1,
        .title = "Ruins Investigation",
        .description = "Investigate the ruins and eliminate the monsters.",
        .is_completed = 0,
        .dialogues = quest1_dialogues,
        .dialogue_count = 2,
        .related_dungeon = 0
    };

    static Dialogue quest2_dialogues[] = {
        {"Mage", "The artifact holds incredible power. We must secure it."},
        {"Archer", "Or destroy it before it falls into the wrong hands."}
    };
    quests[1] = (Quest){
        .quest_id = 2,
        .title = "Artifact Retrieval",
        .description = "Retrieve or destroy the ancient artifact in the ruins.",
        .is_completed = 0,
        .dialogues = quest2_dialogues,
        .dialogue_count = 2,
        .related_dungeon = 1
    };

    *quest_count = 2;
}


void display_quests(Quest quests[], int quest_count) {
    printf("\nAvailable Quests:\n");
    for (int i = 0; i < quest_count; i++) {
        if (!quests[i].is_completed) {
            printf("%d. %s - %s\n", quests[i].quest_id, quests[i].title, quests[i].description);
        }
    }
}

// 퀘스트 완료 시 출력 수정
void complete_quest(Quest *quest) {
    printf("\nQuest Completed: %s\n", quest->title);

    for (int i = 0; i < quest->dialogue_count; i++) {
        draw_frame_with_text(quest->dialogues[i].speaker, quest->dialogues[i].line);
    }

    quest->is_completed = 1;
}

// 프레임을 그리는 함수
void draw_frame_with_text(const char *speaker, const char *line) {
    int line_length = strlen(line);
    int padding = (FRAME_WIDTH - line_length) / 2; // 중앙 정렬을 위한 여백 계산

    // 상단 프레임
    for (int i = 0; i < FRAME_WIDTH; i++) printf("-");
    printf("\n");

    // 대사 출력
    printf("| %-*s |\n", FRAME_WIDTH - 2, speaker); // speaker 출력
    for (int i = 0; i < FRAME_WIDTH; i++) printf("-");
    printf("\n");
    printf("|%*s%-*s|\n", padding, "", FRAME_WIDTH - padding - 2, line); // 중앙 정렬된 내용 출력

    // 하단 프레임
    for (int i = 0; i < FRAME_WIDTH; i++) printf("-");
    printf("\n");
}
