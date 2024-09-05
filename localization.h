/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#define LOCALE_ENGLISH  0
#define LOCALE_TURKISH  1

#ifndef LOCALE
#define LOCALE LOCALE_ENGLISH
#endif

#if LOCALE == LOCALE_TURKISH
#define LOCAL_QUESTION_FILE "questions_tr.txt"
#define LOCAL_TRUE "Dogru"
#define LOCAL_FALSE "Yanlis"

#elif LOCALE == LOCALE_ENGLISH
#define LOCAL_QUESTION_FILE "questions_en.txt"
#define LOCAL_TRUE "True"
#define LOCAL_FALSE "False"

#endif

#endif