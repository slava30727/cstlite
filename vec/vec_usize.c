typedef struct Vec_usize {
    usize mut* ptr;
    usize len, cap;
} Vec_usize;

Vec_usize Vec_usize_new(void) {
    return (Vec_usize) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_usize Vec_usize_with_capacity(usize const cap) {
    return (Vec_usize) {
        .ptr = malloc(sizeof(usize) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_usize_free(Vec_usize const* const self) {
    free(self->ptr);
    *(Vec_usize mut*) self = Vec_usize_new();
}

void Vec_usize_clear(Vec_usize mut* const self) {
    self->len = 0;
}

void Vec_usize_push(Vec_usize mut* const self, usize const value) {
    if (null_mut == self->ptr) {
        *self = Vec_usize_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(usize) * self->cap);
    }

    self->ptr[self->len++] = value;
}

usize mut* Vec_usize_pop(Vec_usize mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(usize) * --self->len
        : null_mut;
}