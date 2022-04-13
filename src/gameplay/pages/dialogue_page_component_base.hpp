#ifndef DANTEO_DIALOGUE_PAGE_COMPONENT_BASE_HPP
#define DANTEO_DIALOGUE_PAGE_COMPONENT_BASE_HPP

#include "gameplay/pages/dialogue_page.hpp"

#include "user_interface/color_ftxui.hpp"

#include "ftxui/component/component_base.hpp"

#include "warnings_ignore_push.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/range/conversion.hpp"
#include "warnings_ignore_pop.hpp"

namespace danteo {

template <typename PageT>
// NOLINTNEXTLINE doesn't define other special member functions
class DialoguePageComponentBase : public ftxui::ComponentBase {
public:
    explicit DialoguePageComponentBase(PageT const& page)
        : page_{page} {}
    ~DialoguePageComponentBase() override = default;

    ftxui::Element Render() override {
        using ranges::to_vector;
        using ranges::views::transform;

        return ftxui::vbox(page_.lines | transform(printLine) | to_vector)
             | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, page_.maxWidth) | ftxui::center;
    }

private:
    static auto characterName(Character const& character) {
        return ftxui::text(std::string{character.name})
             | ftxui::color(convert::toFTX(character.color)) | ftxui::bold;
    }

    static auto lineAlignedLeft(DialogueLine const& leftLine) {
        return ftxui::vbox({characterName(leftLine.character),
                            ftxui::paragraphAlignLeft(std::string{leftLine.line})
                                | ftxui::color(convert::toFTX(leftLine.character.color)),
                            ftxui::text(" ")});
    }

    static auto lineAlignedRight(DialogueLine const& rightLine) {
        return ftxui::vbox({characterName(rightLine.character) | ftxui::align_right,
                            ftxui::paragraphAlignRight(std::string{rightLine.line})
                                | ftxui::color(convert::toFTX(rightLine.character.color)),
                            ftxui::text(" ")});
    }

    static auto lineAlignedCenter(DialogueLine const& centerLine) {
        return ftxui::vbox(
            {characterName(centerLine.character)
                 | ftxui::color(convert::toFTX(centerLine.character.color)) | ftxui::center,
             ftxui::paragraphAlignCenter(std::string{centerLine.line}), ftxui::text(" ")});
    }

    static ftxui::Element printLine(const DialogueLine& line) {
        switch (line.aligned) {
        case DialogueLine::Aligned::Right: return lineAlignedRight(line);
        case DialogueLine::Aligned::Center: return lineAlignedCenter(line);
        case DialogueLine::Aligned::Left: [[fallthrough]];
        default: return lineAlignedLeft(line);
        }
    }

protected:
    PageT const& page_;
};
} // namespace danteo

#endif // DANTEO_DIALOGUE_PAGE_COMPONENT_BASE_HPP
