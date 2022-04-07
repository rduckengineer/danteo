#ifndef DANTEO_STATE_TO_PAGE_REQUEST_MAP_HPP
#define DANTEO_STATE_TO_PAGE_REQUEST_MAP_HPP

#include "engine/state.hpp"
#include "engine/page_request.hpp"

#include <map>
#include <optional>

namespace danteo {
template <typename RequestT>
class StateToPageRequestMap {
public:
    explicit StateToPageRequestMap(std::map<State, RequestT> requestPerState)
        : requestPerState_(std::move(requestPerState)) {}

    [[nodiscard]] std::optional<std::reference_wrapper<RequestT const>> pageFor(State state) const {
        auto pageIt = requestPerState_.find(state);
        if (pageIt == requestPerState_.end()) { return std::nullopt; }
        return std::ref(pageIt->second);
    }

private:
    std::map<State, RequestT> requestPerState_;
};
} // namespace danteo

#endif // DANTEO_STATE_TO_PAGE_REQUEST_MAP_HPP
