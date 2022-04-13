#include "gameplay/pages/dialogue_page_presenter.hpp"

#include "dialogue_page_component_base.hpp"

namespace danteo {

// NOLINTNEXTLINE doesn't define other special member functions
class DialoguePageOnlyPresenter : public DialoguePageComponentBase<DialoguePageOnly> {
public:
    DialoguePageOnlyPresenter(DialoguePageOnly const&            page,
                              std::function<void(engine::Event)> eventHandler)
        : DialoguePageComponentBase{page}
        , eventHandler_{std::move(eventHandler)} {}
    ~DialoguePageOnlyPresenter() override = default;

    ftxui::Element Render() override {
        return ftxui::vbox(
                   {DialoguePageComponentBase::Render(),
                    ftxui::text("> Next") | ftxui::bold | ftxui::inverted | ftxui::align_right})
             | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, page_.maxWidth) | ftxui::center;
    }

    bool OnEvent(ftxui::Event event) override {
        if (event == ftxui::Event::Return) {
            eventHandler_(page_.nextEvent);
            return true;
        }
        return false;
    }

private:
    std::function<void(engine::Event)> eventHandler_;
};

ftxui::Component pageFrom(DialoguePageOnly const&            page,
                          std::function<void(engine::Event)> eventHandler) {
    return std::make_shared<DialoguePageOnlyPresenter>(page, std::move(eventHandler));
}

} // namespace danteo
