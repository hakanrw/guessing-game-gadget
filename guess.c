/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <stdio.h>
#include <math.h>
#include <pico/stdlib.h>
#include <pico/binary_info.h>
#include <pico/rand.h>
#include <hardware/i2c.h>

#include "guess.h"
#include "lcd.h"
#include "question.h"
#include "localization.h"

static bool last_button_a_state = false;
static bool last_button_b_state = false;

static question_t current_question;
static int false_ans_first;
static int current_question_idx;
static int question_count;

static int true_ans_count = 0;

static int state = 0; // 0 -> question, 1 -> true ans, 2 -> false ans

void pins_setup() {
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);

    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(LCD_SDA, GPIO_FUNC_I2C);
    gpio_set_function(LCD_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(LCD_SDA);
    gpio_pull_up(LCD_SCL);

    lcd_init();
    question_count = question_init();
    current_question = question_get(0);
    false_ans_first = get_rand_32() % 2;
    current_question_idx = 0;
}

void question_loop() {
    bool button_a_state = gpio_get(BUTTON_A);
    bool button_b_state = gpio_get(BUTTON_B);

    // pressed a
    if (button_a_state && !last_button_a_state) {
        printf("pressed a\n");
        state = 1 + false_ans_first;
    }

    // pressed b
    if (button_b_state && !last_button_b_state) {
        printf("pressed b\n");
        state = 2 - false_ans_first;
    }

    lcd_set_cursor(0, 0);
    lcd_string(current_question.question);
    lcd_set_cursor(1, false_ans_first ? 8 : 0);
    lcd_string(current_question.true_ans);
    lcd_set_cursor(1, false_ans_first ? 0 : 8);
    lcd_string(current_question.false_ans);
}

void answer_loop() {
    if (state == 1) gpio_put(LED_GREEN, true);
    else gpio_put(LED_RED, true);

    if (state == 1) true_ans_count++;

    lcd_clear();
    lcd_set_cursor(0, 0);
    if (state == 1) lcd_string(LOCAL_TRUE "!");
    else lcd_string(LOCAL_FALSE " :(");

    sleep_ms(2000);

    lcd_clear();
    gpio_put(LED_GREEN, false);
    gpio_put(LED_RED, false);
    current_question_idx = (current_question_idx + 1) % question_count;
    current_question = question_get(current_question_idx);
    false_ans_first = get_rand_32() % 2;
    state = 0;

    char true_msg[STRING_LEN];
    char false_msg[STRING_LEN];

    snprintf(true_msg, STRING_LEN, "%d %s", true_ans_count, LOCAL_TRUE);
    snprintf(false_msg, STRING_LEN, "%d %s", question_count - true_ans_count, LOCAL_FALSE);

    // finished all questions
    if (current_question_idx == 0) {
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_string(true_msg);
        lcd_set_cursor(1, 0);
        lcd_string(false_msg);
        sleep_ms(5000);
        true_ans_count = 0;
        lcd_clear();
    }
}

void board_loop() {
    bool button_a_state = gpio_get(BUTTON_A);
    bool button_b_state = gpio_get(BUTTON_B);

    if (state == 0) question_loop();
    else answer_loop();

    last_button_a_state = button_a_state;
    last_button_b_state = button_b_state;
}

int main() {
    stdio_init_all();
    printf("starting raspberry pico");

    pins_setup();
    while (true) board_loop();
    return 0;
}
