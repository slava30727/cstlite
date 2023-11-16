#include "vec_usize.c"



Vec_usize Vec_usize_clone(Vec_usize const* const self) {
    Vec_usize const result = {
        .ptr = malloc(sizeof(usize) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(usize) * result.cap,
        self->ptr,
        sizeof(usize) * self->len
    );

    return result;
}

void Vec_usize_clone_from(Vec_usize mut* const self, Vec_usize const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(usize) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(usize) * self->cap,
        other->ptr,
        sizeof(usize) * other->len
    );
}

void Vec_usize_reserve_exact(Vec_usize mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(usize) * self->cap);
}

void Vec_usize_reserve(Vec_usize mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_usize_reserve_exact(self, additional_cap);
}