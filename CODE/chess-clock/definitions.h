#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define BUZZER 9
#define LEFT_LED 11
#define RIGHT_LED 10

#define LEFT_PLAYER_BUTTON A0
#define RIGHT_PLAYER_BUTTON A1
#define START_STOP_BUTTON A2
#define SOFT_RESET_BUTTON A3
#define OK_BUTTON A4

#define NINETY_MINUTES 54000
#define THIRTY_MINUTES 18000
#define THREE_MINUTES 1800
#define ONE_MINUTE 600 
#define ONE_SECOND 10

#define DEGREE_SIGN 176

enum class Player
{
    Left, Right
};

enum class Menu
{
    Mode = 2,
    Time = 6,
    Deciseconds = 10,
    Start = 14
};

enum class GameMode
{
    TwoClockUp,
    TwoClockDown,
    OneClockUp,
    OneClockDown,
    Dice
};

enum class TimeMode
{
    Minutes, Seconds  
};

struct Buttons
{
    // First - is currently pressed; second - was previously pressed
    bool left_player[2] = { false, false };
    bool right_player[2] = { false, false };
    bool start_stop[2] = { false, false };
    bool soft_reset[2] = { false, false };
    bool ok[2] = { false, false };
};

struct GameState
{
    // In deciseconds; these shouldn't go past 54000 (90 minutes)
    unsigned long left_player_time = 0;
    unsigned long right_player_time = 0;

    // Right player starts (white player)
    Player player = Player::Right;

    bool start = false;
    bool game_end = false;
    bool make_sound = true;

    bool set_time_in_seconds = false;
    TimeMode last_time_mode = TimeMode::Minutes;

    unsigned long time_limit = THIRTY_MINUTES;  // In deciseconds
    bool show_deciseconds = false;

    int dice_number;
    int dice[2];

//    bool leds[2] = { false, false };

    Menu current_menu = Menu::Mode;
    GameMode game_mode = GameMode::TwoClockUp;
};

typedef void (*mode_func)();

#endif  // DEFINITIONS_H
