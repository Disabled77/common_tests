#pragma once
#include <cstddef>
#include <type_traits>

template <std::size_t...>
struct indices{};

template <std::size_t Begin, std::size_t End, typename Indices = indices<>, typename Enable = void>
struct make_seq_indices
{
    static_assert(Begin <= End, "Begin must be less then End");
};

template <std::size_t Begin, std::size_t End, template <std::size_t...> class I, std::size_t... Indices>
struct make_seq_indices<Begin, End, I<Indices...>, typename std::enable_if<Begin < End, void>::type>
{
    using type = typename make_seq_indices<Begin+1, End, I<Indices..., Begin>>::type;
};

template <std::size_t Begin, std::size_t End, typename Indices>
struct make_seq_indices <Begin, End, Indices, typename std::enable_if<Begin == End, void>::type>
{
    using type = Indices;
};

template <std::size_t Begin, std::size_t End>
using make_seq_indices_T = typename make_seq_indices<Begin, End>::type;