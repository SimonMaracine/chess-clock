#include <LiquidCrystal.h>

#include "characters.h"
#include "definitions.h"

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

unsigned long last_time = 0;  // In milliseconds

Buttons buttons;
GameState state;
mode_func current_mode;

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

void setup()
{
    Serial.begin(9600);
    
    lcd.begin(16, 2);
    lcd.createChar(EMPTY_RECTANGLE, empty_rectangle);
    lcd.createChar(FILLED_RECTANGLE, filled_rectangle);
    lcd.createChar(LEFT_PIPE, left_pipe);
    lcd.createChar(RIGHT_PIPE, right_pipe);
    lcd.createChar(TURN_INDICATOR, turn_indicator);

    // Set initial mode to startup
    current_mode = mode_startup;
}

void loop()
{
    buttons.left_player[1] = buttons.left_player[0];
    buttons.left_player[0] = digitalRead(LEFT_PLAYER_BUTTON);
    buttons.right_player[1] = buttons.right_player[0];
    buttons.right_player[0] = digitalRead(RIGHT_PLAYER_BUTTON);
    buttons.start_stop[1] = buttons.start_stop[0];
    buttons.start_stop[0] = digitalRead(START_STOP_BUTTON);
    buttons.soft_reset[1] = buttons.soft_reset[0];
    buttons.soft_reset[0] = digitalRead(SOFT_RESET_BUTTON);
    buttons.ok[1] = buttons.ok[0];
    buttons.ok[0] = digitalRead(OK_BUTTON);

    current_mode();

    delay(5);
}
