#ifndef DANTEO_COLOR_FTXUI_HPP
#define DANTEO_COLOR_FTXUI_HPP

#include "user_interface/color.hpp"
#include "ftxui/screen/color.hpp"

namespace danteo::convert {
inline ftxui::Color toFTX(HSV color) {
    return ftxui::Color::HSV(color.hue, color.saturation, color.value);
}

inline ftxui::Color toFTX(RGB color) {
    return ftxui::Color::RGB(color.red, color.green, color.blue);
}

inline ftxui::Color toFTX(Color color) {
    return std::holds_alternative<HSV>(color)
             ? toFTX(std::get<HSV>(color))
             : toFTX(std::get<RGB>(color));
}
} // namespace danteo::convert

#endif // DANTEO_COLOR_FTXUI_HPP
