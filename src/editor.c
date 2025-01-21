#include <stdio.h>
#include "editor.h"

Editor editor_new() {
    return (Editor) {
        .row = 0,
        .col = 0,
        .rows = 100,
        .cols = 100
    };
}

void editor_move(Editor *self, int amount, Direction dir) {
    int row = self->row; 
    if (dir == DIR_UP) {
        row--;
    } else if (dir == DIR_DOWN) {
        row++;
    }

    int col = self->col; 
    if (dir == DIR_LEFT) {
        col--;
    } else if (dir == DIR_RIGHT) {
        col++;
    }

    if (row > self->rows || col > self->cols) return;

    self->row = row;
    self->col = col;

    printf("\x1b[%d%c", amount, dir);
    fflush(stdout);
}
