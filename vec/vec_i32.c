#include "../types/marker.h"
#include "../types/int.h"
#include "../types/mem.h"

#include <stdlib.h>
#include <string.h>



typedef struct Vec_i32 {
    i32 mut* ptr;
    usize len, cap;
} Vec_i32;

Vec_i32 Vec_i32_new(void) {
    return (Vec_i32) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_i32 Vec_i32_with_capacity(usize const cap) {
    return (Vec_i32) {
        .ptr = malloc(sizeof(i32) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_i32_free(Vec_i32 const* const self) {
    free(self->ptr);
    *(Vec_i32 mut*) self = Vec_i32_new();
}

void Vec_i32_push(Vec_i32 mut* const self, i32 const value) {
    if (null_mut == self->ptr) {
        *self = Vec_i32_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(i32) * self->cap);
    }

    self->ptr[self->len++] = value;
}

i32 mut* Vec_i32_pop(Vec_i32 mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(i32) * self->len--
        : null_mut;
}