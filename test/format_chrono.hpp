#ifndef DANTEO_FORMAT_CHRONO_HPP
#define DANTEO_FORMAT_CHRONO_HPP

#include <fmt/chrono.h>

template <typename Clock, typename Rep>
std::ostream& operator<<(std::ostream& out, std::chrono::duration<Clock, Rep> const& duration) {
    return out << fmt::format("{}", duration);
}

#endif // DANTEO_FORMAT_CHRONO_HPP
