#include "../types/marker.h"
#include "../types/int.h"
#include "../types/mem.h"

#include <stdlib.h>
#include <string.h>



typedef struct Vec_isize {
    isize mut* ptr;
    usize len, cap;
} Vec_isize;

Vec_isize Vec_isize_new(void) {
    return (Vec_isize) {
        .ptr = null_mut,
        .cap = 0,
        .len = 0
    };
}

Vec_isize Vec_isize_with_capacity(usize const cap) {
    return (Vec_isize) {
        .ptr = malloc(sizeof(isize) * cap),
        .cap = cap,
        .len = 0,
    };
}

void Vec_isize_free(Vec_isize const* const self) {
    free(self->ptr);
    *(Vec_isize mut*) self = Vec_isize_new();
}

void Vec_isize_push(Vec_isize mut* const self, isize const value) {
    if (null_mut == self->ptr) {
        *self = Vec_isize_with_capacity(1);
    }

    if (self->len == self->cap) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, sizeof(isize) * self->cap);
    }

    self->ptr[self->len++] = value;
}

isize mut* Vec_isize_pop(Vec_isize mut* const self) {
    return 0 < self->len
        ? self->ptr + sizeof(isize) * self->len--
        : null_mut;
}