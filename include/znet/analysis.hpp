#pragma once

#include "arcs.hpp"
#include "net_fwd.hpp"
#include "places.hpp"
#include "tags.hpp"
#include "transitions.hpp"

#include <boost/hana.hpp>

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <tuple>
#include <type_traits>

namespace {
namespace hana = boost::hana;
}

namespace znet {

template<typename Net>
struct DeadlockCheck;

template<
    typename... PlaceList,
    typename... JoinPlaceList,
    typename... TransitionList,
    typename... ArcList,
    typename... BackwardArcList>
struct DeadlockCheck<
    Net<Places<PlaceList...>,
        JoinPlaces<JoinPlaceList...>,
        Transitions<TransitionList...>,
        Arcs<ArcList...>,
        BackwardArcs<BackwardArcList...>>>
{
    static consteval bool checkDeadlockFree() { return checkRoot() && checkSubnets() && checkBackwardArcs(); }

private:
    static consteval bool checkBackwardArcs()
    {
        return hana::all_of(
            hana::make_tuple(hana::type_c<BackwardArcList>...),
            [](auto arc)
            {
                using ArcType = typename decltype(arc)::type;
                using SourceType = typename ArcType::source::type;
                using TargetType = typename ArcType::target;

                constexpr bool hasEnoughTokens = SourceType::initial >= ArcType::weight;
                constexpr bool targetIsTransition = TargetType::node == NodeType::Transition;
                return hasEnoughTokens && targetIsTransition;
            });
    }

    static consteval bool dfs(auto queue, auto visited, auto topological_order)
    {
        if constexpr (hana::is_empty(queue))
            return true;
        else
        {
            auto current = hana::front(queue);

            if (hana::contains(visited, current))
                return hana::contains(topological_order, current); // cycles

            auto outgoing_arcs = hana::filter(
                hana::make_tuple(hana::type_c<ArcList>...),
                [&](auto arc) { return hana::equal(hana::type_c<typename decltype(arc)::type::source>, current); });

            auto new_queue = hana::drop_front(queue);
            auto new_visited = hana::insert(visited, current);
            auto all_targets_reachable = hana::all(hana::transform(
                outgoing_arcs,
                [&](auto arc)
                {
                    using TargetType = typename decltype(arc)::type::target;
                    return dfs(hana::prepend(new_queue, hana::type_c<TargetType>), new_visited, topological_order);
                }));

            if (all_targets_reachable)
            {
                // if current node is a transition and if it's enabled
                if constexpr (decltype(current)::type::node == NodeType::Transition)
                {
                    auto incoming_arcs = hana::filter(
                        hana::make_tuple(hana::type_c<ArcList>...),
                        [&](auto arc)
                        { return hana::equal(hana::type_c<typename decltype(arc)::type::target>, current); });

                    auto is_enabled = hana::all(hana::transform(
                        incoming_arcs,
                        [](auto arc)
                        {
                            using SourceType = typename decltype(arc)::type::source::type;
                            using ArcType = typename decltype(arc)::type;
                            return SourceType::initial >= ArcType::weight;
                        }));

                    if (!is_enabled)
                        return false;
                }

                return dfs(new_queue, new_visited, hana::prepend(topological_order, current));
            }

            return false;
        }
    }

    template<typename... RootTags>
    static consteval bool checkSubnetDeadlocks(RootTags... rootTags)
    {
        auto queue = hana::make_tuple(hana::type_c<RootTags>...);
        auto visited = hana::make_set();
        auto topological_order = hana::make_tuple();
        return dfs(queue, visited, topological_order);
    }

    static consteval bool checkRoot()
    {
        using PlaceTagList = hana::tuple<typename PlaceList::tag...>;
        using TargetTagList = hana::tuple<typename ArcList::target...>;

        auto is_root = [](auto tag) { return !hana::contains(TargetTagList{}, tag); };
        auto root_tags = hana::remove_if(PlaceTagList{}, is_root);

        return hana::unpack(root_tags, [](auto... tags) { return checkSubnetDeadlocks(tags...); });
    }

    static consteval bool checkSubnets() { return (checkSubnetDeadlocks(typename BackwardArcList::target{}) && ...); }
};

} // namespace znet
