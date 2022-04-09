#include "gameplay/pages/scene_change_page_presenter.hpp"

#include <fmt/format.h>

namespace danteo {
ftxui::Element present(SceneChangePage const& page) {
    static constexpr int maxHeight = 5;

    return ftxui::vbox({ftxui::filler(),
                        ftxui::text(fmt::format("[ {} ]", page.content)) | ftxui::bold | ftxui::flex
                            | ftxui::center | ftxui::inverted
                            | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, maxHeight),
                        ftxui::filler()});
}

ftxui::Component pageFrom(SceneChangePage const&             page,
                          std::function<void(engine::Event)> eventHandler) {
    return ftxui::Renderer([=] { return present(page); })
         | ftxui::CatchEvent([&, eventHandler_ = std::move(eventHandler)](
                                 ftxui::Event event) { // NOLINT API forces the copy
               if (event == ftxui::Event::Return) {
                   eventHandler_(page.next_event);
                   return true;
               }
               return false;
           });
}
} // namespace danteo
