/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef QUESTION_H
#define QUESTION_H

#include <stdio.h>
#include <string.h>
#include "localization.h"

#define INCBIN_PREFIX g_
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include "incbin.h"

#define QUESTION_AMOUNT 32
#define QUESTION_PARTS 3
#define STRING_LEN 17

typedef struct {
    const char* question;
    const char* true_ans;
    const char* false_ans;
} question_t;

int question_init();

question_t question_get(int question_idx);

#endif