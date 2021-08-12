///Check Windows and Linux line end compatibility with git

#include <LiquidCrystal.h>

#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define LEFT_PLAYER_BUTTON A0
#define RIGHT_PLAYER_BUTTON A1

struct Buttons
{
  // First - is currently pressed; second - was previously pressed
  bool left_player[2] = { false, false };
  bool right_player[2] = { false, false };
};

enum class Player
{
  Left, Right
};

byte EMPTY_RECTANGLE[] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000
};

byte FILLED_RECTANGLE[] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000
};

byte LEFT_PIPE[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};

byte RIGHT_PIPE[] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001
};

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

// In deciseconds; these shouldn't go past 59400
unsigned long left_player_time = 0;
unsigned long right_player_time = 0;

// In milliseconds
unsigned long last_time = 0;

Player player = Player::Left;

Buttons buttons;

void display_time(int x, int y, unsigned long player_time)
{
  const char ASCII_ZERO = '0';
  char output[8];  // Includes the null termination character

  const unsigned long player_time_seconds = player_time / 10.0f;
  
  const unsigned long minutes = player_time_seconds / 60;
  const unsigned long seconds = player_time_seconds % 60;
  const unsigned long deciseconds = player_time % 10;

  output[0] = ASCII_ZERO + minutes / 10;
  output[1] = ASCII_ZERO + minutes % 10;
  output[2] = ':';
  output[3] = ASCII_ZERO + seconds / 10;
  output[4] = ASCII_ZERO + seconds % 10;
  output[5] = '.';
  output[6] = ASCII_ZERO + deciseconds;

  output[7] = 0;

  lcd.setCursor(x, y);
  lcd.print(output);
}

bool is_button_pressed(bool* button)
{
  if (button[0] && !button[1])
    return true;
  else
    return false;
}

void setup()
{
  lcd.begin(16, 2);
  lcd.createChar(0, EMPTY_RECTANGLE);
  lcd.createChar(1, FILLED_RECTANGLE);
  lcd.createChar(2, LEFT_PIPE);
  lcd.createChar(3, RIGHT_PIPE);

  // Left player indicator
  lcd.setCursor(3, 0);
  lcd.write((byte) 0);

  // Right player indicator
  lcd.setCursor(12, 0);
  lcd.write((byte) 1);

  // Middle seperator
  lcd.setCursor(7, 0);
  lcd.write((byte) 3);
  lcd.setCursor(7, 1);
  lcd.write((byte) 3);
  
  lcd.setCursor(8, 0);
  lcd.write((byte) 2);
  lcd.setCursor(8, 1);
  lcd.write((byte) 2);
}

void loop()
{
  buttons.left_player[1] = buttons.left_player[0];
  buttons.left_player[0] = digitalRead(LEFT_PLAYER_BUTTON);
  buttons.right_player[1] = buttons.right_player[0];
  buttons.right_player[0] = digitalRead(RIGHT_PLAYER_BUTTON);

  if (is_button_pressed(buttons.left_player) && player == Player::Left)
  {
    player = Player::Right;
  }
  else if (is_button_pressed(buttons.right_player) && player == Player::Right)
  {
    player = Player::Left;
  }

  if (millis() - last_time > 100)
  {
    if (player == Player::Left)
      left_player_time++;
    else
      right_player_time++;

    last_time = millis();
  }

  display_time(0, 1, left_player_time);
  display_time(9, 1, right_player_time);

  delay(5);
}
