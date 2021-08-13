//void setup_speed_game()
//{
//    // Set to two minutes (for now)
//    state.left_player_time = 1200;
//    state.right_player_time = 1200;
//
//    state.player = Player::Right;
//}

void mode_startup()
{
//    if (is_button_pressed(buttons.left_player))
//    {
//        change_mode(mode_standard_game);
//        return;
//    }
//    else if (is_button_pressed(buttons.right_player))
//    {
//        change_mode(mode_speed_game);
//        setup_speed_game();
//        return;
//    }

    if (is_button_pressed(buttons.left_player) || is_button_pressed(buttons.right_player))
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

    if (state.start)
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
            state.start = false;
        }
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
    display_time(state.left_player_time, Player::Left, false);
    display_time(state.right_player_time, Player::Right, false);
}

void mode_speed_game()
{
    if (is_button_pressed(buttons.start_stop))
    {
        state.start = !state.start;
    }

    if (state.start)
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
            state.start = false;
        }
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
    display_time(state.left_player_time, Player::Left, false);
    display_time(state.right_player_time, Player::Right, false);
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
