/**
 * \file font_renderer.hpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief contains rendering functionality for BDF fonts
 * \version 0.1
 * \date 2021-02-09
 * 
 * @copyright Copyright (c) 2021
 * 
 * \details Note this is probably going to be moved around and restructured once the graphics library
 *          starts to come together in my head. Just putting some thoughts down now to see what shakes loose.
 */

#pragma once

/********************************** Includes *******************************************/
#include "font.hpp"
#include "primatives.hpp"
#include <vector>

namespace graphics
{
/********************************** Types *******************************************/
/**
 * \brief options for handling string wrapping
 * 
 */
enum class text_wrap_mode : unsigned { none = 0, wrap };

/**
 * \brief shape type that handles drawing bitmapped fonts
 */
struct font_renderer : public shape {
    /**
     * \brief Construct a new font renderer object
     * 
     * \param characters characters to render
     * \param origin origin to render at
     * \param color the color to draw the text in
     * \param mode the text wrap mode
     */
    font_renderer(const std::vector<fonts::character>& characters,
                  graphics::origin origin,
                  graphics::color color,
                  text_wrap_mode mode = text_wrap_mode::none);

    /**
     * \brief render a sequence of characters on the screen
     * 
     * \param canvas existing frame canvas
     * \retval the drawing frame
     */
    frame& draw(frame& canvas);

    const std::vector<fonts::character>& characters;
    graphics::color color;
    text_wrap_mode wrap_mode;
};

};  // namespace graphics