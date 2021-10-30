/**
 * \file primatives.hpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief graphics primatives that are used to stitch together more complex scenes from basic objects
 * \version 0.1
 * \date 2021-02-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/********************************** Includes *******************************************/
#include "canvas.h"
#include <cstdint>
#include <utility>
#include <vector>

namespace graphics
{
/********************************** Types *******************************************/
/**
 * \brief structure containing the draw origin for a graphics primative.
 *        This is the top left coordinate of the image as the pixels map as
 *        row major, then column major
 */
struct origin {
    uint16_t x;
    uint16_t y;
};

/**
 * \brief structure containing the color RGB value of a pixel
 */
struct pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

//!< Alias pixel as a color struct for passing colors around more clearly
using color = pixel;

/**
 * \brief frame object that contains a 2D array of pixels that are drawn onto. 
 * \note this is an adapter for the canvas interface
 */
class frame {
  public:
    /**
     * \brief Construct a new frame object from a led matrix canvas pointer
     * 
     * \param canvas pointer to the canvas
     */
    frame(rgb_matrix::Canvas* canvas);

    /**
     * \brief Set a pixel value in the frame to the RGB values in the pixel argument
     * 
     * \param x coordinate to set at
     * \param y coordinate to set at
     * \param pixel color information to set
     */
    void set_pixel(int x, int y, const pixel& pixel);

    /**
     * \brief Set a pixel. Overload to meet the canvas interface
     * 
     * \param x location
     * \param y location
     * \param red pixel R value
     * \param green pixel G value
     * \param blue pixel B value
     */
    void set_pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);

    /**
     * \brief Get the width of the frame
     * 
     * \retval width as an integer
     */
    int width(void) const;

    /**
     * \brief Get the height of the frame
     * 
     * \retval height as an integer
     */
    int height(void) const;

    /**
     * \brief clear the canvas
     */
    void clear(void);

    /**
     * \brief fill the canvas all with a specific color
     * 
     * \param red R value
     * \param green G value
     * \param blue B value
     */
    void fill(uint8_t red, uint8_t green, uint8_t blue);

  private:
    rgb_matrix::Canvas* _canvas;
};

/**
 * \brief shape interface for drawing graphics primatives
 */
struct shape {
    origin _origin;

    shape(const origin& origin)
        : _origin(origin) { }

    virtual frame& draw(frame& canvas) = 0;
};

};  // namespace graphics
