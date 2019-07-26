#pragma once

#include "ofMain.h"


class ofxClickable {
public:
    ofxClickable();
    
    virtual void setup(string msg, float x, float y, float w, float h);
    virtual void setName(string name);

    virtual void setFont(ofTrueTypeFont *font_);
    virtual void loadIcon(string path);
    virtual void saveIcon(string path);
    virtual void crop(int x, int y, int w, int h);
    virtual void resize(int w, int h);
    virtual void setFromTexture(ofTexture * texture);
    virtual void setFromPixels(ofPixels * pixels);
    
    virtual void enable();
    virtual void disable();
    virtual void setEnabled(bool toEnable);
    virtual void setActive(bool active);

    virtual void setActiveColor(ofColor active);
    virtual void setHoverColor(ofColor hover);
    virtual void setPressedColor(ofColor pressed);
    virtual void setBackgroundColor(ofColor cbg);
    virtual void setActiveBackgroundColor(ofColor cbg);
    virtual void setStringColor(ofColor cstr);
    virtual void setMargin(int mgn);
    virtual void setBackgroundGradient(int bGradientAmt);
    virtual void setCornerRounded(int roundCorners);

    virtual bool getActive() {return isActive;}
    virtual bool getEnabled() {return isEnabled;}
    virtual string getName() {return name;}
    virtual ofColor getActiveColor() {return cActive;}
    virtual ofColor getHoverColor() {return cHover;}
    virtual ofColor getPressedColor() {return cPressed;}
    virtual ofColor getBackgroundColor() {return cBackground;}
    virtual ofColor getActiveBackgroundColor() {return cActiveBackground;}
    virtual ofColor getStringColor() {return cString;}
    virtual ofRectangle getRectangle() {return rect;}
    virtual ofImage & getIcon() {return icon;}
    virtual string & getIconPath() {return iconPath;}
    virtual int getMargin() {return margin;}
    virtual int getBackgroundGradient() {return bGradientAmt;}
    virtual int getCornerRounded() {return roundCorners;}

    virtual void setPosition(int x, int y);
    virtual void draw();
    
    virtual void buttonClicked();

    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void mousePressed(int x, int y);
    virtual void mouseReleased(int x, int y);
    
    ofEvent<void> clickEvent;

protected:
    
    virtual void updateFbo();
    
    bool isHover;
    bool isPressed;
    bool isActive;
    bool isEnabled;

    ofColor cHover;
    ofColor cPressed;
    ofColor cActive;
    ofColor cString;
    ofColor cBackground;
    ofColor cActiveBackground;
    
    ofImage icon;
    ofRectangle rect;
    ofFbo fboBg;
    ofFbo fboMask;
    ofTrueTypeFont *font;

    string name;
    string iconPath;
    int margin;
    int roundCorners;
    int bGradientAmt;
};


