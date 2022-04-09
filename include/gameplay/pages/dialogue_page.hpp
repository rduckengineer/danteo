#ifndef DANTEO_DIALOGUE_PAGE_HPP
#define DANTEO_DIALOGUE_PAGE_HPP

#include "engine/event.hpp"
#include <string_view>
#include <vector>
#include <string>

namespace danteo {
struct Character {
    std::string_view name;

    [[nodiscard]] constexpr bool operator==(Character const&) const = default;
};

struct DialogueLine {
    enum class Aligned {
        Left,
        Right,
        Center
    };

    Character        character;
    std::string_view line;
    Aligned          aligned;

    [[nodiscard]] constexpr bool operator==(DialogueLine const&) const = default;
};

struct DialoguePage {
    static constexpr int defaultMaxWidth = 60;

    DialoguePage()               = default;
    DialoguePage(DialoguePage&&) = default;

    std::vector<DialogueLine> lines;
    int                       maxWidth = defaultMaxWidth;
};

struct DialoguePageOnly : DialoguePage {
    engine::Event nextEvent;
};

struct DialoguePageWithChoice : DialoguePage {
    std::vector<std::string>   choices;
    std::vector<engine::Event> nextEvents;
};
} // namespace danteo

#endif // DANTEO_DIALOGUE_PAGE_HPP
