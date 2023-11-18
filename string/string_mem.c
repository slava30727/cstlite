void String_reserve_exact(String mut* const self, usize const additional_cap) {
    if (additional_cap + self->len <= self->cap) {
        return;
    }

    self->cap += additional_cap + self->len - self->cap;
    self->ptr = realloc(self->ptr, self->cap);
}

void String_reserve(String mut* const self, usize const additional_cap) {
    if (additional_cap + self->len <= self->cap) {
        return;
    }

    usize const next_cap_diff = 3 * self->cap / 2 + 1 - self->cap;
    String_reserve_exact(
        self,
        additional_cap <= next_cap_diff
            ? next_cap_diff
            : additional_cap
    );
}

void String_append(String mut* const self, String const* const src) {
    String_reserve(self, src->len);

    memcpy(self->ptr + self->len, src->ptr, src->len);

    self->len += src->len;
}