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

#include <filesystem>
#include <algorithm>
#include "ofApp.h"

/**
 * @brief 
 * 
*/
void ofApp::setup(){
    //!< I hate pathing...
    auto path = std::filesystem::current_path();
    auto parent_path = path.parent_path();
    std::filesystem::path shader_path = parent_path / std::filesystem::path{"shaders"};    
    _shader.load(shader_path / std::filesystem::path{"shadersGL3/shader"});


    _image.allocate(80, 60, OF_IMAGE_GRAYSCALE);

    int planeWidth = ofGetWidth();
    int planeHeight = ofGetHeight();
    int planeGridSize = 10;
    int planeColums = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;
        
    _plane.set(800, 600, 80, 60, OF_PRIMITIVE_TRIANGLES);
    _plane.mapTexCoordsFromTexture(_image.getTexture());
}

/**
 * @brief 
*/
void ofApp::update(){
    ofPixels& pixels = _image.getPixels();
    const auto width = _image.getWidth();
    const auto height = _image.getHeight();
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            pixels[static_cast<long long int>(row * width + column)] = sin(ofGetElapsedTimef()*column)*255;
        }
    }
    _image.update();

}

/**
 * @brief 
*/
void ofApp::draw(){
    //!< bind the texture to the shader
    _image.getTexture().bind();

    //!< start the shader
    _shader.begin();

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
    _shader.end();
}

void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::mouseEntered(int x, int y) {}

void ofApp::mouseExited(int x, int y) {}