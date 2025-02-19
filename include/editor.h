#include <stdio.h>
#include <stdlib.h>

// ANSI Escape code directions
typedef enum {
    DIR_UP = 'A',
    DIR_DOWN = 'B',
    DIR_RIGHT = 'C',
    DIR_LEFT = 'D'
} Direction;

// Controll Sequence Introducer command (CSI)
// To issue CSI we use \x1b[ followed:
// 1. any number (including zero) of "parameter bytes" from 0x30 to 0x3F ( 0-9;:;<=>? )
// 2. any number of "intermediate bytes" 0x20 to 0x2F ( !"#$%&'()*+,-./ )
// 3. finally by a single byte from 0x40 to 0x7E ( @A–Z[\]^_`a–z{|}~ )
//
// Parameters are separated by ; so to skip the middle parameter you would
// do 1;;3 or just 1;0;3
typedef struct {
    int row, col;
    int rows, cols;

    int should_update, running, insert_mode;

    char **buffer;
} Editor;

Editor editor_new(void);
void editor_free(Editor *self);

// move uses [n 'DIR'
// where n says how much to move
// and 'DIR' is A for Up
//              B for Down
//              C for Right
//              D for Left
// Example: \x1b[4D -> moves left by 4 chars
void editor_move(Editor *self, int amount, Direction dir);
void editor_write(Editor *self, char value);
void editor_update(Editor *self);
