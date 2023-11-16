#include "vec_u64.c"



Vec_u64 Vec_u64_clone(Vec_u64 const* const self) {
    Vec_u64 const result = {
        .ptr = malloc(sizeof(u64) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(u64) * result.cap,
        self->ptr,
        sizeof(u64) * self->len
    );

    return result;
}

void Vec_u64_clone_from(Vec_u64 mut* const self, Vec_u64 const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(u64) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(u64) * self->cap,
        other->ptr,
        sizeof(u64) * other->len
    );
}

void Vec_u64_reserve_exact(Vec_u64 mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(u64) * self->cap);
}

void Vec_u64_reserve(Vec_u64 mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_u64_reserve_exact(self, additional_cap);
}