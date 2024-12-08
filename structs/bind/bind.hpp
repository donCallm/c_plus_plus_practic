#pragma once

#include <functional>
#include <tuple>
#include <array>
#include <utility>
#include <iostream>
#include "placeholders.hpp"

template <typename T>
struct func_traits;

template <typename Ret, typename ...Args>
struct func_traits<Ret(Args...)> {
    using ret_type = Ret;
    using arg_tuple = std::tuple<Args...>;
};

template <typename Ret, typename ...Args>
struct func_traits<Ret(*)(Args...)> {
    using ret_type = Ret;
    using arg_tuple = std::tuple<Args...>;
};

template <std::size_t... Incs>
struct index_seq {
    static constexpr std::size_t size = sizeof...(Incs);
};

template <std::size_t N, std::size_t... Incs>
struct make_index : make_index<N - 1, Incs..., N - 1> {};

template <std::size_t... Incs>
struct make_index<0, Incs...> {
    using type = index_seq<Incs...>;
};

template <size_t N>
using make_index_sequence = typename make_index<N>::type;

template <typename Func, typename ...BindArgs>
struct bind {

    using ret_type = typename func_traits<Func>::ret_type;
    using arg_tuple = typename func_traits<Func>::arg_tuple;

    bind(Func& f, BindArgs&&... args)
        : _bind_args(std::forward<BindArgs>(args)...),
        _func(f),
        _ph_count(0)
    {
        if (sizeof...(BindArgs) < std::tuple_size<decltype(arg_tuple{})>::value) {
            throw std::runtime_error("too few args");
        } else if (sizeof...(BindArgs) > std::tuple_size<decltype(arg_tuple{})>::value) {
            throw std::runtime_error("too many args");
        }
        handle_bind_args(make_index_sequence<sizeof...(BindArgs)>());
    }

    template <typename ...Args>
    ret_type operator()(Args&&... args) {
        if (sizeof...(args) < _ph_count) {
            throw std::runtime_error("too few params");
        }

        std::tuple<Args...> new_args(std::forward<Args>(args)...);

        constexpr size_t params_size = sizeof...(BindArgs);
        arg_tuple full_args = handle_new_args(new_args, make_index_sequence<params_size>());

        std::apply(_func, full_args);
    }

private:
    template <size_t ...Incs>
    void handle_bind_args(const index_seq<Incs...>&) {
        ((handle_bind_args_impl<Incs>()), ...);
    }

    template <size_t Index>
    void handle_bind_args_impl() {
        std::cout << "handle_bind_args_impl start\n";
        if (Index >= std::tuple_size<decltype(_bind_args)>::value) {
            throw std::runtime_error("invalid index");
        }
        auto bind_elem = std::get<Index>(_bind_args);
        if (is_placeholder<decltype(bind_elem)>::value) {
            ++_ph_count;
        }
        std::cout << "handle_bind_args_impl end\n";
    }

    template <typename ...Args, size_t ...Incs>
    arg_tuple handle_new_args(const std::tuple<Args...>& new_args, const index_seq<Incs...>&) {
        arg_tuple full_args;
        ((handle_new_args_impl<Incs>(full_args, new_args)), ...);
        return full_args;
    }

    template <size_t Index>
    void handle_new_args_impl(arg_tuple& full_args, auto new_args) {
        std::cout << "handle_new_args_impl start\n";
        if (Index >= std::tuple_size<decltype(_bind_args)>::value) {
            throw std::runtime_error("invalid index");
        }
        auto bind_elem = std::get<Index>(_bind_args);
        if constexpr (is_placeholder<decltype(bind_elem)>::value) {
            constexpr size_t num = bind_elem.get_num();

            if constexpr (num >= std::tuple_size<decltype(new_args)>::value) {
                throw std::runtime_error("invalid num");
            }
            
            auto new_elem = std::get<num>(new_args);
            std::get<Index>(full_args) = new_elem;
        } else {
            std::get<Index>(full_args) = bind_elem;
        }
        std::cout << "handle_new_args_impl end\n";
    }

private:
    std::tuple<BindArgs...> _bind_args;
    Func&                      _func;
    size_t                     _ph_count;
};