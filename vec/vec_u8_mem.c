Vec_u8 Vec_u8_clone(Vec_u8 const* const self) {
    Vec_u8 const result = {
        .ptr = malloc(sizeof(u8) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(u8) * result.cap,
        self->ptr,
        sizeof(u8) * self->len
    );

    return result;
}

void Vec_u8_clone_from(Vec_u8 mut* const self, Vec_u8 const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(u8) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(u8) * self->cap,
        other->ptr,
        sizeof(u8) * other->len
    );
}

void Vec_u8_reserve_exact(Vec_u8 mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(u8) * self->cap);
}

void Vec_u8_reserve(Vec_u8 mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_u8_reserve_exact(self, additional_cap);
}

Vec_u8 Vec_u8_repeat(usize const count, u8 const value) {
    Vec_u8 mut result = Vec_u8_with_capacity(count);
    result.len = count;

    memset(result.ptr, value, count);

    return result;
}

void Vec_u8_fill(Vec_u8 mut* const self, usize const count, u8 const value) {
    if (self->cap < count) {
        Vec_u8_reserve(self, count - self->cap);
    }

    self->len = count;

    memset(self->ptr, value, count);
}