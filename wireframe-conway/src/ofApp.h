/**
 * \file ofApp.h
 * \author Graham Riches (graham.riches@live.com)
 * \brief definitions for a simple open-frameworks sketch app
 * \version 0.1
 * \date 2021-02-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/********************************** Includes *******************************************/
#include "ofMain.h"
#include "conway.h"
#include <cstdint>

/********************************** Constants *******************************************/
constexpr int grid_density = 20;

/********************************** Types *******************************************/
class application : public ofBaseApp {
  public:
    application(int width, int height, int wireframe_resolution = 2, uint64_t sample_rate = 100, float scale=40);

    //!< open frameworks application interface functions
    void setup();
    void update();
    void draw();
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
    game_of_life _conway;    
    int _width;
    int _height;
    float _scale;
    uint64_t _sample_rate_ms;
    uint64_t _last_sample_time;
};
