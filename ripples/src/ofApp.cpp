/**
 * \file ofApp.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief 
 * \version 0.1
 * \date 2021-02-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/********************************** Includes *******************************************/
#include "ofApp.h"
#include <filesystem>


/********************************** Function Definitions *******************************************/
/**
 * \brief Construct a new application::application object
 * 
 * \param width width of the wireframe in grid tiles
 * \param height height of the wireframe in grid tiles
 */
application::application(int width, int height) 
: _width(width)
, _height(height) {
    _image.allocate(height, width, OF_IMAGE_GRAYSCALE);
    _plane.set(1200, 900, height, height, OF_PRIMITIVE_TRIANGLES);
    _plane.mapTexCoordsFromTexture(_image.getTexture());
}

/**
 * \brief setup function to load shaders and other objects
 */
void application::setup() { 
    auto path = std::filesystem::current_path();
    auto parent_path = path.parent_path();
    std::filesystem::path shader_path = parent_path / std::filesystem::path{"shaders"};
    _displacement_shader.load(shader_path / std::filesystem::path{"shadersGL3/shader"});    
}


/**
 * \brief update method to draw a new frame
 */
void application::update() {     
    //!< update the image to draw it
    ofPixels& pixels = _image.getPixels();
    const auto width = _image.getWidth();
    const auto height = _image.getHeight();        
    for ( uint64_t row = 0; row < height; row++ ) {
        for ( uint64_t column = 0; column < width; column++ ) {
            pixels[row * static_cast<int>(width) + column] = 255;
        }
    }
    _image.update();    
}


/**
 * \brief renders the image to the screen
 */
void application::draw() { 
    //!< bind the texture to the shader
    _image.getTexture().bind();    

    //!< start the shader
    _displacement_shader.begin();    

    //!< push the current local coordinate system to move to a new relative one
    ofPushMatrix();

    //!< translate the plane into the center of the screen
    auto center_x = ofGetWidth() / 2.0;
    auto center_y = ofGetHeight() / 2.0;
    ofTranslate(center_x, center_y);

    //!< rotate it to a more isometric view
    auto rotation = ofMap(0.30, 0, 1, -60, 60, true) + 60;
    ofRotateDeg(rotation, 1, 0, 0);

    //!< draw the wireframe
    _plane.drawWireframe();

    ofPopMatrix();
    _displacement_shader.end();
}


/********************************** Unused Openframeworks API Functions *******************************************/
void application::keyPressed(int key) { }
void application::keyReleased(int key) { }
void application::mouseMoved(int x, int y) { }
void application::mouseDragged(int x, int y, int button) { }
void application::mousePressed(int x, int y, int button) { }
void application::mouseReleased(int x, int y, int button) { }
void application::mouseEntered(int x, int y) { }
void application::mouseExited(int x, int y) { }
void application::windowResized(int w, int h) { }
void application::gotMessage(ofMessage msg) { }
void application::dragEvent(ofDragInfo dragInfo) { }
