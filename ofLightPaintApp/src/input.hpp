//
//  input.hpp
//  ofLightPaintApp
//
//  Created by Admin Mac on 18/12/2019.
//

#ifndef input_hpp
#define input_hpp

#include <stdio.h>
#include "ofxBlackMagic.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"


/*
 
 Conclusion, on peut bien déssiner un shader, à l'intérieur d'un fbo.
 Puis venir donner le pointeur de se fbo.
 
 
*/

class Input
{
    
public:
    
    Input();
    Input( ofParameterGroup* pg, int w, int h);
    void setup();
    void loadMovie(string name);
    void update();
    void setUseVideo(bool &isUse);
    void setVideoIndex(int &newIndex);
    void setVideoPause(bool &isPause);
    
    int w;
    int h;
    ofFbo fbo;
    ofParameterGroup* pg;
    ofVideoPlayer player;
    ofParameter<bool> useOfVideoPlayer;
    ofParameter<bool> playerPause;
    ofParameter<int> videoIndex;
    ofParameter<float> threshold;
    ofParameter<float> smooth;
    ofShader shader;
    
    
};
    


/*
 
 ofxBlackMagic cam;
 cam.setup(1920, 1080, 30);
 cam.drawColor();
 
 */


#endif /* input_hpp */
