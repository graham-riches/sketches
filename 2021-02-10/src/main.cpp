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
    //!< let open frameworks handle setting up OpenGL
    ofSetupOpenGL(1024, 768, OF_WINDOW);

    //!< start the application event loop
    auto app = std::make_unique<ofApp>();
    ofRunApp(app.get());
}
