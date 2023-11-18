#include "vec_char.c"



Vec_char Vec_char_clone(Vec_char const* const self) {
    Vec_char const result = {
        .ptr = malloc(sizeof(char) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(char) * result.cap,
        self->ptr,
        sizeof(char) * self->len
    );

    return result;
}

void Vec_char_clone_from(Vec_char mut* const self, Vec_char const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(char) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(char) * self->cap,
        other->ptr,
        sizeof(char) * other->len
    );
}

void Vec_char_reserve_exact(Vec_char mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(char) * self->cap);
}

void Vec_char_reserve(Vec_char mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_char_reserve_exact(self, additional_cap);
}

Vec_char Vec_char_repeat(usize const count, char const value) {
    Vec_char mut result = Vec_char_with_capacity(count);
    result.len = count;

    memset(result.ptr, value, count);

    return result;
}

void Vec_char_fill(Vec_char mut* const self, usize const count, char const value) {
    if (self->cap < count) {
        Vec_char_reserve(self, count - self->cap);
    }

    self->len = count;

    memset(self->ptr, value, count);
}