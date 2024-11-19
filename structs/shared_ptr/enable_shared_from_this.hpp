#pragma once

#include "shared_ptr.hpp"

template <typename T>
struct enable_shared_from_this {
    protected:
        enable_shared_from_this() noexcept = default;

    shared_ptr<T> shared_from_this() {
        return shared_ptr<T>(static_cast<T*>(this));
    }
};
