typedef struct Vec {
    u8 mut* ptr;
    usize len, elem_size, cap;
} Vec;

Vec Vec_new(usize const elem_size) {
    return (Vec) {
        .elem_size = elem_size,
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec Vec_with_capacity(usize const elem_size, usize const cap) {
    return (Vec) {
        .ptr = malloc(elem_size * cap),
        .cap = cap,
        .len = 0,
        .elem_size = elem_size
    };
}

void Vec_free(Vec const* const self) {
    free(self->ptr);
    *(Vec mut*) self = Vec_new(self->elem_size);
}

void Vec_push(Vec mut* const self, Addr const value_ptr) {
    if (null_mut == self->ptr) {
        *self = Vec_with_capacity(self->elem_size, 1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, self->elem_size * self->cap);
    }

    memcpy_s(
        self->ptr + self->elem_size * self->len,
        self->elem_size,
        value_ptr,
        self->elem_size
    );

    self->len += 1;
}

AddrMut Vec_pop(Vec mut* const self) {
    return 0 < self->len
        ? self->ptr + self->elem_size * self->len--
        : null_mut;
}

AddrMut Vec_get_address(Vec const* const self, usize const index) {
    return self->ptr + self->elem_size * index;
}

#define Vec_get(self, Type, index) \
    ((Type mut*) Vec_get_address(self, index))

void Vec_set(Vec mut* const self, usize const index, Addr const value_ptr) {
    memcpy_s(
        Vec_get_address(self, index),
        self->elem_size,
        value_ptr,
        self->elem_size
    );
}