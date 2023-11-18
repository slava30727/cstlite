typedef struct Vec_i8 {
    i8 mut* ptr;
    usize len, cap;
} Vec_i8;

Vec_i8 Vec_i8_new(void) {
    return (Vec_i8) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_i8 Vec_i8_with_capacity(usize const cap) {
    return (Vec_i8) {
        .ptr = malloc(sizeof(i8) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_i8_free(Vec_i8 const* const self) {
    free(self->ptr);
    *(Vec_i8 mut*) self = Vec_i8_new();
}

void Vec_i8_push(Vec_i8 mut* const self, i8 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_i8_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(i8) * self->cap);
    }

    self->ptr[self->len++] = value;
}

i8 mut* Vec_i8_pop(Vec_i8 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(i8) * self->len--
        : null_mut;
}