#ifndef DANTEO_DANTEO_PAGE_PER_STATE_HPP
#define DANTEO_DANTEO_PAGE_PER_STATE_HPP

#include "engine/state.hpp"
#include "gameplay/danteo_page_request.hpp"

#include <map>
#include <optional>

namespace danteo {
class StateToPageRequestMap {
public:
    explicit StateToPageRequestMap(std::map<State, DanteoPageRequest> requestPerState)
        : requestPerState_(std::move(requestPerState)) {}

    [[nodiscard]] std::optional<std::reference_wrapper<DanteoPageRequest const>> pageFor(
        State state) const {
        auto pageIt = requestPerState_.find(state);
        if (pageIt == requestPerState_.end()) { return std::nullopt; }
        return std::ref(pageIt->second);
    }

private:
    std::map<State, DanteoPageRequest> requestPerState_;
};
} // namespace danteo

#endif // DANTEO_DANTEO_PAGE_PER_STATE_HPP
