void setup_standard_game()
{
    state.left_player_time = 0;
    state.right_player_time = 0;

    state.player = Player::Right;

    state.start = false;
    state.game_end = false;
}

void setup_speed_game()
{
    state.left_player_time = state.time_limit;
    state.right_player_time = state.time_limit;

    state.player = Player::Right;

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
    lcd.print("By Simon & Tudor");
}

void mode_standard_game()
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
    lcd.write((byte) 0);

    // Right player indicator
    lcd.setCursor(15, 0);
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

    if (state.player == Player::Left)
    {
        lcd.setCursor(12, 0);
        lcd.print(' ');

        lcd.setCursor(3, 0);
        lcd.write((byte) 4);
    }
    else
    {
        lcd.setCursor(3, 0);
        lcd.print(' ');

        lcd.setCursor(12, 0);
        lcd.write((byte) 4);
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

void mode_speed_game()
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
    lcd.write((byte) 0);

    // Right player indicator
    lcd.setCursor(15, 0);
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

    if (state.player == Player::Left)
    {
        lcd.setCursor(12, 0);
        lcd.print(' ');

        lcd.setCursor(3, 0);
        lcd.write((byte) 4);
    }
    else
    {
        lcd.setCursor(3, 0);
        lcd.print(' ');

        lcd.setCursor(12, 0);
        lcd.write((byte) 4);
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
                    case GameMode::STD:
                        setup_standard_game();
                        change_mode(mode_standard_game);
                        return;
                    case GameMode::Speed:
                        setup_speed_game();
                        change_mode(mode_speed_game);
                        return;
                }
                break;
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
    lcd.print('S');

    lcd.setCursor((int) state.current_menu, 1);
    lcd.write((byte) 4);
}

void mode_modes()
{
    if (is_button_pressed(buttons.left_player))
    {
        switch (state.game_mode)
        {
            case GameMode::STD:
                state.game_mode = GameMode::Speed;
                break;
            case GameMode::Speed:
                state.game_mode = GameMode::STD;
                break;
        }
    }
    else if (is_button_pressed(buttons.right_player))
    {
        switch (state.game_mode)
        {
            case GameMode::STD:
                state.game_mode = GameMode::Speed;
                break;
            case GameMode::Speed:
                state.game_mode = GameMode::STD;
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
        case GameMode::STD:
            lcd.print("Standard Game   ");
            break;
        case GameMode::Speed:
            lcd.print("Speed Game      ");
            break;
    }
}

void mode_time()
{
    if (buttons.left_player[0] && state.time_limit > 600)
    {
        state.time_limit -= 600;
        delay(200);
    }
    
    if (buttons.right_player[0] && state.time_limit < 54000)
    {
        state.time_limit += 600;
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
    lcd.print(state.time_limit / 600);
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
