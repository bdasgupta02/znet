#pragma once

#include <atomic>
#include <cstdint>
#include <tuple>

namespace znet {

namespace {
template<typename Tag, std::uint64_t Initial>
struct PlaceBase
{
    using tag = Tag;

    static constexpr std::uint64_t tokens = Initial;

    std::atomic_uint64_t runtime_tokens{Initial};
};

template<typename... PlaceList>
struct PlacesBase
{
    using places_type = std::tuple<PlaceList...>;

    places_type places;
};
} // namespace

template<typename Tag, std::uint64_t Initial>
using Place = PlaceBase<Tag, Initial>;

template<typename... PlaceList>
using Places = PlacesBase<PlaceList...>;

template<typename Tag, std::uint64_t Initial>
using JoinPlace = PlaceBase<Tag, Initial>;

template<typename... PlaceList>
using JoinPlaces = PlacesBase<PlaceList...>;

} // namespace znet
