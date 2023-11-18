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

Vec_u64 Vec_u64_repeat(usize const count, u64 const value) {
    Vec_u64 mut result = Vec_u64_with_capacity(count);
    result.len = count;

    for (usize mut i = 0; i < result.len; ++i) {
        result.ptr[i] = value;
    }

    return result;
}

void Vec_u64_fill(Vec_u64 mut* const self, usize const count, u64 const value) {
    if (self->cap < count) {
        Vec_u64_reserve(self, count - self->cap);
    }

    self->len = count;

    for (usize mut i = 0; i < self->len; ++i) {
        self->ptr[i] = value;
    }
}