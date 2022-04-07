#include "gameplay/pages/dialogue_page_presenter.hpp"

#include <ranges>

namespace danteo {
ftxui::Component pageFrom(DialoguePage const&                page,
                          std::function<void(engine::Event)> eventHandler) {

    auto characterName = [](Character const& character) {
        return ftxui::text(std::string{character.name}) | ftxui::bold;
    };

    auto lineAlignedLeft = [=](DialogueLine const& leftLine) {
        return ftxui::vbox({characterName(leftLine.character),
                            ftxui::paragraphAlignLeft(std::string{leftLine.line})});
    };

    auto lineAlignedRight = [=](DialogueLine const& rightLine) {
        return ftxui::vbox({characterName(rightLine.character) | ftxui::align_right,
                            ftxui::paragraphAlignRight(std::string{rightLine.line})});
    };

    auto lineAlignedCenter = [=](DialogueLine const& centerLine) {
        return ftxui::vbox({characterName(centerLine.character) | ftxui::center,
                            ftxui::paragraphAlignCenter(std::string{centerLine.line})});
    };

    auto printLine = [&](DialogueLine const& line) {
        switch (line.aligned) {
        case DialogueLine::Aligned::Right: return lineAlignedRight(line);
        case DialogueLine::Aligned::Center: return lineAlignedCenter(line);
        case DialogueLine::Aligned::Left: [[fallthrough]];
        default: return lineAlignedLeft(line);
        }
    };

    auto staticPage = [=] {
        ftxui::Elements elements;
        for (auto const& line : page.lines) {
            elements.push_back(printLine(line));
        }
        return ftxui::vbox(std::move(elements))
             | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, page.maxWidth) | ftxui::center;
    };

    return ftxui::Renderer(std::move(staticPage))
         | ftxui::CatchEvent([&, eventHandler_ = std::move(eventHandler)](
                                 ftxui::Event event) { // NOLINT API forces the copy
               if (event == ftxui::Event::Return) {
                   eventHandler_(page.nextEvent);
                   return true;
               }
               return false;
           });
}

} // namespace danteo
