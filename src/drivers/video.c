#include "video.h"
#include "stdint.h"
#include "IO.h"

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int col;
int row;

void increment_cursor()
{
    // //fake_curmem_pos += 2;
    col++;

    update_cursor(col, row);
}


void clear_row()
{
    col = 0;

    for (int cols = 0; cols < VGA_WIDTH; cols++)
    {
        int curpos = get_cursor_position();
        int location = 0xb8000+curpos*2;
        int locationColour = 0xb8000+curpos*2+1;

        *(char*)location = ' ';
        *(char*)locationColour = 0x1F;  // white text on light blue background
        increment_cursor();
    }

    //new_line();
}

void scroll()
{
    for (int y = 0; y < VGA_HEIGHT - 1; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            int old_position = (y * VGA_WIDTH + x) * 2;
            int new_position = ((y + 1) * VGA_WIDTH + x) * 2;

            *(char*)(0xb8000 + old_position) = *(char*)(0xb8000 + new_position);
            *(char*)(0xb8000 + old_position + 1) = *(char*)(0xb8000 + new_position + 1);
        }
    }

    row = VGA_HEIGHT - 1;
    col = 0;
    update_cursor(col, row);
    clear_row();

    row = VGA_HEIGHT - 1;
    col = 0;
    update_cursor(col, row);
}


void new_line()
{
    col = 0;

    if (row < VGA_HEIGHT - 1)
    {
        row++;
        update_cursor(col, row);
        return;
    }
    else
    {
        scroll();
    }
}

void clear_screen()
{
    for (int rows = 0; rows < VGA_HEIGHT; rows++)
    {
        col = 0;
        row = rows;
        update_cursor(col, row);
        clear_row();
    }
    col = 0;
    row = 0;
    update_cursor(col, row);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	port_byte_write(0x3D4, 0x0F);
	port_byte_write(0x3D5, (uint8_t) (pos & 0xFF));
	port_byte_write(0x3D4, 0x0E);
	port_byte_write(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t get_cursor_position(void)
{
    uint16_t pos = 0;
    port_byte_write(0x3D4, 0x0F);
    pos |= port_byte_read(0x3D5);
    port_byte_write(0x3D4, 0x0E);
    pos |= ((uint16_t)port_byte_read(0x3D5)) << 8;
    return pos;
}

void print_char(char character)
{
    int curpos = get_cursor_position();
    int location = 0xb8000+curpos*2;
    int locationColour = 0xb8000+curpos*2+1;

    *(char*)location = character;
    *(char*)locationColour = 0x1F;  // white text on light blue background

    increment_cursor();
}

void print_string(char* str)
{
    for (int i = 0; 1; i++)
    {
        char character = (uint8_t) str[i];

        if (character == '\0')
        {
            return;
        }

        if (character == '\n')
        {
            new_line();
            continue;
        }

        print_char(character);
    }
}


// KERNEL PANIC VIDEO CONTROLLER BELOW

void panic_clear_row()
{
    col = 0;

    for (int cols = 0; cols < VGA_WIDTH; cols++)
    {
        int curpos = get_cursor_position();
        int location = 0xb8000+curpos*2;
        int locationColour = 0xb8000+curpos*2+1;

        *(char*)location = ' ';
        *(char*)locationColour = 0x4F;  // white text on red background
        increment_cursor();
    }

    //new_line();
}

void panic_clear_screen()
{
    for (int rows = 0; rows < VGA_HEIGHT; rows++)
    {
        col = 0;
        row = rows;
        update_cursor(col, row);
        panic_clear_row();
    }
    col = 0;
    row = 0;
    update_cursor(col, row);
}

void panic_print_char(char character)
{
    int curpos = get_cursor_position();
    int location = 0xb8000+curpos*2;
    int locationColour = 0xb8000+curpos*2+1;

    *(char*)location = character;
    *(char*)locationColour = 0x4F;  // white text on red background

    increment_cursor();
}

void panic_print_string(char* str)
{
    for (int i = 0; 1; i++)
    {
        char character = (uint8_t) str[i];

        if (character == '\0')
        {
            return;
        }

        if (character == '\n')
        {
            new_line();
            continue;
        }

        panic_print_char(character);
    }
}

// SYSTEM REPORTS CONTROLLER BELOW

void system_print_char(char character, int colour)
{
    int curpos = get_cursor_position();
    int location = 0xb8000+curpos*2;
    int locationColour = 0xb8000+curpos*2+1;

    *(char*)location = character;

    if (colour == 1)
    {
        *(char*)locationColour = 0x1A;  // green text on light blue background
    }
    else if (colour == 2)
    {
        *(char*)locationColour = 0x1E;  // yellow text on light blue background
    }
    else
    {
        *(char*)locationColour = 0x1A;  // green text on light blue background for else default
    }
    

    increment_cursor();
}

void system_print_string(char* str, int colour)
{
    for (int i = 0; 1; i++)
    {
        char character = (uint8_t) str[i];

        if (character == '\0')
        {
            return;
        }

        if (character == '\n')
        {
            new_line();
            continue;
        }

        system_print_char(character, colour);
    }
}