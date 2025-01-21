#pragma once

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>


typedef enum {
    TC_NOERR = 1,
    TC_GET_ATTR_ERR = 2,
    TC_SET_ATTR_ERR = 3
} TC_ERR ;

TC_ERR set_raw_mode();
TC_ERR restore_mode(struct termios *original);
TC_ERR save_original(struct termios *original);
