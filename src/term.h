#pragma once

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define TC_NOERR 0
#define TC_GET_ATTR_ERR 1
#define TC_SET_ATTR_ERR 2

int set_raw_mode();
int restore_mode(struct termios *original);
int save_original(struct termios *original);
