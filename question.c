/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "question.h"

INCTXT(questions, LOCAL_QUESTION_FILE);

char questions[QUESTION_AMOUNT][QUESTION_PARTS][STRING_LEN];

int question_init() {
    const char *current_pos = g_questions_data;

    const char question[STRING_LEN];
    const char true_ans[STRING_LEN];
    const char false_ans[STRING_LEN];

    int question_count = 0;

    while (sscanf(current_pos, "%[^\t]\t%[^\t]\t%[^\n]\n", question, true_ans, false_ans) == QUESTION_PARTS) {
        strncpy(questions[question_count][0], question, STRING_LEN);
        questions[question_count][0][STRING_LEN - 1] = 0; // null terminate

        strncpy(questions[question_count][1], true_ans, STRING_LEN);
        questions[question_count][1][STRING_LEN - 1] = 0; // null terminate

        strncpy(questions[question_count][2], false_ans, STRING_LEN);
        questions[question_count][2][STRING_LEN - 1] = 0; // null terminate

        printf("question %d: %s - %s - %s\n", question_count, questions[question_count][0], questions[question_count][1], questions[question_count][2]);

        question_count++;
        // Move current_pos to the next line in the buffer
        current_pos = strchr(current_pos, '\n');  // Find the next newline
        if (current_pos) current_pos++;  // Move past the newline character
        else break;  // No more newlines, end of buffer
    }

    printf("total questions: %d\n", question_count);

    return question_count;
}

question_t question_get(int question_idx) {
    question_t question;
    question.question = questions[question_idx][0];
    question.true_ans = questions[question_idx][1];
    question.false_ans = questions[question_idx][2];

    return question;
}