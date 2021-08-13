#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define LEFT_PLAYER_BUTTON A0
#define RIGHT_PLAYER_BUTTON A1
#define START_STOP_BUTTON A2
#define SOFT_RESET_BUTTON A3
#define OK_BUTTON A4

#define THIRTY_MINUTES 18000
#define NINETY_MINUTES 54000
#define ONE_MINUTE 600

typedef void (*mode_func)();

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
    STD, Speed
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

    unsigned long time_limit = THIRTY_MINUTES;  // In deciseconds
    bool show_deciseconds = false;

    Menu current_menu = Menu::Mode;
    GameMode game_mode = GameMode::STD;
};
