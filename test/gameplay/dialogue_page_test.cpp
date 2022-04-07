#include "gameplay/pages/dialogue_page.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

// NOLINTNEXTLINE[readability-function-cognitive-complexity]
SCENARIO("A DialogueLine describes one line of dialogue") {
    GIVEN("A character") {
        static constexpr danteo::Character kenobi{"General Kenobi"sv};

        THEN("The character has the correct name") {
            STATIC_REQUIRE(kenobi.name == "General Kenobi"sv);
        }

        AND_GIVEN("Some text and its alignment") {
            static constexpr auto line = "Hello there."sv;
            static constexpr auto aligned{danteo::DialogueLine::Aligned::Left};

            THEN("The DialogueLine contains all three") {
                static constexpr danteo::DialogueLine dialogueLine{
                    .character = kenobi, .line = line, .aligned = aligned};

                STATIC_REQUIRE(dialogueLine.character == kenobi);
                STATIC_REQUIRE(dialogueLine.line == line);
                STATIC_REQUIRE(dialogueLine.aligned == aligned);
            }
        }
    }
}

// NOLINTNEXTLINE[readability-function-cognitive-complexity]
SCENARIO("A DialoguePage defines a sequence of lines of dialogue") {
    GIVEN("Two characters") {
        static constexpr danteo::Character kenobi{"General Kenobi"sv};
        static constexpr danteo::Character grievous{"General Grievous"sv};

        AND_GIVEN("Their dialogue lines") {
            using danteo::DialogueLine;
            static constexpr DialogueLine line1{
                kenobi, "Hello there."sv, DialogueLine::Aligned::Left};
            static constexpr danteo::DialogueLine line2{
                grievous, "General Kenobi!"sv, DialogueLine::Aligned::Right};

            AND_GIVEN("The next event") {
                static constexpr danteo::engine::Event event{"Next"sv};

                danteo::DialoguePage page{event, std::vector{line1, line2}};

                THEN("The dialogue page holds them in the correct order") {
                    CHECK(page.lines.size() == 2);
                    CHECK(page.lines[0] == line1);
                    CHECK(page.lines[1] == line2);
                }

                THEN("The next event is the correct one") { CHECK(page.nextEvent == event); }
            }
        }
    }
}
