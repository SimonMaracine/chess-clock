#include <Arduino.h>
#include <LiquidCrystal.h>

#include "definitions.h"
#include "modes.h"
#include "characters.h"
#include "helpers.h"

void mode_startup();
void mode_two_clock_up();
void mode_two_clock_down();
void mode_one_clock_up();
void mode_one_clock_down();
void mode_menu();
void mode_modes();
void mode_time();
void mode_deciseconds();

extern LiquidCrystal lcd;
extern unsigned long last_time;
extern Buttons buttons;
extern GameState state;
extern mode_func current_mode;

void setup_two_clock_up()
{
    state.left_player_time = 0;
    state.right_player_time = 0;

    state.player = Player::Right;

    state.start = false;
    state.game_end = false;
}

void setup_two_clock_down()
{
    state.left_player_time = state.time_limit;
    state.right_player_time = state.time_limit;

    state.player = Player::Right;

    state.start = false;
    state.game_end = false;
}

void setup_one_clock_up()
{
    state.right_player_time = 0;

    state.start = false;
    state.game_end = false;
}

void setup_one_clock_down()
{
    state.right_player_time = state.time_limit;

    state.start = false;
    state.game_end = false;
}

void mode_startup()
{
    if (buttons.left_player[0] || buttons.right_player[0] ||
        buttons.start_stop[0] || buttons.soft_reset[0] ||
        buttons.ok[0])
    {
        change_mode(mode_menu);
        return;
    }

    lcd.setCursor(0, 0);
    lcd.print("Chess Clock v1.0");
    lcd.setCursor(0, 1);
    lcd.print("By Tudor & Simon");
}

void mode_two_clock_up()
{
    if (is_button_pressed(buttons.start_stop))
    {
        state.start = !state.start;
    }

    if (state.start && !state.game_end)
    {
        if (is_button_pressed(buttons.left_player) && state.player == Player::Left)
        {
            state.player = Player::Right;
        }
        else if (is_button_pressed(buttons.right_player) && state.player == Player::Right)
        {
            state.player = Player::Left;
        }

        if (millis() - last_time > 100)
        {
            if (state.player == Player::Left)
                state.left_player_time++;
            else
                state.right_player_time++;

            last_time = millis();
        }

        if (state.left_player_time == state.time_limit ||
                state.right_player_time == state.time_limit)
        {
            state.game_end = true;
        }
    }

    if (is_button_pressed(buttons.soft_reset))
    {
        change_mode(mode_menu);
        return;
    }

    // Left player indicator
    lcd.setCursor(0, 0);
    lcd.write((byte) EMPTY_RECTANGLE);

    // Right player indicator
    lcd.setCursor(15, 0);
    lcd.write((byte) FILLED_RECTANGLE);

    // Middle seperator
    lcd.setCursor(7, 0);
    lcd.write((byte) RIGHT_PIPE);
    lcd.setCursor(7, 1);
    lcd.write((byte) RIGHT_PIPE);

    lcd.setCursor(8, 0);
    lcd.write((byte) LEFT_PIPE);
    lcd.setCursor(8, 1);
    lcd.write((byte) LEFT_PIPE);

    if (state.player == Player::Left)
    {
        lcd.setCursor(12, 0);
        lcd.print(' ');

        lcd.setCursor(3, 0);
        lcd.write((byte) TURN_INDICATOR);
    }
    else
    {
        lcd.setCursor(3, 0);
        lcd.print(' ');

        lcd.setCursor(12, 0);
        lcd.write((byte) TURN_INDICATOR);
    }

    // Player times
    if (state.show_deciseconds)
    {
        display_time(state.left_player_time, Player::Left, true);
        display_time(state.right_player_time, Player::Right, true);
    }
    else
    {
        display_time(state.left_player_time, Player::Left, false);
        display_time(state.right_player_time, Player::Right, false);
    }
}

void mode_two_clock_down()
{
    if (is_button_pressed(buttons.start_stop))
    {
        state.start = !state.start;
    }

    if (state.start && !state.game_end)
    {
        if (is_button_pressed(buttons.left_player) && state.player == Player::Left)
        {
            state.player = Player::Right;
        }
        else if (is_button_pressed(buttons.right_player) && state.player == Player::Right)
        {
            state.player = Player::Left;
        }

        if (millis() - last_time > 100)
        {
            if (state.player == Player::Left)
                state.left_player_time--;
            else
                state.right_player_time--;

            last_time = millis();
        }

        if (state.left_player_time == 0 || state.right_player_time == 0)
        {
            state.game_end = true;
        }
    }

    if (is_button_pressed(buttons.soft_reset))
    {
        change_mode(mode_menu);
        return;
    }

    // Left player indicator
    lcd.setCursor(0, 0);
    lcd.write((byte) EMPTY_RECTANGLE);

    // Right player indicator
    lcd.setCursor(15, 0);
    lcd.write((byte) FILLED_RECTANGLE);

    // Middle seperator
    lcd.setCursor(7, 0);
    lcd.write((byte) RIGHT_PIPE);
    lcd.setCursor(7, 1);
    lcd.write((byte) RIGHT_PIPE);

    lcd.setCursor(8, 0);
    lcd.write((byte) LEFT_PIPE);
    lcd.setCursor(8, 1);
    lcd.write((byte) LEFT_PIPE);

    if (state.player == Player::Left)
    {
        lcd.setCursor(12, 0);
        lcd.print(' ');

        lcd.setCursor(3, 0);
        lcd.write((byte) TURN_INDICATOR);
    }
    else
    {
        lcd.setCursor(3, 0);
        lcd.print(' ');

        lcd.setCursor(12, 0);
        lcd.write((byte) TURN_INDICATOR);
    }

    // Player times
    if (state.show_deciseconds)
    {
        display_time(state.left_player_time, Player::Left, true);
        display_time(state.right_player_time, Player::Right, true);
    }
    else
    {
        display_time(state.left_player_time, Player::Left, false);
        display_time(state.right_player_time, Player::Right, false);
    }
}

void mode_one_clock_up()
{
    if (is_button_pressed(buttons.start_stop) ||
        is_button_pressed(buttons.left_player) ||
        is_button_pressed(buttons.right_player))
    {
        state.start = !state.start;
    }
    else if (is_button_pressed(buttons.ok))
    {
        state.start = false;
        state.game_end = false;
        state.right_player_time = 0;
    }

    if (state.start && !state.game_end)
    {
        if (millis() - last_time > 100)
        {
            state.right_player_time++;

            last_time = millis();
        }

        if (state.right_player_time == state.time_limit)
        {
            state.game_end = true;
        }
    }

    if (is_button_pressed(buttons.soft_reset))
    {
        change_mode(mode_menu);
        return;
    }

    if (state.show_deciseconds)
    {
        display_time_one(state.right_player_time, true);
    }
    else
    {
        display_time_one(state.right_player_time, false);
    }
}

void mode_one_clock_down()
{
    if (is_button_pressed(buttons.start_stop) ||
        is_button_pressed(buttons.left_player) ||
        is_button_pressed(buttons.right_player))
    {
        state.start = !state.start;
    }
    else if (is_button_pressed(buttons.ok))
    {
        state.start = false;
        state.game_end = false;
        state.right_player_time = state.time_limit;
    }

    if (state.start && !state.game_end)
    {
        if (millis() - last_time > 100)
        {
            state.right_player_time--;

            last_time = millis();
        }

        if (state.right_player_time == 0)
        {
            state.game_end = true;
        }
    }

    if (is_button_pressed(buttons.soft_reset))
    {
        change_mode(mode_menu);
        return;
    }

    if (state.show_deciseconds)
    {
        display_time_one(state.right_player_time, true);
    }
    else
    {
        display_time_one(state.right_player_time, false);
    }
}

void mode_menu()
{
    if (is_button_pressed(buttons.left_player))
    {
        lcd.setCursor((int) state.current_menu, 1);
        lcd.print(' ');

        if (state.current_menu == Menu::Mode)
        {
            state.current_menu = Menu::Start;
        }
        else
        {
            state.current_menu = (Menu) ((int) state.current_menu - 4);
        }
    }
    else if (is_button_pressed(buttons.right_player))
    {
        lcd.setCursor((int) state.current_menu, 1);
        lcd.print(' ');

        if (state.current_menu == Menu::Start)
        {
            state.current_menu = Menu::Mode;
        }
        else
        {
            state.current_menu = (Menu) ((int) state.current_menu + 4);
        }
    }
    else if (is_button_pressed(buttons.ok))
    {
        switch (state.current_menu)
        {
            case Menu::Mode:
                change_mode(mode_modes);
                return;
            case Menu::Time:
                change_mode(mode_time);
                return;
            case Menu::Deciseconds:
                change_mode(mode_deciseconds);
                return;
            case Menu::Start:
                switch (state.game_mode)
                {
                    case GameMode::TwoClockUp:
                        setup_two_clock_up();
                        change_mode(mode_two_clock_up);
                        return;
                    case GameMode::TwoClockDown:
                        setup_two_clock_down();
                        change_mode(mode_two_clock_down);
                        return;
                    case GameMode::OneClockUp:
                        setup_one_clock_up();
                        change_mode(mode_one_clock_up);
                        return;
                    case GameMode::OneClockDown:
                        setup_one_clock_down();
                        change_mode(mode_one_clock_down);
                        return;
                }
        }
    }

    lcd.setCursor(3, 0);
    lcd.print("Setup Menu");

    lcd.setCursor(1, 1);
    lcd.print('M');
    lcd.setCursor(5, 1);
    lcd.print('T');
    lcd.setCursor(9, 1);
    lcd.print('D');
    lcd.setCursor(13, 1);
    lcd.write((byte) START_FLAG);

    lcd.setCursor((int) state.current_menu, 1);
    lcd.write((byte) TURN_INDICATOR);
}

void mode_modes()
{
    if (is_button_pressed(buttons.left_player))
    {
        switch (state.game_mode)
        {
            case GameMode::TwoClockUp:
                state.game_mode = GameMode::OneClockDown;
                break;
            case GameMode::TwoClockDown:
                state.game_mode = GameMode::TwoClockUp;
                break;
            case GameMode::OneClockUp:
                state.game_mode = GameMode::TwoClockDown;
                break;
            case GameMode::OneClockDown:
                state.game_mode = GameMode::OneClockUp;
                break;
        }
    }
    else if (is_button_pressed(buttons.right_player))
    {
        switch (state.game_mode)
        {
            case GameMode::TwoClockUp:
                state.game_mode = GameMode::TwoClockDown;
                break;
            case GameMode::TwoClockDown:
                state.game_mode = GameMode::OneClockUp;
                break;
            case GameMode::OneClockUp:
                state.game_mode = GameMode::OneClockDown;
                break;
            case GameMode::OneClockDown:
                state.game_mode = GameMode::TwoClockUp;
                break;
        }
    }
    else if (is_button_pressed(buttons.ok))
    {
        change_mode(mode_menu);
        return;
    }

    lcd.setCursor(0, 0);
    lcd.print("Set Game Mode:");

    lcd.setCursor(0, 1);
    switch (state.game_mode)
    {
        case GameMode::TwoClockUp:
            lcd.print("Two Clock ");
            lcd.write((byte) UP_ARROW);
            break;
        case GameMode::TwoClockDown:
            lcd.print("Two Clock ");
            lcd.write((byte) DOWN_ARROW);
            break;
        case GameMode::OneClockUp:
            lcd.print("One Clock ");
            lcd.write((byte) UP_ARROW);
            break;
        case GameMode::OneClockDown:
            lcd.print("One Clock ");
            lcd.write((byte) DOWN_ARROW);
            break;
    }
}

void mode_time()
{
    if (buttons.left_player[0] && state.time_limit > ONE_MINUTE)
    {
        state.time_limit -= ONE_MINUTE;
        delay(200);
    }

    if (buttons.right_player[0] && state.time_limit < NINETY_MINUTES)
    {
        state.time_limit += ONE_MINUTE;
        delay(200);
    }

    if (is_button_pressed(buttons.ok))
    {
        change_mode(mode_menu);
        return;
    }

    lcd.setCursor(0, 0);
    lcd.print("Set Time Limit:");

    lcd.setCursor(0, 1);
    lcd.print(state.time_limit / ONE_MINUTE);
    lcd.print(" ");
}

void mode_deciseconds()
{
    if (is_button_pressed(buttons.left_player))
    {
        state.show_deciseconds = !state.show_deciseconds;
    }
    else if (is_button_pressed(buttons.right_player))
    {
        state.show_deciseconds = !state.show_deciseconds;
    }
    else if (is_button_pressed(buttons.ok))
    {
        change_mode(mode_menu);
        return;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Show Deciseconds:");

    lcd.setCursor(0, 1);
    if (state.show_deciseconds)
        lcd.print("On ");
    else
        lcd.print("Off");
}
