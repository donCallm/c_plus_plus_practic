#pragma once

#include <cstddef>

constexpr const size_t MAX_PH_COUNT = 10;

template <size_t N>
struct placeholders {
    constexpr size_t get_num() { return N; }
};

placeholders<1>  _1;
placeholders<2>  _2;
placeholders<3>  _3;
placeholders<4>  _4;
placeholders<5>  _5;
placeholders<6>  _6;
placeholders<7>  _7;
placeholders<8>  _8;
placeholders<9>  _9;
placeholders<10> _10;

template <typename T>
struct is_placeholder {
    static constexpr bool value = false;
};

template <size_t N>
struct is_placeholder<placeholders<N>> {
    static constexpr bool value = true; // if we cant call is_placeholder - SFINAE work
};
