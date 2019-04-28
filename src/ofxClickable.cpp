#include "ofxClickable.h"


//--------------------------------------------------------------
ofxClickable::ofxClickable() {
    rect = ofRectangle(0, 0, 0, 0);
    isHover = false;
    isPressed = false;
    isActive = false;
    font = NULL;
    drawStr = "";
    cHover = ofColor::orange;
    cPressed = ofColor::red;
    cActive = ofColor::green;
    cString = ofColor::black;
    cBackground = ofColor::white;
}

//--------------------------------------------------------------
void ofxClickable::setup(string msg, float x, float y, float w, float h) {
    setString(msg);
    setPosition(x, y);
    resize(w, h);
}

//--------------------------------------------------------------
void ofxClickable::setString(string msg) {
    drawStr = msg;
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
    ofPushStyle();
    
    if (isActive) {
        ofSetColor(cActive);
        ofDrawRectangle(rect.getX()-4, rect.getY()-4, rect.getWidth()+8, rect.getHeight()+8);
    }
    if (isHover) {
        ofSetColor(cHover);
        ofDrawRectangle(rect.getX()-4, rect.getY()-4, rect.getWidth()+8, rect.getHeight()+8);
    }
    if (isPressed) {
        ofSetColor(cPressed);
        ofDrawRectangle(rect.getX()-4, rect.getY()-4, rect.getWidth()+8, rect.getHeight()+8);
    }
    
    ofSetColor(cBackground);
    ofDrawRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
    if (thumb.isAllocated()) {
        ofSetColor(ofColor::white);
        thumb.draw(rect.getX(), rect.getY());
    }
    if (drawStr != "" && font != NULL) {
        ofSetColor(cString);
        int fw = font->getStringBoundingBox(drawStr, 0, 0).getWidth();
        int fh = font->getStringBoundingBox(drawStr, 0, 0).getHeight();
        int x = rect.getX() + 0.5 * (rect.getWidth() - fw);
        int y = rect.getY() + rect.getHeight() - 0.5 * (rect.getHeight() - fh);
        font->drawString(drawStr, x, y);
    }
    
    ofPopStyle();
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
