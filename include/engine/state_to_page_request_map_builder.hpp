#ifndef DANTEO_STATE_TO_PAGE_REQUEST_MAP_BUILDER_HPP
#define DANTEO_STATE_TO_PAGE_REQUEST_MAP_BUILDER_HPP

#include "engine/state_to_page_request_map.hpp"

namespace danteo::engine {
template <typename RequestT>
class StateToPageRequestMap<RequestT>::Builder {
    struct MapInserter {
        Builder&      parent_;
        engine::State state_;

        template <typename PageT>
            requires(std::constructible_from<RequestT, PageT> && !std::is_lvalue_reference_v<PageT>)
        void operator<<(PageT&& rhs) && {
            parent_.pagePerState_.try_emplace(
                state_, std::move(rhs)); // NOLINT has to be an r-value here by construction
        }
    };

public:
    MapInserter operator<<(engine::State rhs) { return {*this, rhs}; }

    StateToPageRequestMap<RequestT> build() && {
        return StateToPageRequestMap{std::move(pagePerState_)};
    }

private:
    std::map<engine::State, RequestT> pagePerState_;
};
} // namespace danteo::engine

#endif // DANTEO_STATE_TO_PAGE_REQUEST_MAP_BUILDER_HPP
