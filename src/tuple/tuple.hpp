#pragma once
#include <utility>
#include <tuple>

#include "compile_list.hpp"
#include "utility.hpp"


template <typename Op, typename... Args>
inline constexpr auto apply(Op&& op, Args&&... args) -> decltype(std::forward<Op>(op)(std::forward<Args>(args)...))
{
    return (std::forward<Op>(op)(std::forward<Args>(args)...));
}

template <typename Op, typename Tuple, template <std::size_t...> class I, std::size_t... Indices>
inline constexpr auto applyTuple(Op&& op, Tuple&& tuple, I<Indices...>&&) ->
decltype(std::forward<Op>(op)(std::get<Indices>(std::forward<Tuple>(tuple))...))
{
    return std::forward<Op>(op)(std::get<Indices>(std::forward<Tuple>(tuple))...);
}


template <typename Op, typename Tuple, typename Indices = make_seq_indices_T<SIZE_C(0), std::tuple_size<typename std::decay<Tuple>::type>::value>>
inline constexpr auto applyTuple(Op&& op, Tuple&& tuple)
{
    return applyTuple(std::forward<Op>(op),std::forward<Tuple>(tuple), Indices{});
}

