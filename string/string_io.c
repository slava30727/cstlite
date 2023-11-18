String String_read_line(void) {
    String mut result = String_DEFAULT;

    for (char mut cur_char = getchar()
        ; cur_char != '\n'
        ; cur_char = getchar()
    ) {
        String_push(&mut result, cur_char);
    }

    return result;
}

void String_print(String const* const self) {
    for (usize mut i = 0; i < self->len; ++i) {
        putchar(self->ptr[i]);
    }
}