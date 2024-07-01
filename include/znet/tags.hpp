#pragma once

#include "node_type.hpp"

#include <cstdint>

namespace znet::tag {

template<typename T, NodeType Node>
struct TagBase
{
    using type = T;
    static constexpr NodeType node = Node;
};

template<typename T, std::uint64_t Initial>
struct Place : TagBase<T, NodeType::Place>
{
    static constexpr auto initial = Initial;
};

template<typename T, std::uint64_t Initial>
struct JoinPlace : TagBase<T, NodeType::JoinPlace>
{
    static constexpr auto initial = Initial;
};

template<typename T>
struct Transition : TagBase<T, NodeType::Transition>
{};

template<typename T>
struct Arc : TagBase<T, NodeType::Arc>
{};

template<typename T>
struct BackwardArc : TagBase<T, NodeType::BackwardArc>
{};

} // namespace znet::tag
