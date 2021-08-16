#ifndef HELPERS_H
#define HELPERS_H

void display_time(unsigned long player_time, Player player, bool show_deciseconds);
bool is_button_pressed(bool* button);
void change_mode(mode_func mode);

#endif  // HELPERS_H
