#pragma once

#include "ofMain.h"


class ofxClickable {
public:
    ofxClickable();
    
    virtual void setup(string msg, float x, float y, float w, float h);
    virtual void setName(string name);
    virtual void setFont(ofTrueTypeFont *font_) {this->font = font_;}
    virtual void loadIcon(string path);
    virtual void saveIcon(string path);
    virtual void resize(int w, int h);
    virtual void setFromTexture(ofTexture * texture);
    
    virtual void setActive(bool active) {isActive=active;}
    virtual void setActiveColor(ofColor active) {cActive=active;}
    virtual void setHoverColor(ofColor hover) {cHover=hover;}
    virtual void setPressedColor(ofColor pressed) {cPressed=pressed;}
    virtual void setBackgroundColor(ofColor cbg) {cBackground=cbg;}
    virtual void setStringColor(ofColor cstr) {cString=cstr;}
    
    string getName() {return name;}
    bool getActive() {return isActive;}
    ofColor getActiveColor() {return cActive;}
    ofColor getHoverColor() {return cHover;}
    ofColor getPressedColor() {return cPressed;}
    ofColor getBackgroundColor() {return cBackground;}
    ofColor getStringColor() {return cString;}
    ofRectangle getRectangle() {return rect;}
    
    virtual void setPosition(int x, int y);
    virtual void draw();
    
    virtual void buttonClicked();

    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void mousePressed(int x, int y);
    virtual void mouseReleased(int x, int y);
    
    ofEvent<void> clickEvent;
    
protected:
    
    bool isHover, isPressed, isActive;
    ofColor cHover, cPressed, cActive, cString, cBackground;
    ofImage icon;
    ofRectangle rect;
    string name;
    string iconPath;
    ofTrueTypeFont *font;
};


