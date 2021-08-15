#define EMPTY_RECTANGLE 0
#define FILLED_RECTANGLE 1
#define LEFT_PIPE 2
#define RIGHT_PIPE 3
#define TURN_INDICATOR 4

byte empty_rectangle[] = {
    B00000,
    B11111,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111,
    B00000
};

byte filled_rectangle[] = {
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000
};

byte left_pipe[] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};

byte right_pipe[] = {
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001
};

byte turn_indicator[] = {
    B00000,
    B00000,
    B01110,
    B11111,
    B11111,
    B01110,
    B00000,
    B00000
};

///Start flag image
byte customChar[] = {
  B10101,
  B01011,
  B10101,
  B01011,
  B00001,
  B00001,
  B00001,
  B00001
};
