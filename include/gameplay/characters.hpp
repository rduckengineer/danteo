#ifndef DANTEO_CHARACTERS_HPP
#define DANTEO_CHARACTERS_HPP

#include "gameplay/danteo_page_request.hpp"

namespace danteo::characters {
constexpr Character You{"You", RGB{220, 220, 220}};
constexpr Character Virgil{"Virgil", RGB{230, 150, 10}};
constexpr Character PM{"Cerberus", RGB{135, 230, 10}};
constexpr Character BitterSenior{"BS", RGB{230, 100, 10}};
/*[[maybe_unused]] constexpr Character DustyDev{"Dustin"};
[[maybe_unused]] constexpr Character FuncBro{"Alonzo"};
[[maybe_unused]] constexpr Character NoProblemo{"NP"};
[[maybe_unused]] constexpr Character QAGuy{"QA"};*/
} // namespace danteo::characters

#endif // DANTEO_CHARACTERS_HPP
