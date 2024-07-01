#pragma once

#include "analysis.hpp"
#include "arcs.hpp"
#include "net_fwd.hpp"
#include "places.hpp"
#include "transitions.hpp"

#include <functional>

namespace znet {

template<typename _Places, typename _JoinPlaces, typename _Transitions, typename _Arcs, typename _BackwardArcs>
class Net
{
public:
    static constexpr bool is_deadlock_free = DeadlockCheck<Net>::checkDeadlockFree();

    // TODO
    void start() {}

    template<typename Tag>
    void bind(Tag, std::function<void()> callable)
    {
        transitions.bind(Tag{}, callable);
    }

private:
    _Places places;
    _JoinPlaces joinPlaces;
    _Transitions transitions;
};

} // namespace znet
