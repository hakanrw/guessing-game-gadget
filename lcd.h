/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef LCD_H
#define LCD_H

#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include <pico/binary_info.h>

void i2c_write_byte(uint8_t val);

void lcd_toggle_enable(uint8_t val);

void lcd_send_byte(uint8_t val, int mode);

void lcd_clear(void);

void lcd_set_cursor(int line, int position);

void lcd_string(const char *s);

void lcd_init();

#endif // !LCD_H