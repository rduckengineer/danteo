#include "engine/state_machine.hpp"
#include "engine/state_graph_builder.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

namespace {
constexpr danteo::State young{"Young"sv};
constexpr danteo::State old{"Old"sv};
constexpr danteo::State heaven{"Heaven"sv};
constexpr danteo::State hell{"Hell"sv};

constexpr danteo::Event growOld{"GrowOld"sv};
constexpr danteo::Event die{"Die"sv};
constexpr danteo::Event respawn{"Respawn"};

auto const graph = [](bool& hasBeenNice) {
    danteo::StateGraph::Builder builder{};
    builder / young + growOld                          = old;
    builder / old + die | [&] { return hasBeenNice; }  = heaven;
    builder / old + die | [&] { return !hasBeenNice; } = hell;
    builder / heaven + respawn                         = young;
    return std::move(builder).build();
};
} // namespace

// NOLINTNEXTLINE readability-function-cognitive-complexity
SCENARIO("A State Machine manages the current state") {
    GIVEN("A state machine containing a graph") {
        bool hasBeenNice = true;

        danteo::StateMachine stateMachine{graph(hasBeenNice), young};

        THEN("The initial state matches the one given at construction") {
            CHECK(stateMachine.state() == young);
        }

        WHEN("Trying to perform an invalid transition") {
            auto newState = stateMachine.when(die);
            THEN("Does nothing") {
                CHECK_FALSE(newState.has_value());
                CHECK(stateMachine.state() == young);
            }
        }

        WHEN("Trying to perform a valid transition") {
            auto newState = stateMachine.when(growOld);
            THEN("The current state moves to the transition's landing state") {
                REQUIRE(newState.has_value());
                CHECK(*newState == old);
                CHECK(stateMachine.state() == old);
            }
        }

        SECTION("The graph can move from state to state") {
            CHECK(stateMachine.state() == young);

            stateMachine.when(growOld);
            CHECK(stateMachine.state() == old);

            hasBeenNice = true; // NOLINT not actually a dead store
            stateMachine.when(die);
            CHECK(stateMachine.state() == heaven);

            stateMachine.when(respawn);
            CHECK(stateMachine.state() == young);

            stateMachine.when(growOld);
            CHECK(stateMachine.state() == old);

            hasBeenNice = false; // NOLINT reassignment
            stateMachine.when(die);
            CHECK(stateMachine.state() == hell);

            stateMachine.when(respawn);
            CHECK(stateMachine.state() == hell); // stuck for eternity...
        }
    }
}
