/**
 * \file main.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief main OF sketch startup
 * \version 0.1
 * \date 2021-02-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/********************************** Includes *******************************************/
#include "ofMain.h"
#include "ofApp.h"
#include <memory>

/********************************** Function Definitions *******************************************/
/**
 * \brief main application startup function
 * 
 * \param argc number of CLI arguments
 * \param argv list of arguments
 * \retval int 
 */
int main(int argc, char* argv[] ){
    ofGLWindowSettings window_settings;
    window_settings.setGLVersion(3, 2);
    window_settings.setSize(1600, 1200);
    ofCreateWindow(window_settings);
    auto app = std::make_unique<application>(160, 160);
    ofRunApp(app.get());
}
