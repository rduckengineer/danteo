#include "gameplay/pages/dialogue_page_builder.hpp"

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
            static constexpr auto helloThere    = "Hello there."sv;
            static constexpr auto generalKenobi = "General Kenobi!"sv;

            danteo::DialoguePage page{
                danteo::DialogueBuilder::place(kenobi)
                    .left()
                    .andPlace(grievous)
                    .right()
                    .then(kenobi)
                    .says(helloThere)
                    .then(grievous)
                    .says(generalKenobi)};

            THEN("The dialogue page holds them all and in the correct order") {

                CHECK(page.lines.size() == 2);

                CHECK(page.lines[0].character == kenobi);
                CHECK(page.lines[0].line == helloThere);
                CHECK(page.lines[0].aligned == danteo::DialogueLine::Aligned::Left);
                CHECK(page.lines[1].character == grievous);
                CHECK(page.lines[1].line == generalKenobi);
                CHECK(page.lines[1].aligned == danteo::DialogueLine::Aligned::Right);
            }
        }
    }
}
