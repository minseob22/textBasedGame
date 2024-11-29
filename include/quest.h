#ifndef QUEST_H
#define QUEST_H


#include <stdio.h>
#include "character.h"
#include "dungeon.h"

#define MAX_QUESTS 10

typedef struct {
    char *speaker;  // 대화 주체 (예: "Warrior")
    char *line;     // 대화 내용
} Dialogue;

typedef struct {
    int quest_id;     // 퀘스트 ID
    char *title;      // 퀘스트 제목
    char *description; // 퀘스트 설명
    int is_completed; // 퀘스트 완료 여부
    Dialogue *dialogues; // 퀘스트와 관련된 대사
    int dialogue_count;  // 대사 개수
    int related_dungeon; // 관련된 던전 ID (예: 0, 1, 2)
} Quest;

void initialize_quests(Quest quests[], int *quest_count);
void display_quests(Quest quests[], int quest_count);
void complete_quest(Quest *quest);
void draw_frame_with_text(const char *speaker, const char *line);

#endif // QUEST_H