/**
 * \file ofApp.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief definitions for a simple open frameworks sketch app
 * \version 0.1
 * \date 2021-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ofApp.h"
#include <algorithm>
#include <filesystem>


/**
 * \brief constructor for game of life application
 * \param width width in tiles
 * \param height in tiles
 * \param wireframe_resolution how many wireframes per conway grid location
 * \param sample_rate time sample rate in ms
 * \param scale height scale for rendering
*/
application::application(int width, int height, int wireframe_resolution, uint64_t sample_rate, float scale)
: _conway(game_of_life{random_boolean_grid(height, width, grid_density)})
, _width(width)
, _height(height)
, _sample_rate_ms(sample_rate)
, _scale(scale)
, _last_sample_time(0)
{
    _image.allocate(height, width, OF_IMAGE_GRAYSCALE);
    _plane.set(1200, 900, height*wireframe_resolution, height*wireframe_resolution, OF_PRIMITIVE_TRIANGLES);
    _plane.mapTexCoordsFromTexture(_image.getTexture());
}   

/**
 * \brief open frameworks setup function that runs prior to the main event loop
 */
void application::setup() {    
    auto path = std::filesystem::current_path();
    auto parent_path = path.parent_path();
    std::filesystem::path shader_path = parent_path / std::filesystem::path{"shaders"};
    _displacement_shader.load(shader_path / std::filesystem::path{"shadersGL3/shader"});
    
    _plane.set(800, 600, 160, 120, OF_PRIMITIVE_TRIANGLES);
    _plane.mapTexCoordsFromTexture(_image.getTexture());
}

/**
 * \brief frame update method
 */
void application::update() {
    const auto elapsed_time_ms = ofGetElapsedTimeMillis();
    if ((elapsed_time_ms - _last_sample_time) / _sample_rate_ms) {
        //!< update timestamp
        _last_sample_time = elapsed_time_ms;

        //!< get the next generation
        auto current_generation = _conway.next_generation();
        
        //!< update the image to draw it
        ofPixels& pixels = _image.getPixels();
        const auto width = _image.getWidth();
        const auto height = _image.getHeight();        
        for ( uint64_t row = 0; row < height; row++ ) {
            for ( uint64_t column = 0; column < width; column++ ) {
                pixels[row * static_cast<int>(width) + column] = current_generation[row][column]*255;
            }
        }
        _image.update();
    }
}

/**
 * \brief main method to render the scene
 */
void application::draw() {
    //!< bind the texture to the shader
    _image.getTexture().bind();
    
    auto time = ofGetElapsedTimef();
    auto percent_y = ofClamp(sin(time), 0, 1) * _scale;

    //!< start the shader
    _displacement_shader.begin();

    _displacement_shader.setUniform1f("scale", percent_y);

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

void application::keyPressed(int key) { }

void application::keyReleased(int key) { }

void application::mouseMoved(int x, int y) { }

void application::mouseDragged(int x, int y, int button) { }

void application::mousePressed(int x, int y, int button) { }

void application::mouseReleased(int x, int y, int button) { }

void application::windowResized(int w, int h) { }

void application::gotMessage(ofMessage msg) { }

void application::dragEvent(ofDragInfo dragInfo) { }

void application::mouseEntered(int x, int y) { }

void application::mouseExited(int x, int y) { }