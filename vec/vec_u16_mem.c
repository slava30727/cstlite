Vec_u16 Vec_u16_clone(Vec_u16 const* const self) {
    Vec_u16 const result = {
        .ptr = malloc(sizeof(u16) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(u16) * result.cap,
        self->ptr,
        sizeof(u16) * self->len
    );

    return result;
}

void Vec_u16_clone_from(Vec_u16 mut* const self, Vec_u16 const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(u16) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(u16) * self->cap,
        other->ptr,
        sizeof(u16) * other->len
    );
}

void Vec_u16_reserve_exact(Vec_u16 mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(u16) * self->cap);
}

void Vec_u16_reserve(Vec_u16 mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_u16_reserve_exact(self, additional_cap);
}

Vec_u16 Vec_u16_repeat(usize const count, u16 const value) {
    Vec_u16 mut result = Vec_u16_with_capacity(count);
    result.len = count;

    for (usize mut i = 0; i < result.len; ++i) {
        result.ptr[i] = value;
    }

    return result;
}

void Vec_u16_fill(Vec_u16 mut* const self, usize const count, u16 const value) {
    if (self->cap < count) {
        Vec_u16_reserve(self, count - self->cap);
    }

    self->len = count;

    for (usize mut i = 0; i < self->len; ++i) {
        self->ptr[i] = value;
    }
}