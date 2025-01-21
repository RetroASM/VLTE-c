#include <stdio.h>
#include "raw.h"
#include "editor.h"

int main(void) {
    struct termios original_settings;
    save_original(&original_settings);

    set_raw_mode();

    bool running = true;
    bool insert_mode = false;
    Editor editor = editor_new();
    while (running) {
        if (insert_mode) {
            // TODO: write to the buffer
            continue;
        }

        char key = '\x1b';
        read(STDIN_FILENO, &key, 1);
        switch (key) {
        case 'h':
            editor_move(&editor, 1, DIR_LEFT);
            break;
        case 'l':
            editor_move(&editor, 1, DIR_RIGHT);
            break;
        case 'k':
            editor_move(&editor, 1, DIR_UP);
            break;
        case 'j':
            editor_move(&editor, 1, DIR_DOWN);
            break;
        case '\x1b':
            running = false;
            break;
        default:
            printf("Unsupported key\n");
            break;
        }
    }

    restore_mode(&original_settings);
    return 0;
}
