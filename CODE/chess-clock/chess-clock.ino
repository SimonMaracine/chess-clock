#include <LiquidCrystal.h>

#include "characters.h"
#include "definitions.h"
#include "modes.h"

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

unsigned long last_time = 0;  // In milliseconds

Buttons buttons;
GameState state;
mode_func current_mode;

void setup()
{
    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.createChar(EMPTY_RECTANGLE, empty_rectangle);
    lcd.createChar(FILLED_RECTANGLE, filled_rectangle);
    lcd.createChar(LEFT_PIPE, left_pipe);
    lcd.createChar(RIGHT_PIPE, right_pipe);
    lcd.createChar(TURN_INDICATOR, turn_indicator);
    lcd.createChar(START_FLAG, start_flag);
    lcd.createChar(UP_ARROW, up_arrow);
    lcd.createChar(DOWN_ARROW, down_arrow);

    // Set initial mode to startup
    current_mode = mode_startup;

    ///Set initial time setup in minutes
    state.set_time_in_seconds = false;
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
