typedef struct Vec_char {
    char mut* ptr;
    usize len, cap;
} Vec_char;

Vec_char Vec_char_new(void) {
    return (Vec_char) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_char Vec_char_with_capacity(usize const cap) {
    return (Vec_char) {
        .ptr = malloc(sizeof(char) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_char_free(Vec_char const* const self) {
    free(self->ptr);
    *(Vec_char mut*) self = Vec_char_new();
}

void Vec_char_clear(Vec_char mut* const self) {
    self->len = 0;
}

void Vec_char_push(Vec_char mut* const self, char const value) {
    if (null_mut == self->ptr) {
        *self = Vec_char_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(char) * self->cap);
    }

    self->ptr[self->len++] = value;
}

char mut* Vec_char_pop(Vec_char mut* const self) {
    return 0 < self->len
        ? (self->ptr + sizeof(char) * self->len--)
        : null_mut;
}