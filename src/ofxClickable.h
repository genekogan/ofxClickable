#pragma once

#include "ofMain.h"


class ofxClickable {
public:
    ofxClickable();
    
    virtual void load(string path);
    virtual void save(string path);
    
    virtual void resize(int w, int h);
    virtual void setFromTexture(ofTexture * texture);
    
    virtual void setActive(bool active) {isActive=active;}
    virtual void setActiveColor(ofColor active) {cActive=active;}
    virtual void setHoverColor(ofColor hover) {cHover=hover;}
    virtual void setPressedColor(ofColor pressed) {cPressed=pressed;}

    ofColor getActiveColor() {return cActive;}
    ofColor getHoverColor() {return cHover;}
    ofColor getPressedColor() {return cPressed;}
    ofRectangle getRectangle() {return rect;}
    
    virtual void setPosition(int x, int y);
    virtual void draw();
    
    virtual void buttonClicked();

    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void mousePressed(int x, int y);
    virtual void mouseReleased(int x, int y);
    
protected:
    
    bool isHover, isPressed, isActive;
    ofColor cHover, cPressed, cActive;
    ofImage thumb;
    ofRectangle rect;
};


