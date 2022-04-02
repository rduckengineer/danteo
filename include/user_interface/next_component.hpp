#ifndef DANTEO_NEXT_COMPONENT_HPP
#define DANTEO_NEXT_COMPONENT_HPP

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"

#include <concepts>

namespace danteo {

template <std::invocable OnNextCallback>
class NextComponent : public ftxui::ComponentBase {
public:
    explicit NextComponent(OnNextCallback onNext)
        : cb(std::move(onNext)) {}

    [[nodiscard]] bool Focusable() const override { return false; }

    bool OnEvent(ftxui::Event event) override {
        if (event == ftxui::Event::Return) {
            cb();
            return true;
        }

        return false;
    }

private:
    OnNextCallback cb;
};

template <typename T>
NextComponent(T) -> NextComponent<T>;

template <typename T>
ftxui::Component makeNextComponent(T callback) {
    return std::make_shared<NextComponent<T>>(std::move(callback));
}

} // namespace danteo

#endif // DANTEO_NEXT_COMPONENT_HPP
