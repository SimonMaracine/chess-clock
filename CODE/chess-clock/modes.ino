void setup_speed_game()
{
  // Set to two minutes (for now)
  state.left_player_time = 1200;
  state.left_player_time = 1200;
  
  state.player = Player::Right;
}

void mode_startup()
{
  if (is_button_pressed(buttons.left_player))
  {
    change_mode(mode_standard_game);
    return;
  }
  else if (is_button_pressed(buttons.right_player))
  {
    change_mode(mode_speed_game);
    setup_speed_game();
    return;
  }

//  if (is_button_pressed(buttons.left_player) || is_button_pressed(buttons.right_player))
//  {
//    change_mode(mode_menu);
//    return;
//  }

  lcd.setCursor(0, 0);
  lcd.print("Chess Clock");
  lcd.setCursor(0, 1);
  lcd.print("By Simon & Tudor");
}

void mode_standard_game()
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

  // Player times
  display_time(state.left_player_time, Player::Left, false);
  display_time(state.right_player_time, Player::Right, false);
}

void mode_speed_game()
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

  // Player times
  display_time(state.left_player_time, Player::Left, false);
  display_time(state.right_player_time, Player::Right, false);
}