#include "office_space_scene.hpp"

#include "engine/state_to_page_request_map_builder.hpp"

#include "gameplay/pages/scene_change_page.hpp"
#include "gameplay/pages/dialogue_page_builder.hpp"

#include "gameplay/characters.hpp"

namespace danteo::scenes {
using namespace characters;
namespace {
DialoguePageWithChoice makeMeetTheTeamPage();
DialoguePageWithChoice makeOkayPage();
DialoguePageOnly       makeFmtPrintPage();
DialoguePageOnly       makeGlobalPage();
} // namespace

// NOLINTNEXTLINE not static to keep options open
void OfficeScene::addScene(DanteoStateToPageMap::Builder& builder) const {

    builder << SceneStates::officeScene << SceneChangePage{"Office Space", Events::next};

    builder << SceneStates::meetTheTeam << makeMeetTheTeamPage();
    builder << SceneStates::ooookay << makeOkayPage();
    builder << SceneStates::fmtPrint << makeFmtPrintPage();
    builder << SceneStates::aGlobal << makeGlobalPage();
}

namespace {
using SceneEvents = OfficeScene::SceneEvents;

DialoguePageWithChoice makeMeetTheTeamPage() {
    return {
        {// clang-format off
DialogueBuilder::place(BitterSenior).left()
    .andPlace(DustyDev).left()
    .andPlace(FuncBro).left()
             // clang-format on

             .then(BitterSenior)
             .says("Well, here's the H-team. The A-team but from Hell 'cause we're... Well. "
                   "You get the idea. Team, meet the rookie.")

             .then(FuncBro)
             .says("[](auto const& name) { return concat(\"Sup! \", name); }")

             .then(DustyDev)
             .says(R"(printf("Hello %s\n", g_pszRookieName);)")

        },
        std::vector<std::string>{"... Okay.", "`fmt::print`", "A global, really?"},
        std::vector<engine::Event>{SceneEvents::okay, SceneEvents::fmtPrint, SceneEvents::globals}};
}

DialoguePageWithChoice makeOkayPage() {
    return {{// clang-format off
             DialogueBuilder::place(BitterSenior).left()
                 .andPlace(You).right()
                 // clang-format on

                 .then(You)
                 .says("Okay..?")

                 .then(BitterSenior)
                 .says("Well, you could say hi back.")

            },
            std::vector<std::string>{"`fmt::print`", "A global, really?"},
            std::vector<engine::Event>{SceneEvents::fmtPrint, SceneEvents ::globals}};
}

DialoguePageOnly makeFmtPrintPage() {
    return {
        {// clang-format off
         DialogueBuilder::place(FuncBro).left()
             .andPlace(You).right()
             .andPlace(DustyDev).left()
             // clang-format on

             .then(You)
             .says("fmt::print(\"Hi team!\");")

             .then(FuncBro)
             .says("Wow! Sweet side effects you've got there! Haha!")

             .then(DustyDev)
             .says("Oh yeah? Because you're not mutating your programmers' minds when making them "
                   "think of useless recursive functions instead of perfectly good nested loops, "
                   "riiight?!")

             .then(FuncBro)
             .says("You're just sad because you can't compose monads to make new versions of "
                   "the world.")

             .then(DustyDev)
             .says("YOUR COPIES ARE FRAGMENTING MY MEMORY PAGES!")

             .then(DustyDev)
             .says("Ugh! Come rookie, let's pair, we don't need to stay around His Highness's "
                   "misplaced sense of purity.")

        },
        Events::next};
}

DialoguePageOnly makeGlobalPage() {
    return {
        {// clang-format off
             DialogueBuilder::place(You).right()
                 .andPlace(DustyDev).left()
                 .andPlace(FuncBro).left()
             // clang-format on

             .then(You)
             .says("Is my name in a global?")

             .then(DustyDev)
             .says("Yes, it's more efficient that way.")

             .then(You)
             .says("More effic- Wait, is that Hungarian notation?")

             .then(DustyDev)
             .says("Yes! I see you know your classics!")

             .then(FuncBro)
             .says("Forget him, he's still writing like it's the 80s. Yes, we want to make "
                   "programmers suffer, but I'll show you how to do it with *style*")

        },
        Events::next};
}
} // namespace
} // namespace danteo::scenes
