#include "gameplay/pages/dialogue_page_presenter.hpp"

#include "dialogue_page_component_base.hpp"

#include "ftxui/component/component.hpp"

#include <gsl/span>

namespace danteo {

// NOLINTNEXTLINE doesn't define other special member functions
class DialoguePageWithChoicePresenter : public DialoguePageComponentBase<DialoguePageWithChoice> {
public:
    DialoguePageWithChoicePresenter(DialoguePageWithChoice const&      page,
                                    std::function<void(engine::Event)> eventHandler)
        : DialoguePageComponentBase(page)
        , menu_{ftxui::Menu(
              &page.choices, &selection_,
              verticalMenuAlignedRight(selection_, std::move(eventHandler), page_.nextEvents))} {}
    ~DialoguePageWithChoicePresenter() override = default;

    ftxui::Element Render() override {
        return ftxui::vbox({DialoguePageComponentBase::Render(), menu_->Render()})
             | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, page_.maxWidth) | ftxui::center;
    }

    bool OnEvent(ftxui::Event event) override { return menu_->OnEvent(event); }

private:
    static ftxui::MenuOption verticalMenuAlignedRight(int&                               selection,
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

    int              selection_ = 0;
    ftxui::Component menu_;
};

ftxui::Component pageFrom(DialoguePageWithChoice const&      page,
                          std::function<void(engine::Event)> eventHandler) {
    return std::make_shared<DialoguePageWithChoicePresenter>(page, std::move(eventHandler));
}
} // namespace danteo
