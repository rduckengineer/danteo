#include "gameplay/pages/dialogue_page_presenter.hpp"

#include "user_interface/color_ftxui.hpp"
#include "user_interface/scroller.hpp"

#include "warnings_ignore_push.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/range/conversion.hpp"
#include "warnings_ignore_pop.hpp"

#include <gsl/span>

namespace danteo {
namespace {
ftxui::Element    printLine(DialogueLine const& line);
ftxui::MenuOption verticalMenuAlignedRight(int&                               selection,
                                           std::function<void(engine::Event)> handler,
                                           gsl::span<engine::Event const>     events);
} // namespace

std::function<ftxui::Element()> staticPageFrom(DialoguePage const& page) {
    return [&page]() -> ftxui::Element {
        using ranges::views::transform;
        using ranges::to_vector;

        return ftxui::vbox(page.lines | ::ranges::views::transform(printLine) | ::ranges::to_vector)
//             | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, page.maxHeight)
             | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, page.maxWidth) | ftxui::center;
    };
}

ftxui::Component pageFrom(DialoguePageOnly const&            page,
                          std::function<void(engine::Event)> eventHandler) {
    return ftxui::Scroller(ftxui::Renderer([&] {
               return ftxui::vbox({staticPageFrom(page)(),
                                   ftxui::text("> Next") | ftxui::bold | ftxui::inverted
                                       | ftxui::align_right})
                    | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, page.maxWidth) | ftxui::center;
           }))
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
        int selection = 0;

        auto option
            = verticalMenuAlignedRight(selection, std::move(eventHandler_), page.nextEvents);

        auto menu = ftxui::Menu(&page.choices, &selection, option);

        return ftxui::Renderer(menu, [&] {
            return ftxui::vbox({staticPageFrom(page)(), menu->Render()})
                 | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, page.maxWidth) | ftxui::center;
        });
    }();
}

namespace {
auto characterName(Character const& character) {
    return ftxui::text(std::string{character.name}) | ftxui::color(convert::toFTX(character.color))
         | ftxui::bold;
}
auto lineAlignedLeft(DialogueLine const& leftLine) {
    return ftxui::vbox({characterName(leftLine.character),
                        ftxui::paragraphAlignLeft(std::string{leftLine.line})
                            | ftxui::color(convert::toFTX(leftLine.character.color)),
                        ftxui::text(" ")});
}

auto lineAlignedRight(DialogueLine const& rightLine) {
    return ftxui::vbox({characterName(rightLine.character) | ftxui::align_right,
                        ftxui::paragraphAlignRight(std::string{rightLine.line})
                            | ftxui::color(convert::toFTX(rightLine.character.color)),
                        ftxui::text(" ")});
}

auto lineAlignedCenter(DialogueLine const& centerLine) {
    return ftxui::vbox(
        {characterName(centerLine.character)
             | ftxui::color(convert::toFTX(centerLine.character.color)) | ftxui::center,
         ftxui::paragraphAlignCenter(std::string{centerLine.line}), ftxui::text(" ")});
}

ftxui::Element printLine(const DialogueLine& line) {
    switch (line.aligned) {
    case DialogueLine::Aligned::Right: return lineAlignedRight(line);
    case DialogueLine::Aligned::Center: return lineAlignedCenter(line);
    case DialogueLine::Aligned::Left: [[fallthrough]];
    default: return lineAlignedLeft(line);
    }
}

ftxui::MenuOption verticalMenuAlignedRight(int&                               selection,
                                           std::function<void(engine::Event)> handler,
                                           gsl::span<engine::Event const>     events) {
    auto option = ftxui::MenuOption::Vertical();

    option.on_enter = [events, &selection, handler_ = std::move(handler)] {
        handler_(events[static_cast<size_t>(selection)]);
    };

    option.entries.transform = [transform = std::move(option.entries.transform)](
                                   ftxui::EntryState const& state) -> ftxui::Element {
        return transform(state) | ftxui::align_right;
    };

    return option;
}

} // namespace
} // namespace danteo
