typedef struct Vec_Bool {
    u8 mut* ptr;
    usize len, cap;
} Vec_Bool;

Vec_Bool Vec_Bool_new(void) {
    return (Vec_Bool) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_Bool Vec_Bool_with_capacity(usize const cap) {
    return (Vec_Bool) {
        .ptr = malloc(1 * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_Bool_free(Vec_Bool const* const self) {
    free(self->ptr);
    *(Vec_Bool mut*) self = Vec_Bool_new();
}

void Vec_Bool_clear(Vec_Bool mut* const self) {
    self->len = 0;
}

void Vec_Bool_push(Vec_Bool mut* const self, Bool const value) {
    if (null_mut == self->ptr) {
        *self = Vec_Bool_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, 1 * self->cap);
    }

    self->ptr[self->len++] = value;
}

Bool Vec_Bool_pop(Vec_Bool mut* const self) {
    return 0 < self->len
        ? (Bool) *(self->ptr + 1 * --self->len)
        : null_mut;
}