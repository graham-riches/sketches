/**
 * \file animation.hpp
 * \author Graham Riches
 * \brief Halloween board sequence / animations
 * \version 0.1
 * \date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "graphics.hpp"
#include "font.hpp"

class animation {
  public:
    /**
     * \brief Construct a new animation object
     * 
     * \param frame The graphics frame
     * \param fone The font to use
     */
    animation(graphics::frame& frame, fonts::font& font);

    /**
     * \brief Run animation sequence
     */
    void run();

  private:
    //!< Display methods
    void display_image(const std::string& path, uint32_t time_ms);
    void scroll_text(const std::string& message);

    //!< Members
    graphics::frame& m_frame;
    fonts::font& m_font;
};