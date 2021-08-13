typedef void (*mode_func)();

enum class Player
{
  Left, Right
};

struct Buttons
{
  // First - is currently pressed; second - was previously pressed
  bool left_player[2] = { false, false };
  bool right_player[2] = { false, false };
};

struct GameState
{
  // In deciseconds; these shouldn't go past 59400
  unsigned long left_player_time = 0;
  unsigned long right_player_time = 0;

  // Right player starts (white player)
  Player player = Player::Right;
};
