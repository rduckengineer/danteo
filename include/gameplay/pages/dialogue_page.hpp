#ifndef DANTEO_DIALOGUE_PAGE_HPP
#define DANTEO_DIALOGUE_PAGE_HPP

#include "engine/event.hpp"

#include "user_interface/color.hpp"

#include <string_view>
#include <vector>
#include <string>

#include <fmt/format.h>

namespace danteo {
struct Character {
    std::string_view name;
    Color            color;

    [[nodiscard]] constexpr bool operator==(Character const& other) const {
        return name == other.name;
    }
};
} // namespace danteo

template <>
struct fmt::formatter<danteo::Character> {
    // cppcheck-suppress[functionStatic]
    constexpr auto parse(fmt::format_parse_context& context) {
        auto ctxIt = context.begin();
        while (ctxIt != context.end() && *ctxIt != '}')
            ;
        return ctxIt;
    }

    template <typename FormatContext>
    // cppcheck-suppress[functionStatic]
    auto format(danteo::Character const& character, FormatContext& context)
        -> decltype(context.out()) {
        return fmt::format_to(context.out(), "{:}", character.name);
    }
};

namespace danteo {

struct DialogueLine {
    enum class Aligned {
        Left,
        Right,
        Center
    };

    Character   character;
    std::string line;
    Aligned     aligned;

    [[nodiscard]] bool operator==(DialogueLine const&) const = default;
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
