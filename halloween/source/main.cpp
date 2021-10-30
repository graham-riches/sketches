/**
 * \file main.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \version 0.1
 * \date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/********************************** Includes *******************************************/
#include "canvas.h"
#include "config_parser.hpp"
#include "expected.hpp"
#include "animation.hpp"
#include "graphics.hpp"
#include "led-matrix.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

/********************************** Types and Aliases *******************************************/
using json = nlohmann::json;

/****************************** Function Definitions ***********************************/
/**
 * \brief main application entry point.
 * 
 * \param argc number of command line arguments
 * \param argv space delimited command line arguments
 * \retval int process return value
 */
int main(int argc, char* argv[]) {
    // load and parse configuration
    json config = json::parse(std::ifstream{"/home/pi/halloween/config.json"});
    auto maybe_options = create_options_from_json(config);
    auto options = maybe_options.get_value();

    // load a font file
    auto maybe_font = fonts::font::from_stream(std::ifstream{std::string{"/home/pi/halloween/fonts/7x13B.bdf"}});
    auto font = maybe_font.get_value();

    //!< create the RGB Matrix object from the validated options.
    auto matrix = std::unique_ptr<rgb_matrix::RGBMatrix>(rgb_matrix::CreateMatrixFromOptions(options.options, options.runtime_options));
    matrix->StartRefresh();  //!< unfortunately this manages it's own pthread :(

    //!< Start the animation
    auto frame = graphics::frame(matrix.get());
    animation animation(frame, font);
    while (true) {
        animation.run();
    }

    return 0;
}
