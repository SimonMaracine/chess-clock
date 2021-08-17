#ifndef HELPERS_H
#define HELPERS_H

void display_time(unsigned long player_time, Player player, bool show_deciseconds);
bool is_button_pressed(bool* button);
void change_mode(mode_func mode);
void display_time_one(unsigned long time, bool show_deciseconds);

#endif  // HELPERS_H
