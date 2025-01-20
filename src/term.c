#include "term.h"

int set_raw_mode() {
    struct termios raw;

    if (tcgetattr(STDIN_FILENO, &raw) == -1) {
        return TC_GET_ATTR_ERR;
    }

    // Disable echo and canonical mode
    raw.c_lflag &= ~(ECHO | ICANON);

    // Min chars to read
    raw.c_cc[VMIN] = 1;

    // No timeout
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        return TC_SET_ATTR_ERR;
    }

    return TC_NOERR;
}

int restore_mode(struct termios *original) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, original) == -1) {
        return TC_SET_ATTR_ERR;
    }
    return TC_NOERR;
}

int save_original(struct termios *original) {
    if (tcgetattr(STDIN_FILENO, original) == -1) {
        return TC_GET_ATTR_ERR;
    }
    return TC_NOERR;
}
