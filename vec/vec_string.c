typedef struct Vec_String {
    String mut* ptr;
    usize len, cap;
} Vec_String;

Vec_String Vec_String_new(void) {
    return (Vec_String) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_String Vec_String_with_capacity(usize const cap) {
    return (Vec_String) {
        .ptr = malloc(sizeof(String) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_String_free(Vec_String const* const self) {
    for (usize mut i = 0; i < self->len; ++i) {
        String_free(self->ptr + i);
    }
    free(self->ptr);
    *(Vec_String mut*) self = Vec_String_new();
}

void Vec_String_push(Vec_String mut* const self, String const value) {
    if (null_mut == self->ptr) {
        *self = Vec_String_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(String) * self->cap);
    }

    self->ptr[self->len++] = value;
}

void Vec_String_clear(Vec_String mut* const self) {
    for (usize mut i = 0; i < self->len; ++i) {
        String_free(self->ptr + i);
    }
    self->len = 0;
}

String mut* Vec_String_pop(Vec_String mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(String) * self->len--
        : null_mut;
}