#pragma once

#include <cstdint>
#include <type_traits>

namespace znet {

namespace {
template<typename Source, typename Target, std::uint64_t Weight>
struct ArcBase
{
    using source = Source;
    using target = Target;

    static constexpr auto weight = Weight;
};

template<typename... ArcList>
struct ArcsBase
{};
}; // namespace

template<typename Source, typename Target, std::uint64_t Weight>
using Arc = ArcBase<Source, Target, Weight>;

template<typename Source, typename Target, std::uint64_t Weight>
using BackwardArc = ArcBase<Source, Target, Weight>;

template<typename... ArcList>
using Arcs = ArcsBase<ArcList...>;

template<typename... ArcList>
using BackwardArcs = ArcsBase<ArcList...>;

} // namespace znet
