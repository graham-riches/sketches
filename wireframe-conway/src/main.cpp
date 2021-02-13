/**
 * \file main.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief sketch of the day
 * \version 0.1
 * \date 2021-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/********************************** Includes *******************************************/
#include "ofApp.h"
#include "ofMain.h"
#include <memory>

/********************************** Functions *******************************************/
/**
 * @brief main sketch application 
 * @return 
*/
int main(int argc, char* argv[]) {    
    ofGLWindowSettings window_settings;
    window_settings.setGLVersion(3, 2);
    window_settings.setSize(1600, 1200);
    ofCreateWindow(window_settings);    

    //!< start the application event loop
    auto app = std::make_unique<application>(80, 60);
    ofRunApp(app.get());
}
