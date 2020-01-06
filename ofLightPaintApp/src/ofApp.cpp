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

/*
 ========================================
 HSV seems to be better than hsl
 because pure blue and pure white are at the same level of value.
 When using the threshold, we don"t want to discriminate any pure color compare to white
 
 
 
 
 //HSV (hue, saturation, value) to RGB.
 //Sources: https://gist.github.com/yiwenl/745bfea7f04c456e0101, https://gist.github.com/sugi-cho/6a01cae436acddd72bdf
 vec3 hsv2rgb(vec3 c){
 vec4 K=vec4(1.,2./3.,1./3.,3.);
 return c.z*mix(K.xxx,saturate(abs(fract(c.x+K.xyz)*6.-K.w)-K.x),c.y);
 }
 
 //RGB to HSV.
 //Source: https://gist.github.com/yiwenl/745bfea7f04c456e0101
 vec3 rgb2hsv(vec3 c) {
 float cMax=max(max(c.r,c.g),c.b),
 cMin=min(min(c.r,c.g),c.b),
 delta=cMax-cMin;
 vec3 hsv=vec3(0.,0.,cMax);
 if(cMax>cMin){
 hsv.y=delta/cMax;
 if(c.r==cMax){
 hsv.x=(c.g-c.b)/delta;
 }else if(c.g==cMax){
 hsv.x=2.+(c.b-c.r)/delta;
 }else{
 hsv.x=4.+(c.r-c.g)/delta;
 }
 hsv.x=fract(hsv.x/6.);
 }
 return hsv;
 }
 //Source: https://gist.github.com/sugi-cho/6a01cae436acddd72bdf
 vec3 rgb2hsv_2(vec3 c){
 vec4 K=vec4(0.,-1./3.,2./3.,-1.),
 p=mix(vec4(c.bg ,K.wz),vec4(c.gb,K.xy ),step(c.b,c.g)),
 q=mix(vec4(p.xyw,c.r ),vec4(c.r ,p.yzx),step(p.x,c.r));
 float d=q.x-min(q.w,q.y),
 e=1e-10;
 return vec3(abs(q.z+(q.w-q.y)/(6.*d+e)),d/(q.x+e),q.x);
 }
 
 
 
 
 
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
    pg.add(zoom_level.set("Zoom", 2, 1, 10));
    gui.setup(pg);
    gui.add(pg_input);
    gui.add(pg_imageBuffer);
    
    
    //Vignette setup
    vignetteInput = ofRectangle(240, 40, 355, 200);
    vignetteBuffer = ofRectangle(240, 320, 355, 200);
    vignetteFx = ofRectangle(240, 560, 355, 200);
    vignetteZoom = ofRectangle(690, 100, 355, 200);
    zoomImage.allocate(vignetteZoom.width/2, vignetteZoom.height/2, OF_IMAGE_COLOR_ALPHA);
    zoomPixels.allocate(1920,1080, OF_IMAGE_COLOR_ALPHA );
    zoomPixels.setColor(ofColor::goldenRod);
    zoomRectangle = ofRectangle();
    transparentBg.load("transparent.png");
    
    bool isZoomAllocated = zoomPixels.isAllocated();
    

    
    
    //SYPHON SETTINGS
    syphonOut.setName("palme");
    imgTest.load("tof.jpg");
    
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    ofEnableAlphaBlending();
    

    
    //update module one by one
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
            float zoomRatioW = (vignetteInput.width / input->w )*vignetteZoom.width/zoom_level;
            float zoomRatioH = (vignetteInput.height / input->h )*vignetteZoom.height/zoom_level;
            zoomRectangle = ofRectangle(relativePosX + vignetteInput.x, relativePosY+vignetteInput.y , zoomRatioW, zoomRatioH);
            zoomLevelEntry = 1;
            
        }
        
        else if(vignetteBuffer.inside(ofGetMouseX(), ofGetMouseY()) ){
            float relativePosX = ( ofGetMouseX() - vignetteBuffer.x );
            float relativePosY = ( ofGetMouseY() - vignetteBuffer.y );
            float zoomRatioW = (vignetteBuffer.width / input->w )*vignetteZoom.width/zoom_level;
            float zoomRatioH = (vignetteBuffer.height / input->h )*vignetteZoom.height/zoom_level;
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
    
   
    ofSetColor(255, 255, 255);
    ofFill();
    syphonOut.publishTexture(&(imageBuffer->fbo.getTexture()));

    
    
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
    transparentBg.draw(vignetteZoom);
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
        int cropW = vignetteZoom.width/zoom_level;
        int cropH = vignetteZoom.height/zoom_level;
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
        int cropW = vignetteZoom.width/zoom_level;
        int cropH = vignetteZoom.height/zoom_level;
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
