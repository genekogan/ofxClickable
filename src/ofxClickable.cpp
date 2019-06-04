#include "ofxClickable.h"


//--------------------------------------------------------------
ofxClickable::ofxClickable() {
    rect = ofRectangle(0, 0, 0, 0);
    isHover = false;
    isPressed = false;
    isActive = false;
    font = NULL;
    name = "";
    cHover = ofColor::orange;
    cPressed = ofColor::red;
    cActive = ofColor::green;
    cString = ofColor::black;
    cBackground = ofColor::white;
}

//--------------------------------------------------------------
void ofxClickable::setup(string name, float x, float y, float w, float h) {
    setName(name);
    setPosition(x, y);
    resize(w, h);
}

//--------------------------------------------------------------
void ofxClickable::setName(string name) {
    this->name = name;
}

//--------------------------------------------------------------
void ofxClickable::loadIcon(string path) {
    this->iconPath = path;
    icon.load(iconPath);
    if (icon.isAllocated()) {
        icon.resize(rect.getWidth(), rect.getHeight());
    }
}

//--------------------------------------------------------------
void ofxClickable::saveIcon(string path) {
    this->iconPath = path;
    icon.save(iconPath);
}

//--------------------------------------------------------------
void ofxClickable::resize(int w, int h) {
    rect.setWidth(w);
    rect.setHeight(h);
    if (icon.isAllocated()) {
        icon.resize(rect.getWidth(), rect.getHeight());
    }
}

//--------------------------------------------------------------
void ofxClickable::setFromTexture(ofTexture * texture) {
    texture->readToPixels(icon);
}

//--------------------------------------------------------------
void ofxClickable::draw() {
    ofPushStyle();
    
    ofFill();
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
    ofDrawRectangle(rect);
    if (icon.isAllocated()) {
        ofSetColor(ofColor::white);
        icon.draw(rect.getX(), rect.getY());
    }
    if (name != "" && font != NULL) {
        ofSetColor(cString);
        int fw = font->getStringBoundingBox(name, 0, 0).getWidth();
        int fh = font->getStringBoundingBox(name, 0, 0).getHeight();
        int x = rect.getX() + 0.5 * (rect.getWidth() - fw);
        int y = rect.getY() + rect.getHeight() - 0.5 * (rect.getHeight() - fh);
        font->drawString(name, x, y);
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
    ofNotifyEvent(clickEvent, this);
}
