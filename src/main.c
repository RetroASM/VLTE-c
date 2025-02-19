#include "../include/editor.h"
#include "../include/raw.h"

int main(void) {
    struct termios original_settings;
    save_original(&original_settings);

    set_raw_mode();

    Editor editor = editor_new();
    while (editor.running) {
        if (editor.should_update == 1) {
            editor_update(&editor);
        }

        if (editor.insert_mode) {
            char key = '\x1b';
            read(STDIN_FILENO, &key, 1);
            switch (key) {
            case '\x1b':
                editor.insert_mode = 0;
                break;
            default:
                editor_write(&editor, key);
                break;
            }

            continue;
        }


        // NORMAL MODE
        char key = '\x1b';
        read(STDIN_FILENO, &key, 1);
        switch (key) {
        case 'i':
            editor.insert_mode = 1;
            break;
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
        default:
            break;
        }
    }

    restore_mode(&original_settings);
    editor_free(&editor);
}
