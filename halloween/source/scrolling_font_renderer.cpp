/**
 * \file scrolling_font_renderer.cpp
 * \author Graham Riches
 * \version 0.1
 * \date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "scrolling_font_renderer.hpp"
#include <chrono>

namespace graphics {

scrolling_font_renderer::scrolling_font_renderer(const std::vector<fonts::character>& characters,
                                                 uint32_t scroll_rate_ms,
                                                 graphics::origin origin,
                                                 graphics::color color)
    : shape(origin)
    , m_characters(characters)
    , m_shift_rate_ms(scroll_rate_ms)
    , m_color(color)
    , m_pixel_offset(0)
    , m_total_message_length(0)
    , m_last_draw_time(std::chrono::system_clock::now()) {
    if ( characters.size() > 0 ) {
        auto ch = characters[0];
        auto bbox = ch.properties.b_box;
        m_total_message_length = m_characters.size() * bbox.width;
    }
}

frame& scrolling_font_renderer::draw(frame& canvas) {
    auto current_time = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_last_draw_time);
    if ( elapsed.count() >= m_shift_rate_ms ) {
        m_last_draw_time = current_time;
        const auto width = canvas.width();
        int x_offset{0};

        for ( size_t character_count = 0; character_count < m_characters.size(); character_count++ ) {
            //!< get the current character
            auto character = m_characters[character_count];
            auto bbox = character.properties.b_box;
            auto alignment = (bbox.width % 8 == 0) ? (bbox.width / 8) : (bbox.width / 8) + 1;
            uint32_t pixel_alignment = alignment << 8ul;

            //!< draw the character
            for ( int j = 0; j < character.properties.b_box.height; j++ ) {
                for ( int i = 0; i < character.properties.b_box.width; i++ ) {
                    int x = _origin.x + x_offset + i - m_pixel_offset;
                    auto y = _origin.y + j;
                    if ( (character.bitmap[j] & (pixel_alignment >> i)) && (x >= _origin.x) ) {                        
                        canvas.set_pixel(x, y, m_color);
                    } else {
                        canvas.set_pixel(x, y, {0, 0, 0});
                    }
                }
            }

            //!< update the x-draw position for the next character
            x_offset += bbox.width;
        }
        m_pixel_offset++;
    }
    return canvas;
}

bool scrolling_font_renderer::message_completed() const {
    return (m_pixel_offset == m_total_message_length);
}

};