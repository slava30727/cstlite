Vec_isize Vec_isize_clone(Vec_isize const* const self) {
    Vec_isize const result = {
        .ptr = malloc(sizeof(isize) * self->len),
        .cap = self->len,
        .len = self->len
    };

    memcpy_s(
        result.ptr,
        sizeof(isize) * result.cap,
        self->ptr,
        sizeof(isize) * self->len
    );

    return result;
}

void Vec_isize_clone_from(Vec_isize mut* const self, Vec_isize const* const other) {
    if (self->cap < other->len) {
        self->ptr = realloc(self->ptr, sizeof(isize) * other->len);
    }

    self->len = other->len;

    memcpy_s(
        self->ptr,
        sizeof(isize) * self->cap,
        other->ptr,
        sizeof(isize) * other->len
    );
}

void Vec_isize_reserve_exact(Vec_isize mut* const self, usize const additional_cap) {
    if (additional_cap <= self->cap - self->len) {
        return;
    }

    self->cap += additional_cap;
    self->ptr = realloc(self->ptr, sizeof(isize) * self->cap);
}

void Vec_isize_reserve(Vec_isize mut* const self, usize mut additional_cap) {
    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;

    additional_cap = additional_cap <= next_cap_diff
        ? next_cap_diff
        : additional_cap;

    Vec_isize_reserve_exact(self, additional_cap);
}

Vec_isize Vec_isize_repeat(usize const count, isize const value) {
    Vec_isize mut result = Vec_isize_with_capacity(count);
    result.len = count;

    for (usize mut i = 0; i < result.len; ++i) {
        result.ptr[i] = value;
    }

    return result;
}

void Vec_isize_fill(Vec_isize mut* const self, usize const count, isize const value) {
    if (self->cap < count) {
        Vec_isize_reserve(self, count - self->cap);
    }

    self->len = count;

    for (usize mut i = 0; i < self->len; ++i) {
        self->ptr[i] = value;
    }
}