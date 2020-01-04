#include "ofApp.h"

/*
 
 Global architecture
 
 
                 Input ( file or hdmi input )
                    |
                   / \
                  /   \
        videoBuffer     ImageBuffer
                  \   /
                   Mask
                    |
                 ouput_fx
                    |
                image_layer ( can be post of pre-fx )
                    |
                 output_final
 
 
 
 */





//--------------------------------------------------------------
void ofApp::setup(){

    input_w = 1280;
    input_h = 720;
    ofBackground(100);
    
    input = new Input(&pg_input, input_w, input_h);
    imageBuffer = new ImageBuffer(&pg_imageBuffer, input_w, input_h, 5);
    pg.setName("main");
    pg.add(bg_color.set("BackGround", 35, 0, 255));
    gui.setup(pg);
    gui.add(pg_input);
    gui.add(pg_imageBuffer);
    
    
    //Vignette setup
    vignetteInput = ofRectangle(240, 40, 426, 240);
    vignetteBuffer = ofRectangle(240, 320, 426, 240);
    vignetteZoom = ofRectangle(690, 100, 355, 200);
    zoomImage.allocate(vignetteZoom.width/2, vignetteZoom.height/2, OF_IMAGE_COLOR_ALPHA);
    zoomPixels.allocate(1920,1080, OF_IMAGE_COLOR_ALPHA );
    zoomPixels.setColor(ofColor::goldenRod);
    zoomRectangle = ofRectangle();
    
    bool isZoomAllocated = zoomPixels.isAllocated();
    
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    input->update();
    imageBuffer->update(&(input->fbo));
    
    //Zoom updating
    float zoomRatioX = 0;
    float zoomRatioY = 0;
    
    //Set Manually zoom when mouse pressed
    if(ofGetMousePressed()){
    
        if(vignetteInput.inside(ofGetMouseX(), ofGetMouseY())){
            float relativePosX = ( ofGetMouseX() - vignetteInput.x );
            float relativePosY = ( ofGetMouseY() - vignetteInput.y );
            float zoomRatioW = (vignetteInput.width / input->w )*vignetteZoom.width/2;
            float zoomRatioH = (vignetteInput.height / input->h )*vignetteZoom.height/2;
            zoomRectangle = ofRectangle(relativePosX + vignetteInput.x, relativePosY+vignetteInput.y , zoomRatioW, zoomRatioH);
            zoomLevelEntry = 1;
            
        }
        
        else if(vignetteBuffer.inside(ofGetMouseX(), ofGetMouseY()) ){
            float relativePosX = ( ofGetMouseX() - vignetteBuffer.x );
            float relativePosY = ( ofGetMouseY() - vignetteBuffer.y );
            float zoomRatioW = (vignetteBuffer.width / input->w )*vignetteZoom.width/2;
            float zoomRatioH = (vignetteBuffer.height / input->h )*vignetteZoom.height/2;
            zoomRectangle = ofRectangle(relativePosX + vignetteBuffer.x, relativePosY +vignetteBuffer.y, zoomRatioW, zoomRatioH);
            zoomLevelEntry = 2;
        }
        
        else {
            
            //zoomLevelEntry = 0;
        
        }
        
    }
    
    updateZoom();
 
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(bg_color);
    
    ofSetColor(255,255,255);
    gui.draw();
    
    ofSetColor(0, 0, 255);
    ofNoFill();
    ofDrawRectangle(vignetteInput);
    ofSetColor(255,255,255);
    input->fbo.draw(vignetteInput);
    
    
    ofSetColor(0, 0, 255);
    ofNoFill();
    ofDrawRectangle(vignetteBuffer);
    ofSetColor(255,255,255);
    imageBuffer->draw(vignetteBuffer);
    
    ofSetColor(0, 0, 255);
    ofNoFill();
    ofDrawRectangle(vignetteZoom);
    ofSetColor(255,255,255);
    zoomImage.draw(vignetteZoom);
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofDrawRectangle(zoomRectangle);
    

}

//--------------------------------------------------------------
void ofApp::updateZoom(){
    
    // ZOOM is set from INPUT
    if(zoomLevelEntry == 1){
        
        input->fbo.readToPixels(zoomPixels);
        float posX = zoomRectangle.x - vignetteInput.x;
        float posY = zoomRectangle.y - vignetteInput.y;
        float ratioX = vignetteInput.width / input_w;
        float ratioY = vignetteInput.height / input_h;
        int cropX = posX / ratioX;
        int cropY = posY / ratioY;
        int cropW = vignetteZoom.width/2;
        int cropH = vignetteZoom.height/2;
        zoomPixels.crop(cropX, cropY, cropW, cropH);
        
        
    }
    
    // ZOOM is set from BUFFER_IMAGE
    if(zoomLevelEntry == 2){
        
        imageBuffer->fbo.readToPixels(zoomPixels);
        float posX = zoomRectangle.x - vignetteBuffer.x;
        float posY = zoomRectangle.y - vignetteBuffer.y;
        float ratioX = vignetteBuffer.width / input_w;
        float ratioY = vignetteBuffer.height / input_h;
        int cropX = posX / ratioX;
        int cropY = posY / ratioY;
        int cropW = vignetteZoom.width/2;
        int cropH = vignetteZoom.height/2;
        zoomPixels.crop(cropX, cropY, cropW, cropH);
    
    }
    
    // ZOOM is set to NOTHING
    if(zoomLevelEntry == 0){
        zoomPixels.setColor(ofColor::black);
        zoomPixels.crop(0,0, vignetteZoom.width, vignetteZoom.height);
    }
    
    zoomImage.setFromPixels(zoomPixels);
    

     

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
