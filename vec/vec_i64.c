typedef struct Vec_i64 {
    i64 mut* ptr;
    usize len, cap;
} Vec_i64;

Vec_i64 Vec_i64_new(void) {
    return (Vec_i64) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_i64 Vec_i64_with_capacity(usize const cap) {
    return (Vec_i64) {
        .ptr = malloc(sizeof(i64) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_i64_free(Vec_i64 const* const self) {
    free(self->ptr);
    *(Vec_i64 mut*) self = Vec_i64_new();
}

void Vec_i64_push(Vec_i64 mut* const self, i64 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_i64_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(i64) * self->cap);
    }

    self->ptr[self->len++] = value;
}

i64 mut* Vec_i64_pop(Vec_i64 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(i64) * self->len--
        : null_mut;
}