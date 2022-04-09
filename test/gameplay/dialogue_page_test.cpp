#include "gameplay/pages/dialogue_page_builder.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

// NOLINTNEXTLINE[readability-function-cognitive-complexity]
SCENARIO("A DialogueLine describes one line of dialogue") {
    GIVEN("A character") {
        static constexpr danteo::Character kenobi{"General Kenobi"sv, danteo::HSV{0, 0, 255}};

        THEN("The character has the correct name") {
            STATIC_REQUIRE(kenobi.name == "General Kenobi"sv);
        }

        AND_GIVEN("Some text and its alignment") {
            std::string           line{"Hello there."};
            static constexpr auto aligned{danteo::DialogueLine::Aligned::Left};

            THEN("The DialogueLine contains all three") {
                danteo::DialogueLine const dialogueLine{
                    .character = kenobi, .line = line, .aligned = aligned};

                CHECK(dialogueLine.character == kenobi);
                CHECK(dialogueLine.line == line);
                CHECK(dialogueLine.aligned == aligned);
            }
        }
    }
}

// NOLINTNEXTLINE[readability-function-cognitive-complexity]
SCENARIO("A DialoguePage defines a sequence of lines of dialogue") {
    GIVEN("Two characters") {
        static constexpr danteo::Character kenobi{"General Kenobi"sv, danteo::RGB{0, 0, 255}};
        static constexpr danteo::Character grievous{"General Grievous"sv, danteo::RGB{255, 0, 0}};

        AND_GIVEN("Their dialogue lines") {
            std::string const helloThere    = "Hello there.";
            std::string const generalKenobi = "General Kenobi!";

            danteo::DialoguePage page{
                // clang-format off
                danteo::DialogueBuilder::place(kenobi).left().andPlace(grievous).right()
                    .then(kenobi).says(helloThere)
                    .then(grievous).says(generalKenobi)
                //clang-format on
            };

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
