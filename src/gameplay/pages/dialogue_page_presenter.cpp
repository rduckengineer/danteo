#include "gameplay/pages/dialogue_page_presenter.hpp"

#include "warnings_ignore_push.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/range/conversion.hpp"
#include "warnings_ignore_pop.hpp"

namespace danteo {
namespace {
ftxui::Element printLine(DialogueLine const& line);
} // namespace

std::function<ftxui::Element()> staticPageFrom(DialoguePage const& page) {
    return [&page] {
        using ranges::views::transform;
        using ranges::to_vector;

        return ftxui::vbox(page.lines | transform(printLine) | to_vector)
             | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, page.maxWidth) | ftxui::center;
    };
}

ftxui::Component pageFrom(DialoguePageOnly const&            page,
                          std::function<void(engine::Event)> eventHandler) {
    return ftxui::Renderer(staticPageFrom(page))
         | ftxui::CatchEvent([&, eventHandler_ = std::move(eventHandler)](
                                 ftxui::Event event) { // NOLINT API forces the copy
               if (event == ftxui::Event::Return) {
                   eventHandler_(page.nextEvent);
                   return true;
               }
               return false;
           });
}

ftxui::Component pageFrom(DialoguePageWithChoice const&      page,
                          std::function<void(engine::Event)> eventHandler) {
    return [&page, eventHandler_ = std::move(eventHandler)]() mutable {
        int  selection  = 0;
        auto option     = ftxui::MenuOption::Vertical();
        option.on_enter = [&page, &selection, handler = std::move(eventHandler_)] {
            handler(page.nextEvents[static_cast<size_t>(selection)]);
        };
        return ftxui::Container::Vertical({ftxui::Renderer(staticPageFrom(page)),
                                           ftxui::Menu(&page.choices, &selection, option)})
             | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, page.maxWidth) | ftxui::center;
    }();
}

namespace {
auto characterName(Character const& character) {
    return ftxui::text(std::string{character.name}) | ftxui::bold;
}
auto lineAlignedLeft(DialogueLine const& leftLine) {
    return ftxui::vbox(
        {characterName(leftLine.character), ftxui::paragraphAlignLeft(std::string{leftLine.line})});
}

auto lineAlignedRight(DialogueLine const& rightLine) {
    return ftxui::vbox({characterName(rightLine.character) | ftxui::align_right,
                        ftxui::paragraphAlignRight(std::string{rightLine.line})});
}

auto lineAlignedCenter(DialogueLine const& centerLine) {
    return ftxui::vbox({characterName(centerLine.character) | ftxui::center,
                        ftxui::paragraphAlignCenter(std::string{centerLine.line})});
}

ftxui::Element printLine(const DialogueLine& line) {
    switch (line.aligned) {
    case DialogueLine::Aligned::Right: return lineAlignedRight(line);
    case DialogueLine::Aligned::Center: return lineAlignedCenter(line);
    case DialogueLine::Aligned::Left: [[fallthrough]];
    default: return lineAlignedLeft(line);
    }
}

} // namespace
} // namespace danteo
