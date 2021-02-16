/**
 * \file ofApp.h
 * \author Graham Riches (graham.riches@live.com)
 * \brief 
 * \version 0.1
 * \date 2021-02-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/********************************** Includes *******************************************/
#include "ofMain.h"

/********************************** Types *******************************************/
class application : public ofBaseApp {
  public:
    application(int width, int height);

    void setup();
    void update();
    void draw();

    //!< open frameworks base application interface functions
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

  private:
    ofShader _displacement_shader;
    ofPlanePrimitive _plane;
    ofImage _image;    
    int _width;
    int _height;
};
