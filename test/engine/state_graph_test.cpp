#include "engine/state_graph_builder.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

namespace {
struct TestStates {
    static constexpr danteo::State first{"first"sv};
    static constexpr danteo::State second{"second"sv};
    static constexpr danteo::State third{"third"sv};
};

struct TestEvents {
    static constexpr danteo::Event next{"next"sv};
    static constexpr danteo::Event end{"end"sv};
};
}

// NOLINTNEXTLINE[readability-function-cognitive-complexity]
SCENARIO("The navigation graph represents the graph of allowed state changes") {
    GIVEN("A navigation graph") {
        auto builder = danteo::StateGraph::Builder{};

        builder / TestStates::second + TestEvents::next = TestStates::third;

        danteo::StateGraph navigation = std::move(builder).build();
        WHEN("Trying to find an existing a unique unconditional transition") {
            auto maybeLandingState
                = navigation.firstValidTransition(TestStates::second, TestEvents::next);

            THEN("The transition is found and it lands on the correct state") {
                REQUIRE(maybeLandingState);
                CHECK(*maybeLandingState == TestStates::third);
            }
        }

        WHEN("Trying to find a non-existant transition") {
            auto maybeLandingState
                = navigation.firstValidTransition(TestStates::second, TestEvents::end);
            THEN("The landing state is empty") { REQUIRE_FALSE(maybeLandingState); }
        }
    }
    GIVEN("A navigation graph where the first potential transition is conditional") {
        bool takeSecond = true;
        auto goToSecond = [&] { return takeSecond; };

        auto builder = danteo::StateGraph::Builder{};

        builder / TestStates::first + TestEvents::next | goToSecond = TestStates::second;
        builder / TestStates::first + TestEvents::next              = TestStates::third;

        danteo::StateGraph navigation = std::move(builder).build();

        WHEN("The conditions matches") {
            takeSecond = true;
            auto maybeLandingState
                = navigation.firstValidTransition(TestStates::first, TestEvents::next);

            THEN("The first transition's landing state is returned") {
                REQUIRE(maybeLandingState);
                CHECK(*maybeLandingState == TestStates::second);
            }
        }

        WHEN("The condition does not match") {
            takeSecond = false;
            auto maybeLandingState
                = navigation.firstValidTransition(TestStates::first, TestEvents::next);

            THEN("The other transition's landing state is returned") {
                REQUIRE(maybeLandingState);
                CHECK(*maybeLandingState == TestStates::third);
            }
        }
    }
}
