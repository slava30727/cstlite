typedef struct Vec_i16 {
    i16 mut* ptr;
    usize len, cap;
} Vec_i16;

Vec_i16 Vec_i16_new(void) {
    return (Vec_i16) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_i16 Vec_i16_with_capacity(usize const cap) {
    return (Vec_i16) {
        .ptr = malloc(sizeof(i16) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_i16_free(Vec_i16 const* const self) {
    free(self->ptr);
    *(Vec_i16 mut*) self = Vec_i16_new();
}

void Vec_i16_clear(Vec_i16 mut* const self) {
    self->len = 0;
}

void Vec_i16_push(Vec_i16 mut* const self, i16 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_i16_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(i16) * self->cap);
    }

    self->ptr[self->len++] = value;
}

i16 mut* Vec_i16_pop(Vec_i16 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(i16) * self->len--
        : null_mut;
}