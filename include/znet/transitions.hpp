#pragma once

#include <functional>

namespace znet {

template<typename Tag>
struct Transition
{
    using tag = Tag;

    std::function<void()> callable;
};

template<typename... TransitionList>
struct Transitions
{
    using transitions_type = std::tuple<TransitionList...>;

    template<typename Tag>
    void bind(Tag, std::function<void()> callable)
    {
        std::get<Transition<Tag>>(transitions) = {callable};
    }

    transitions_type transitions;
};

} // namespace znet
