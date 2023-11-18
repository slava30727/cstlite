Vec_i64 Vec_i64_clone(Vec_i64 const* const self) {
    Vec_i64 const result = {
        .ptr = malloc(sizeof(i64) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(i64) * result.cap,
        self->ptr,
        sizeof(i64) * self->len
    );

    return result;
}

void Vec_i64_clone_from(Vec_i64 mut* const self, Vec_i64 const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(i64) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(i64) * self->cap,
        other->ptr,
        sizeof(i64) * other->len
    );
}

void Vec_i64_reserve_exact(Vec_i64 mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(i64) * self->cap);
}

void Vec_i64_reserve(Vec_i64 mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_i64_reserve_exact(self, additional_cap);
}

Vec_i64 Vec_i64_repeat(usize const count, i64 const value) {
    Vec_i64 mut result = Vec_i64_with_capacity(count);
    result.len = count;

    for (usize mut i = 0; i < result.len; ++i) {
        result.ptr[i] = value;
    }

    return result;
}

void Vec_i64_fill(Vec_i64 mut* const self, usize const count, i64 const value) {
    if (self->cap < count) {
        Vec_i64_reserve(self, count - self->cap);
    }

    self->len = count;

    for (usize mut i = 0; i < self->len; ++i) {
        self->ptr[i] = value;
    }
}