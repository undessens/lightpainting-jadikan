//
//  imageBuffer.cpp
//  ofLightPaintApp
//
//  Created by Admin Mac on 18/12/2019.
//


/*
 Contrairement à videoBuffer, imageBuffer, enregistre l'entiereté des frames dans un slot mémoire, qui est alors possible d'enregistrer en jpg en tant que image, d'afficher ou non.
Il est donc moins lourd en terme de mémoire, et permet typiquement d'enregistrer un petit dessin, une petite forme, dans une case mémoire temporaire ou un fichier jpeg.
 
 
*/

#include "imageBuffer.hpp"

//--------------------------------------------------------------
ImageBuffer::ImageBuffer(){}


//--------------------------------------------------------------
ImageBuffer::ImageBuffer( ofParameterGroup* _pg, int _w, int _h, int _nbImage){
    
    //Geometry
    pg = _pg;
    w = _w;
    h = _h;
    nbImage = _nbImage;
    setup();
    
    
}


//--------------------------------------------------------------
void ImageBuffer::setup(){
    
    // GUI MANAGEMENT
    
    reset.addListener(this, &ImageBuffer::resetBuffer);
    
    pg->add(currentImage.set("Image index", 0, 0, nbImage));
    pg->add(reset.set("Reset", false));
    pg->add(darkerInTime.set("Darker", 0, 0, 10));
    pg->add(opacityAtDraw.set("Opacity", 255, 100, 255));
    
    // FBO CLEAR
    fbo.allocate(w, h, GL_RGBA32F_ARB);
    fbo.begin();
    ofClear(0,0,0, 0);
    fbo.end();
    
}

//--------------------------------------------------------------
void ImageBuffer::update(ofFbo* input){

    
    
    ofEnableAlphaBlending();
    fbo.begin();
    
    ofFill();
    ofSetColor(0, 0, 0, darkerInTime);
    ofDrawRectangle(0,0,w,h);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(opacityAtDraw,opacityAtDraw,opacityAtDraw);
    
    input->draw(0, 0);
    fbo.end();
    
    
}

//--------------------------------------------------------------
void ImageBuffer::draw(int x,int y,int width, int height){
    
    fbo.draw(x, y, width, height);
}

//--------------------------------------------------------------
void ImageBuffer::draw(ofRectangle rect){
    
    fbo.draw(rect);
}

//--------------------------------------------------------------
void ImageBuffer::resetBuffer(bool &isReset){
    
    if(isReset){
    
        fbo.begin();
        ofClear(0,0,0, 255);
        fbo.end();
        
    }
    
}

