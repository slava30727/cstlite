typedef struct Vec_u64 {
    u64 mut* ptr;
    usize len, cap;
} Vec_u64;

Vec_u64 Vec_u64_new(void) {
    return (Vec_u64) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_u64 Vec_u64_with_capacity(usize const cap) {
    return (Vec_u64) {
        .ptr = malloc(sizeof(u64) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_u64_free(Vec_u64 const* const self) {
    free(self->ptr);
    *(Vec_u64 mut*) self = Vec_u64_new();
}

void Vec_u64_push(Vec_u64 mut* const self, u64 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_u64_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(u64) * self->cap);
    }

    self->ptr[self->len++] = value;
}

u64 mut* Vec_u64_pop(Vec_u64 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(u64) * self->len--
        : null_mut;
}