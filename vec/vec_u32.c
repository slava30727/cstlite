typedef struct Vec_u32 {
    u32 mut* ptr;
    usize len, cap;
} Vec_u32;

Vec_u32 Vec_u32_new(void) {
    return (Vec_u32) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_u32 Vec_u32_with_capacity(usize const cap) {
    return (Vec_u32) {
        .ptr = malloc(sizeof(u32) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_u32_free(Vec_u32 const* const self) {
    free(self->ptr);
    *(Vec_u32 mut*) self = Vec_u32_new();
}

void Vec_u32_clear(Vec_u32 mut* const self) {
    self->len = 0;
}

void Vec_u32_push(Vec_u32 mut* const self, u32 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_u32_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(u32) * self->cap);
    }

    self->ptr[self->len++] = value;
}

u32 mut* Vec_u32_pop(Vec_u32 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(u32) * --self->len
        : null_mut;
}