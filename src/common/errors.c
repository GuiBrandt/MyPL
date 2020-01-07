#include <common/errors.h>

static mypl_error_code last_error = MYPL_ERR_OK;
static const char* last_error_message = 0;

void mypl_set_last_error(mypl_error_code code, const char* message) {
    last_error = code;
    last_error_message = message;
}

mypl_error_code __mypl_last_error() {
    return last_error;
}

const char* __mypl_last_error_message() {
    return last_error_message;
}