#ifndef DANTEO_DIALOGUE_PAGE_HPP
#define DANTEO_DIALOGUE_PAGE_HPP

#include "engine/event.hpp"
#include <string_view>
#include <vector>

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
    danteo::engine::Event     nextEvent;
    std::vector<DialogueLine> lines;
    int                       maxWidth = 60;
};

struct DialoguePageWithChoice : DialoguePage {
    std::vector<std::string> choices;
};

} // namespace danteo

#endif // DANTEO_DIALOGUE_PAGE_HPP
