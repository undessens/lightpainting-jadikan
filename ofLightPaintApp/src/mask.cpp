//
//  mask.cpp
//  ofLightPaintApp
//
//  Created by Admin Mac on 18/12/2019.
//

#include "mask.hpp"

/*
 
 Le mask est un fichier image, ajouté au résultat en multiply. Avec une option d'aperçu.
 
 */

//--------------------------------------------------------------
Mask::Mask(){
    
    
    
    
}



//--------------------------------------------------------------
Mask::Mask( ofParameterGroup* _pg, int _w, int _h){
    
    pg = _pg;
    w = _w;
    h = _h;
    setup();
    
}

//--------------------------------------------------------------
void Mask::setup(){
    
    img.load("palme.jpg");
    imageIndex = 1;
    
    pg->setName("Mask");
    pg->add(imageIndex.set("image index",0, 0, 1));
    
    // FBO CLEAR
    fbo.allocate(w, h, GL_RGBA);
    fbo.begin();
    ofClear(0,0,0, 0);
    fbo.end();
    
}

//--------------------------------------------------------------
void Mask::update(ofFbo *input){
    
    
    
    fbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if(imageIndex>0){
    
        
        img.draw(0, 0, w, h);
        ofSetColor(255, 255, 255,255);
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    }
   
    input->draw(0,0);
    
    ofDisableBlendMode();
    fbo.end();
    
}

//--------------------------------------------------------------
void Mask::draw(int x,int  y, int w, int h){
    
    fbo.draw(x, y, w, h);
    
}

//--------------------------------------------------------------
void Mask::draw(ofRectangle rec){
    
    fbo.draw(rec);
    
}
