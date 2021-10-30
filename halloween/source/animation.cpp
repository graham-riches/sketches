/**
 * \file animation.cpp
 * \version 0.1
 * \date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "animation.hpp"
#include "bitmap_image.hpp"
#include <thread>

animation::animation(graphics::frame& frame, fonts::font& font)
    : m_frame(frame)
    , m_font(font) {}


void animation::run() {
    scroll_text(" HAPPY HALLOWEEN!");
    display_image("/home/pi/halloween/images/pumpkin.bmp", 5000);
    scroll_text(" TRICK OR TREAT!");
    display_image("/home/pi/halloween/images/ghosts.bmp", 5000);
    scroll_text(" ENTER IF YOU DARE!");
    display_image("/home/pi/halloween/images/skull.bmp", 5000);
}

void animation::display_image(const std::string& path, uint32_t time_ms) {
    m_frame.clear();
    bitmap_image img(path);
    for (unsigned i = 0; i < 64; ++i) {
        for (unsigned j = 0; j < 32; ++j) {
            uint8_t r, g, b;
            img.get_pixel(i, j, r, g, b);
            m_frame.set_pixel(i, j, r, g, b);
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

void animation::scroll_text(const std::string& message) {
    m_frame.clear();
    auto chars = m_font.encode_with_default(message, ' ');
    auto scroller = graphics::scrolling_font_renderer{chars, 70, graphics::origin{0, 9}, {255, 50, 0} };
    while (!scroller.message_completed()) {
        scroller.draw(m_frame);
    }
}
