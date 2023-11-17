#include <stdio.h>

#include "string.c"



String String_read_line(void) {
    String mut result;

    for (char mut cur_char = getchar()
        ; cur_char != '\n'
        ; cur_char = getchar()
    ) {
        String_push(&mut result, cur_char);
    }

    return result;
}