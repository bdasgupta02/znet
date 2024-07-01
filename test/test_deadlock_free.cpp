#include "znet/arcs.hpp"
#include "znet/net.hpp"
#include "znet/places.hpp"
#include "znet/tags.hpp"
#include "znet/transitions.hpp"

using namespace znet;

void simpleTest()
{
    struct P1 : tag::Place<P1, 1>
    {};
    struct P2 : tag::JoinPlace<P2, 1>
    {};
    struct T1 : tag::Transition<T1>
    {};

    using Place1 = Place<P1, 1>;
    using Place2 = JoinPlace<P2, 1>;
    using Transition1 = Transition<T1>;
    using Arc1 = Arc<P1, T1, 1>;
    using Arc2 = Arc<T1, P2, 1>;
    using BArc1 = BackwardArc<P2, T1, 1>;

    // clang-format off
    using System = Net<
        Places<Place1>,
        JoinPlaces<Place2>,
        Transitions<Transition1>,
        Arcs<Arc1, Arc2>,
        BackwardArcs<BArc1>
    >;
    // clang-format on

    static_assert(System::is_deadlock_free);
}

void hasDeadlockTest() {}

void hasCycleTest() {}

void subnetResolutionTest() {}

int main()
{
    simpleTest();
    hasDeadlockTest();
    hasCycleTest();
    subnetResolutionTest();
}
