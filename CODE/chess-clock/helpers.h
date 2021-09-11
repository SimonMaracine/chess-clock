#ifndef HELPERS_H
#define HELPERS_H

#include "definitions.h"

#define CHANGE_MODE(mode) \
    change_mode(mode); \
    return;

enum class Monotony {
    Ascend, Descend
};

struct Note
{
    int tone_value;
    int duration;
    int delay_value;
};

extern const char* ANIMATION[8];

extern const Note END_MELODY[4];
extern const Note START_MELODY[4];
extern const Note DICE_NOTE1[1];
extern const Note DICE_NOTE2[1];
extern const Note START_BEEP[1];
extern const Note GENTLE_RESET_BEEP[1];

void display_time(unsigned long player_time, Player player, bool show_deciseconds);
bool is_button_pressed(bool* button);
void change_mode(mode_func mode);
void display_time_one(unsigned long time, bool show_deciseconds);
void display_progress_bar(unsigned long time, unsigned long time_limit, Monotony monotony);
void make_sound(const Note* melody, int notes_count);
void toggle_light(bool on, int light);

#endif  // HELPERS_H
