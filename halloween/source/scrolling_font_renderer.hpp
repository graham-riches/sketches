/**
 * \file scrolling_font_renderer.hpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief Font renderer that shifts the image a set pixel offset horizontally on every frame update
 *        to create a scrolling effect
 * \version 0.1
 * \date 2021-02-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/********************************** Includes *******************************************/
#include "font.hpp"
#include "primatives.hpp"
#include <vector>
#include <chrono>

namespace graphics
{
/**
 * \brief shape type that handles drawing bitmapped fonts
 */
struct scrolling_font_renderer : public shape {
    /**
     * \brief Construct a new scrolling font renderer object
     * 
     * \param characters characters to render
     * \param scroll_rate_ms how fast to scroll the text (time in millseconds per pixel shift)
     * \param origin the XY coordinates of the message origin, which is where is scrolls into (disappears at)
     * \param color the message color
     */
    scrolling_font_renderer(const std::vector<fonts::character>& characters, uint32_t scroll_rate_ms, graphics::origin origin, graphics::color color);

    /**
     * \brief render a sequence of characters on the screen. Each successive call to draw
     *        will update the scrolling view if enough time has elapsed.
     * 
     * \param canvas existing frame canvas
     * \retval the drawing frame
     */
    frame& draw(frame& canvas);

    /**
     * \brief Helper to check if the image has been drawn completely
     * 
     * \retval true if the entire message has been printed
     */
    bool message_completed() const;

    //!< Members
    const std::vector<fonts::character>& m_characters;
    uint32_t m_shift_rate_ms;
    graphics::color m_color;
    uint32_t m_pixel_offset;
    uint32_t m_total_message_length;
    std::chrono::time_point<std::chrono::system_clock> m_last_draw_time;
};

};  // namespace graphics