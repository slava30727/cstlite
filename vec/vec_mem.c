#include "vec.c"



Vec Vec_clone(Vec const* const self) {
    Vec const result = {
        .ptr = malloc(self->elem_size * self->len),
        .elem_size = self->elem_size,
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        result.elem_size * result.cap,
        self->ptr,
        self->elem_size * self->len
    );

    return result;
}

void Vec_clone_from(Vec mut* const self, Vec const* const other) {
    // assume `self->elem_size` == `other->elem_size`

    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, other->elem_size * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        self->elem_size * self->cap,
        other->ptr,
        other->elem_size * other->len
    );
}

void Vec_reserve_exact(Vec mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, self->elem_size * self->cap);
}

void Vec_reserve(Vec mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_reserve_exact(self, additional_cap);
}