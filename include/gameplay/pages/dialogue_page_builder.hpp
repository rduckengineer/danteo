#ifndef DANTEO_DIALOGUE_PAGE_BUILDER_HPP
#define DANTEO_DIALOGUE_PAGE_BUILDER_HPP

#include "gameplay/pages/dialogue_page.hpp"

#include <fmt/format.h>
#include "warnings_ignore_push.hpp"
#include <range/v3/algorithm/find_if.hpp>
#include "warnings_ignore_pop.hpp"

namespace danteo {

class DialogueBuilder {
    struct CharacterSideBuilder;
    struct LineBuilder;

    DialogueBuilder() = default;

public:
    static CharacterSideBuilder place(Character const& character);
    CharacterSideBuilder        andPlace(Character const& character) &&;

    LineBuilder then(Character const& character) &&;

    // NOLINTNEXTLINE implicit
    [[nodiscard]] operator DialoguePage() && { return std::move(page_); }

private:
    DialogueLine::Aligned characterSide(Character const& character);

    std::vector<std::pair<Character, DialogueLine::Aligned>> characterPlacement_;
    DialoguePage                                             page_{};
};

struct DialogueBuilder::CharacterSideBuilder {
    CharacterSideBuilder(DialogueBuilder&& parent, Character const& character)
        : parent_{std::move(parent)}
        , character_{character} {}

    DialogueBuilder left() && { return std::move(*this).toSide(DialogueLine::Aligned::Left); }
    DialogueBuilder center() && { return std::move(*this).toSide(DialogueLine::Aligned::Center); }
    DialogueBuilder right() && { return std::move(*this).toSide(DialogueLine::Aligned::Right); }

private:
    DialogueBuilder toSide(DialogueLine::Aligned aligned) && {
        parent_.characterPlacement_.emplace_back(character_, aligned);
        return std::move(parent_);
    }

    DialogueBuilder  parent_;
    Character const& character_;
};

struct DialogueBuilder::LineBuilder {
    LineBuilder(DialogueBuilder&& parent, Character const& character)
        : parent_{std::move(parent)}
        , character_{character} {}

    DialogueBuilder says(std::string line) &&;

private:
    DialogueBuilder  parent_;
    Character const& character_;
};

DialogueBuilder::CharacterSideBuilder DialogueBuilder::place(const Character& character) {
    return DialogueBuilder{}.andPlace(character);
}

DialogueBuilder::CharacterSideBuilder DialogueBuilder::andPlace(Character const& character) && {
    return {std::move(*this), character};
}

DialogueBuilder::LineBuilder DialogueBuilder::then(const Character& character) && {
    return {std::move(*this), character};
}

DialogueBuilder DialogueBuilder::LineBuilder::says(std::string line) && {
    parent_.page_.lines.push_back(
        DialogueLine{character_, std::move(line), parent_.characterSide(character_)});
    return std::move(parent_);
}

DialogueLine::Aligned DialogueBuilder::characterSide(const Character& character) {
    auto alignmentIt = ranges::find_if(characterPlacement_, [&](auto const& pair) {
        return pair.first == character;
    });

    if (alignmentIt == characterPlacement_.end()) {
        throw std::logic_error(fmt::format("This character ({}) should have a side!", character));
    }

    return alignmentIt->second;
}

} // namespace danteo

#endif // DANTEO_DIALOGUE_PAGE_BUILDER_HPP
