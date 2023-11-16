#include "vec_Bool.c"



Vec_Bool Vec_Bool_clone(Vec_Bool const* const self) {
    Vec_Bool const result = {
        .ptr = malloc(1 * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        1 * result.cap,
        self->ptr,
        1 * self->len
    );

    return result;
}

void Vec_Bool_clone_from(Vec_Bool mut* const self, Vec_Bool const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, 1 * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        1 * self->cap,
        other->ptr,
        1 * other->len
    );
}

void Vec_Bool_reserve_exact(Vec_Bool mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, 1 * self->cap);
}

void Vec_Bool_reserve(Vec_Bool mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_Bool_reserve_exact(self, additional_cap);
}