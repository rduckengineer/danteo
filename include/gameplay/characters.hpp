#ifndef DANTEO_CHARACTERS_HPP
#define DANTEO_CHARACTERS_HPP

#include "gameplay/danteo_page_request.hpp"

namespace danteo::characters {
constexpr Character You{"You", RGB{220, 220, 220}};
constexpr Character Virgil{"Virgil", RGB{230, 150, 10}};
constexpr Character PM{"Cerberus", RGB{135, 230, 10}};
constexpr Character BitterSenior{"BS", RGB{230, 100, 10}};
constexpr Character DustyDev{"Dustin", RGB{150, 150, 200}};
constexpr Character FuncBro{"Alonzo", RGB{150, 200, 150}};
// constexpr Character NoProblemo{"NP", RGB{150, 200, 150}};
//[[maybe_unused]] constexpr Character QAGuy{"QA"};
} // namespace danteo::characters

#endif // DANTEO_CHARACTERS_HPP
