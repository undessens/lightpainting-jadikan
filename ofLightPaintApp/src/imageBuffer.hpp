//
//  imageBuffer.hpp
//  ofLightPaintApp
//
//  Created by Admin Mac on 18/12/2019.
//

#ifndef imageBuffer_hpp
#define imageBuffer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

class ImageBuffer
{
    
public:
    
    ImageBuffer();
    ImageBuffer( ofParameterGroup* pg, int w, int h, int nbImage);
    void setup();
    void update(ofFbo* input);
    void draw(int, int, int ,int ); // draw all active images
    void draw(ofRectangle r ); // draw all active images
    void resetBuffer(bool &isReset);
    
    int w;
    int h;
    int nbImage;
    ofFbo fbo; // Will change to an array on fbo, according to each image
    ofParameterGroup* pg;
    ofParameter<int> currentImage;
    ofParameter<int> darkerInTime;
    ofParameter<int> opacityAtDraw;
    ofParameter<bool> reset;
    
    
};

#endif /* imageBuffer_hpp */
