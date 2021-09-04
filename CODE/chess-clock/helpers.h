#ifndef HELPERS_H
#define HELPERS_H

#include "definitions.h"

#define CHANGE_MODE(mode) \
    change_mode(mode); \
    return;

enum class Monotony {
    Ascend, Descend
};

extern const char* ANIMATION[8];

void display_time(unsigned long player_time, Player player, bool show_deciseconds);
bool is_button_pressed(bool* button);
void change_mode(mode_func mode);
void display_time_one(unsigned long time, bool show_deciseconds);
void display_progress_bar(unsigned long time, unsigned long time_limit, Monotony monotony);

#endif  // HELPERS_H
