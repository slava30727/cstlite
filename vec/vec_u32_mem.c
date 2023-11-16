#include "vec_u32.c"



Vec_u32 Vec_u32_clone(Vec_u32 const* const self) {
    Vec_u32 const result = {
        .ptr = malloc(sizeof(u32) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(u32) * result.cap,
        self->ptr,
        sizeof(u32) * self->len
    );

    return result;
}

void Vec_u32_clone_from(Vec_u32 mut* const self, Vec_u32 const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(u32) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(u32) * self->cap,
        other->ptr,
        sizeof(u32) * other->len
    );
}

void Vec_u32_reserve_exact(Vec_u32 mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(u32) * self->cap);
}

void Vec_u32_reserve(Vec_u32 mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_u32_reserve_exact(self, additional_cap);
}