#pragma once

#include "ofMain.h"
#include "ofxOscParameterSync.h"
#include "ofxGui.h"
#include "input.hpp"
#include "imageBuffer.hpp"

class ofApp : public ofBaseApp{

    public:
    
    void setup();
    void update();
    void draw();
    void updateZoom();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    //GUI
    ofxPanel gui;
    ofxOscParameterSync sync;
    ofParameterGroup pg;
    ofParameterGroup pg_input;
    ofParameterGroup pg_imageBuffer;
    ofParameterGroup pg_videoBuffer;
    ofParameterGroup pg_mask;
    ofParameterGroup pg_fx;
    ofParameterGroup pg_output;
    ofParameter<int> bg_color;
    
    //IMAGE parameter
    int input_w;
    int input_h;
    int output_w;
    int output_h;
    
    //Instance
    Input*  input;
    ImageBuffer* imageBuffer;
    
    //Draw video on rectangle
    ofRectangle vignetteInput;
    ofRectangle vignetteBuffer;
    ofRectangle vignetteZoom;
    
    //Zoom : TODO, dedicated class is needed
    ofRectangle zoomRectangle;
    ofPixels zoomPixels;
    ofImage zoomImage;
    int zoomLevelEntry;
    
    
    
    
		
};
