#include "../include/editor.h"

Editor editor_new(void) {
    const int ROWS = 60, COLS = 100;

    char **buff = (char **)calloc((size_t)ROWS, sizeof(char*));
    for (int i = 0; i < ROWS; i++) {
        buff[i] = (char *)calloc((size_t)COLS, sizeof(char));
    }

    return (Editor) {
        .should_update = 1,
        .insert_mode = 0,
        .running = 1,
        .buffer = buff,
        .row = 0,
        .col = 0,
        .rows = ROWS,
        .cols = COLS
    };
}

void editor_free(Editor *self) {
    int i = 0;
    for (i = 0; i < self->rows; i++) {
        free(self->buffer[i]);
    }
    free(self->buffer);

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

void editor_write(Editor *self, char value) {
    if (self->col >= self->cols) return;
    self->should_update = 1;

    self->buffer[self->row][self->col] = value;
    self->col++;
}

void editor_update(Editor *self) {
        self->should_update = 0;

        // clear screen
        printf("\x1b[2J");
        printf("UPDATE\n");

        for (int i = 0; i < self->rows; i++) {
            for (int j = 0; j < self->cols; j++) {
                // printf("%c", self->buffer[i][j]);
            }
        }

        fflush(stdout);
}
