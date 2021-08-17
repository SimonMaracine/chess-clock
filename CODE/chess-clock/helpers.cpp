#include <Arduino.h>
#include <LiquidCrystal.h>

#include "helpers.h"
#include "definitions.h"
#include "characters.h"

extern LiquidCrystal lcd;
extern mode_func current_mode;

void display_time(unsigned long player_time, Player player, bool show_deciseconds)
{
    const char ASCII_ZERO = '0';
    char output[8];  // Includes the null termination character
    int x_position;

    const unsigned long player_time_seconds = player_time / 10.0f;

    const unsigned long minutes = player_time_seconds / 60;
    const unsigned long seconds = player_time_seconds % 60;
    const unsigned long deciseconds = player_time % 10;

    output[0] = ASCII_ZERO + minutes / 10;
    output[1] = ASCII_ZERO + minutes % 10;
    output[2] = ':';
    output[3] = ASCII_ZERO + seconds / 10;
    output[4] = ASCII_ZERO + seconds % 10;
  
    if (show_deciseconds)
    {
        output[5] = '.';
        output[6] = ASCII_ZERO + deciseconds;
        output[7] = 0;
    }
    else
    {
        output[5] = 0;
        // The rest of output doesn't matter
    }

    if (player == Player::Left)
        x_position = 0;
    else
        x_position = 9;

    if (!show_deciseconds)
        x_position++;

    lcd.setCursor(x_position, 1);
    lcd.print(output);
}

bool is_button_pressed(bool* button)
{
    if (button[0] && !button[1])
        return true;
    else
        return false;
}

void change_mode(mode_func mode)
{
    lcd.clear();
    current_mode = mode;
}

void display_time_one(unsigned long time, bool show_deciseconds)
{
    const char ASCII_ZERO = '0';
    char output[8];  // Includes the null termination character
    int x_position;

    const unsigned long player_time_seconds = time / 10.0f;

    const unsigned long minutes = player_time_seconds / 60;
    const unsigned long seconds = player_time_seconds % 60;
    const unsigned long deciseconds = time % 10;

    output[0] = ASCII_ZERO + minutes / 10;
    output[1] = ASCII_ZERO + minutes % 10;
    output[2] = ':';
    output[3] = ASCII_ZERO + seconds / 10;
    output[4] = ASCII_ZERO + seconds % 10;

    if (show_deciseconds)
    {
        output[5] = '.';
        output[6] = ASCII_ZERO + deciseconds;
        output[7] = 0;
    }
    else
    {
        output[5] = 0;
        // The rest of output doesn't matter
    }

    if (!show_deciseconds)
        x_position = 5;
    else
        x_position = 4;

    lcd.setCursor(x_position, 1);
    lcd.print(output);
}

void display_progress_bar(unsigned long time, unsigned long time_limit, Monotony monotony)
{
    const int NUM_CELLS = 16;
    int cells_filled;

    if (monotony == Monotony::Ascend)
    {
        int value = map(time_limit - time, time_limit, 0, 0, time_limit);
        cells_filled = map(value, 0, time_limit, 0, NUM_CELLS);
    }
    else
    {
        cells_filled = map(time_limit - time, 0, time_limit, 0, NUM_CELLS);
    }

    lcd.setCursor(0, 0);
    for (int i = 0; i < cells_filled; i++)
    {
        lcd.write((byte) FILLED_RECTANGLE);
    }
}
