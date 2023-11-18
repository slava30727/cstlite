typedef struct Vec_u8 {
    u8 mut* ptr;
    usize len, cap;
} Vec_u8;

Vec_u8 Vec_u8_new(void) {
    return (Vec_u8) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_u8 Vec_u8_with_capacity(usize const cap) {
    return (Vec_u8) {
        .ptr = malloc(sizeof(u8) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_u8_free(Vec_u8 const* const self) {
    free(self->ptr);
    *(Vec_u8 mut*) self = Vec_u8_new();
}

void Vec_u8_clear(Vec_u8 mut* const self) {
    self->len = 0;
}

void Vec_u8_push(Vec_u8 mut* const self, u8 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_u8_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(u8) * self->cap);
    }

    self->ptr[self->len++] = value;
}

u8 mut* Vec_u8_pop(Vec_u8 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(u8) * --self->len
        : null_mut;
}