typedef void (*mode_func)();

enum class Player
{
    Left, Right
};

enum class Menu
{
    Mode = 2,
    Time = 6,
    Deciseconds= 10,
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
    // In deciseconds; these shouldn't go past 59400
    unsigned long left_player_time = 0;
    unsigned long right_player_time = 0;

    // Right player starts (white player)
    Player player = Player::Right;

    bool start = false;
    bool game_end = false;

    unsigned long time_limit = 18000;  // In deciseconds

    Menu current_menu = Menu::Mode;
    GameMode game_mode = GameMode::STD;
    bool show_deciseconds = false;
};
