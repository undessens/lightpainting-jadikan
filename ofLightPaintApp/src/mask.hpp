//
//  mask.hpp
//  ofLightPaintApp
//
//  Created by Admin Mac on 18/12/2019.
//

#ifndef mask_hpp
#define mask_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

class Mask
{
    
public:
    
    Mask();
    Mask( ofParameterGroup* pg, int w, int h);
    void setup();
    void update(ofFbo* input);
    void draw(int, int, int ,int ); // draw all active images
    void draw(ofRectangle r ); // draw all active images

    
    int w;
    int h;
    ofImage img;
    ofFbo fbo; // Will change to an array on fbo, according to each image
    ofParameterGroup* pg;
    ofParameter<int> imageIndex;
    ofParameter<bool> clear;
    
    
};

#endif /* mask_hpp */
