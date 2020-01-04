//
//  input.cpp
//  ofLightPaintApp
//
//  Created by Admin Mac on 18/12/2019.
//

#include "input.hpp"

//--------------------------------------------------------------
Input::Input(ofParameterGroup* _pg,
                         int _w,
                         int _h
                         ){
    
    
    pg = _pg;
    w = _w;
    h = _h;
    setup();
    
}

//--------------------------------------------------------------
void Input::setup(){
    
    useOfVideoPlayer.addListener(this,&Input::setUseVideo);
    videoIndex.addListener(this, &Input::setVideoIndex);
    playerPause.addListener(this, &Input::setVideoPause);
    
    // GUI MANAGEMENT
    pg->add(useOfVideoPlayer.set("use of video", true));
    pg->add(videoIndex.set("video index", 1, 1, 3));
    pg->add(threshold.set("threshold", 0.1,0, 10.0));
    pg->add(smooth.set("smooth threshold", 0, 0, 5));
    pg->add(playerPause.set("Video Pause", false));
    
    // FBO CLEAR
    fbo.allocate(w, h, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    // SHADER
#ifdef TARGET_OPENGLES
    //shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        //shader.load("shadersGL3/shader");

    }else{
        shader.load("shadersGL2/shader");

    }
#endif
    
    //shader.setUniformTexture("text0", fbo.getTexture(), 0);

    
    
}

//--------------------------------------------------------------
void Input::loadMovie(string name){
    
    player.load(name);
    player.play();
    
}

//--------------------------------------------------------------
void Input::update(){
    
 
     
    
    
    fbo.begin();
    ofClear(255,255,255, 0);
    shader.begin();
    shader.setUniform1f("squared_threshold", threshold);
    shader.setUniform1f("squared_smooth", smooth);
    if(useOfVideoPlayer){
        player.update();
        ofSetColor(255, 255, 255, 255);
        player.draw(0, 0, w, h);
        
    }else{
        // USE of camera from black magic
        ofSetColor(0, 255, 0, 255);
        ofFill();
        ofDrawRectangle(0, 0, w, h);
    }
    shader.end();
    fbo.end();
    
    
    
}

//--------------------------------------------------------------
void Input::setUseVideo(bool &isUse){
    
    if(isUse){
        
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();
        player.stop();
        player.firstFrame();
        player.play();
        
    }else{
        
        player.stop();
        fbo.begin();
        ofClear(0, 255, 0, 127);
        fbo.end();
    }
    
}


//--------------------------------------------------------------
void Input::setVideoIndex(int &newIndex){
    
    ofFile myFile;
    myFile.open(ofToString(newIndex)+".mp4");
    if(myFile.exists()){
        ofLog(OF_LOG_NOTICE, "checking video : TRUE");
    }
    else{
        ofLog(OF_LOG_NOTICE, "checking video : FALSE");
        myFile.open("clouds.mov");
    }
    
    player.load(myFile.path());
    player.setLoopState(OF_LOOP_NORMAL);
    player.play();
    
    
}

//--------------------------------------------------------------
void Input::setVideoPause(bool &isPause){
    
    player.setPaused(isPause);
    
}


