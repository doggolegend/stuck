#pragma once

#include "stdint.h"

void print_string(char* str);
void clear_screen();
void new_line();
void print_char(char character);
uint16_t get_cursor_position();
void update_cursor(int x, int y);

// KERNEL PANIC CONTROLLER BELOW
void panic_clear_row();
void panic_clear_screen();
void panic_print_char(char character);
void panic_print_string(char* str);

// SYSTEM REPORTS CONTROLLER BELOW
void system_print_char(char character, int colour);
void system_print_string(char* str, int colour);
