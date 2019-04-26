#include "ofxClickable.h"


//--------------------------------------------------------------
ofxClickable::ofxClickable() {
    rect = ofRectangle(0, 0, 0, 0);
    isHover = false;
    isPressed = false;
    cHover = ofColor::orange;
    cPressed = ofColor::red;
    cActive = ofColor::green;
}

//--------------------------------------------------------------
void ofxClickable::load(string path) {
    thumb.load(path);
}

//--------------------------------------------------------------
void ofxClickable::save(string path) {
    thumb.save(path);
}

//--------------------------------------------------------------
void ofxClickable::resize(int w, int h) {
    rect.setWidth(w);
    rect.setHeight(h);
    thumb.resize(rect.getWidth(), rect.getHeight());
}

//--------------------------------------------------------------
void ofxClickable::setFromTexture(ofTexture * texture) {
    texture->readToPixels(thumb);
}

//--------------------------------------------------------------
void ofxClickable::draw() {
    if (isActive) {
        ofPushStyle();
        ofSetColor(ofColor::orange);
        ofDrawRectangle(rect.getX()-4, rect.getY()-4, rect.getWidth()+8, rect.getHeight()+8);
        ofPopStyle();
    }
    if (isHover) {
        ofPushStyle();
        ofSetColor(ofColor::green);
        ofDrawRectangle(rect.getX()-4, rect.getY()-4, rect.getWidth()+8, rect.getHeight()+8);
        ofPopStyle();
    }
    if (isPressed) {
        ofPushStyle();
        ofSetColor(ofColor::orange);
        ofDrawRectangle(rect.getX()-4, rect.getY()-4, rect.getWidth()+8, rect.getHeight()+8);
        ofPopStyle();
    }

    thumb.draw(rect.getX(), rect.getY());
}

//--------------------------------------------------------------
void ofxClickable::setPosition(int x, int y) {
    rect.setX(x);
    rect.setY(y);
}

//--------------------------------------------------------------
void ofxClickable::mouseMoved(int x, int y){
    isHover = rect.inside(x, y);
}

//--------------------------------------------------------------
void ofxClickable::mouseDragged(int x, int y){
    
}

//--------------------------------------------------------------
void ofxClickable::mousePressed(int x, int y){
    if (isHover) {
        isPressed = true;
    }
}

//--------------------------------------------------------------
void ofxClickable::mouseReleased(int x, int y){
    if (isPressed) {
        isPressed = false;
        buttonClicked();
    }
}

//--------------------------------------------------------------
void ofxClickable::buttonClicked() {
    ofLog() << "Click!";
}
