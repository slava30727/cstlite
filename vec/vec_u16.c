typedef struct Vec_u16 {
    u16 mut* ptr;
    usize len, cap;
} Vec_u16;

Vec_u16 Vec_u16_new(void) {
    return (Vec_u16) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_u16 Vec_u16_with_capacity(usize const cap) {
    return (Vec_u16) {
        .ptr = malloc(sizeof(u16) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_u16_free(Vec_u16 const* const self) {
    free(self->ptr);
    *(Vec_u16 mut*) self = Vec_u16_new();
}

void Vec_u16_clear(Vec_u16 mut* const self) {
    self->len = 0;
}

void Vec_u16_push(Vec_u16 mut* const self, u16 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_u16_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(u16) * self->cap);
    }

    self->ptr[self->len++] = value;
}

u16 mut* Vec_u16_pop(Vec_u16 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(u16) * --self->len
        : null_mut;
}