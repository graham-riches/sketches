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
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //!< I hate pathing...
    auto path = std::filesystem::current_path();
    auto parent_path = path.parent_path();
    std::filesystem::path shader_path = parent_path / std::filesystem::path{"shaders"};

#ifdef TARGET_OPENGLES
    shader.load(shader_path / std::filesystem::path{"shadersES2/shader"});
#else
    if(ofIsGLProgrammableRenderer()){
        _shader.load(shader_path / std::filesystem::path{"shadersGL3/shader"});
    }else{
        _shader.load(shader_path / std::filesystem::path{"shadersGL2/shader"});
    }
#endif

    int planeWidth = ofGetWidth();
    int planeHeight = ofGetHeight();
    int planeGridSize = 10;
    int planeColums = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;

    _plane.set(planeWidth, planeHeight, planeColums, planeRows, OF_PRIMITIVE_TRIANGLES);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    _shader.begin();

    // center screen.
    float cx = ofGetWidth() / 2.0;
    float cy = ofGetHeight() / 2.0;

    // the plane is being position in the middle of the screen,
    // so we have to apply the same offset to the mouse coordinates before passing into the shader.
    float mx = mouseX - cx;
    float my = mouseY - cy;

    // we can pass in a single value into the shader by using the setUniform1 function.
    // if you want to pass in a float value, use setUniform1f.
    // if you want to pass in a integer value, use setUniform1i.
    _shader.setUniform1f("mouseRange", 150);

    // we can pass in two values into the shader at the same time by using the setUniform2 function.
    // inside the shader these two values are set inside a vec2 object.
    _shader.setUniform2f("mousePos", mx, my);

    // color changes from magenta to blue when moving the mouse from left to right.
    float percentX = mouseX / (float)ofGetWidth();
    percentX = ofClamp(percentX, 0, 1);
    ofFloatColor colorLeft = ofColor::magenta;
    ofFloatColor colorRight = ofColor::blue;
    ofFloatColor colorMix = colorLeft.getLerped(colorRight, percentX);

    // create a float array with the color values.
    float mouseColor[4] = {colorMix.r, colorMix.g, colorMix.b, colorMix.a};

    // we can pass in four values into the shader at the same time as a float array.
    // we do this by passing a pointer reference to the first element in the array.
    // inside the shader these four values are set inside a vec4 object.
    _shader.setUniform4fv("mouseColor", mouseColor);

    ofTranslate(cx, cy);

    _plane.drawWireframe();

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