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