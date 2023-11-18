typedef struct String {
    char mut* ptr;
    usize len, cap;
} String;

#define String_DEFAULT ((String) { .ptr = null_mut, .len = 0, .cap = 0 })

String String_from_literal(char const* const str) {
    usize const len = strlen(str);

    String const result = {
        .ptr = malloc(len),
        .len = len,
        .cap = len
    };

    memcpy_s(result.ptr, result.cap, str, len + 1);

    return result;
}

String String_with_capacity(usize const cap) {
    return (String) {
        .ptr = malloc(cap),
        .cap = cap,
        .len = 0
    };
}

void String_free(String const* const self) {
    free(self->ptr);
    *(String mut*) self = String_DEFAULT;
}

void String_push(String mut* const self, char const symbol) {
    if (null_mut == self->ptr) {
        *self = String_with_capacity(16);
    }

    if (self->cap == self->len) {
        self->cap = 3 * self->cap / 2 + 1;
        self->ptr = realloc(self->ptr, self->cap);
    }

    self->ptr[self->len++] = symbol;
}

char String_pop(String mut* const self) {
    return self->ptr[--self->len];
}