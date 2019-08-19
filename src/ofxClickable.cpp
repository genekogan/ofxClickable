#include "ofxClickable.h"


//--------------------------------------------------------------
ofxClickable::ofxClickable() {
    rect = ofRectangle(0, 0, 1, 1);
    margin = 3;
    bGradientAmt = 0;
    roundCorners = 0;
    isEnabled = true;
    isHover = false;
    isPressed = false;
    isActive = false;
    font = NULL;
    name = "";
    cHover = ofColor::orange;
    cPressed = ofColor::red;
    cActive = ofColor::lightGreen;
    cString = ofColor::black;
    cBackground = ofColor::white;
    cActiveBackground = ofColor(220, 245, 220);
    fboMask.allocate(rect.getWidth(), rect.getHeight());
    autoMouse = false;
    autoDraw = false;
}

//--------------------------------------------------------------
void ofxClickable::setup(string name, float x, float y, float w, float h) {
    setName(name);
    setPosition(x, y);
    resize(w, h);
    isEnabled = true;
}

//--------------------------------------------------------------
void ofxClickable::setName(string name) {
    this->name = name;
}

//--------------------------------------------------------------
void ofxClickable::enable() {
    isEnabled = true;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::disable() {
    isEnabled = false;
    isHover = false;
    isActive = false;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setAutoMouse(bool autoMouse) {
    this->autoMouse = autoMouse;
    if (autoMouse) {
        ofAddListener(ofEvents().mouseMoved, this, &ofxClickable::mouseMoved);
        ofAddListener(ofEvents().mousePressed, this, &ofxClickable::mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &ofxClickable::mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &ofxClickable::mouseReleased);
    }
    else {
        ofRemoveListener(ofEvents().mouseMoved, this, &ofxClickable::mouseMoved);
        ofRemoveListener(ofEvents().mousePressed, this, &ofxClickable::mousePressed);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofxClickable::mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxClickable::mouseReleased);
    }
}

//--------------------------------------------------------------
void ofxClickable::setAutoDraw(bool autoDraw) {
    this->autoDraw = autoDraw;
    if (autoDraw) {
        ofAddListener(ofEvents().draw, this, &ofxClickable::draw);
    }
    else {
        ofRemoveListener(ofEvents().draw, this, &ofxClickable::draw);
    }
}

//--------------------------------------------------------------
void ofxClickable::setEnabled(bool toEnable) {
    if (toEnable) {
        enable();
    } else {
        disable();
    }
}

//--------------------------------------------------------------
void ofxClickable::setActive(bool active) {
    isActive = active;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::loadIcon(string path) {
    this->iconPath = path;
    icon.load(iconPath);
    if (icon.isAllocated()) {
        int iw = icon.getWidth();
        int ih = icon.getHeight();
        float aspect = float(iw) / ih;
        if (aspect > rect.getWidth() / rect.getHeight()) {
            icon.resize(rect.getWidth(), rect.getWidth()/aspect);
        } else {
            icon.resize(aspect * rect.getHeight(), rect.getHeight());
        }
    }
    updateFbo();
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
        loadIcon(iconPath);
    }
    fboMask.allocate(rect.getWidth(), rect.getHeight());
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::updateFbo() {
    ofPushStyle();
    
    // draw the rounded mask
    fboMask.begin();
    ofClear(0, 0);
    ofSetColor(ofColor::white);
    ofDrawRectRounded(0, 0, rect.getWidth(), rect.getHeight(), roundCorners);
    fboMask.end();
    
    // draw the FBO
    fboBg.allocate(rect.getWidth(), rect.getHeight());
    fboBg.begin();
    ofClear(0, 0);

    // draw background or gradient
    if (bGradientAmt > 0) {
        ofColor color = isActive ? cActiveBackground : cBackground;
        ofColor color2 = ofColor(ofClamp(color.r-bGradientAmt, 0, 255),
                                 ofClamp(color.g-bGradientAmt, 0, 255),
                                 ofClamp(color.b-bGradientAmt, 0, 255));
        ofBackgroundGradient(color, color2, OF_GRADIENT_LINEAR);
    }
    else {
        ofColor color = isActive ? cActiveBackground : cBackground;
        ofBackground(color);
    }

    // draw the icon
    if (icon.isAllocated()) {
        ofSetColor(ofColor::white);
        float x = 0.5 * (rect.getWidth() - icon.getWidth());
        float y = 0.5 * (rect.getHeight() - icon.getHeight());
        icon.draw(x, y);
    }

    if (!isEnabled) {
        ofSetColor(ofColor::white, 200);
        ofDrawRectRounded(0, 0, rect.getWidth(), rect.getHeight(), roundCorners);
    }

    fboBg.end();
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxClickable::crop(int x, int y, int w, int h) {
    rect.setWidth(w);
    rect.setHeight(h);
    if (icon.isAllocated()) {
        icon.crop(x, y, w, h);
    }
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setFromTexture(ofTexture * texture) {
    texture->readToPixels(icon);
    icon.update();
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setFromPixels(ofPixels * pixels) {
    icon.setFromPixels(*pixels);
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::draw() {
    ofPushStyle();

    // draw outer rectangle
    ofFill();
    if (isActive) {
        ofSetColor(cActive);
        if (roundCorners > 0) {
            ofDrawRectRounded(rect.getX()-margin, rect.getY()-margin, rect.getWidth()+2*margin, rect.getHeight()+2*margin, roundCorners);
        } else {
            ofDrawRectangle(rect.getX()-margin, rect.getY()-margin, rect.getWidth()+2*margin, rect.getHeight()+2*margin);
        }
    }
    if (isHover) {
        ofSetColor(cHover);
        if (roundCorners > 0) {
            ofDrawRectRounded(rect.getX()-margin, rect.getY()-margin, rect.getWidth()+2*margin, rect.getHeight()+2*margin, roundCorners);
        } else {
            ofDrawRectangle(rect.getX()-margin, rect.getY()-margin, rect.getWidth()+2*margin, rect.getHeight()+2*margin);
        }
    }
    if (isPressed) {
        ofSetColor(cPressed);
        if (roundCorners > 0) {
            ofDrawRectRounded(rect.getX()-margin, rect.getY()-margin, rect.getWidth()+2*margin, rect.getHeight()+2*margin, roundCorners);
        } else {
            ofDrawRectangle(rect.getX()-margin, rect.getY()-margin, rect.getWidth()+2*margin, rect.getHeight()+2*margin);
        }
    }
    
    // background gradient
    ofSetColor(ofColor::white);
    fboBg.getTexture().setAlphaMask(fboMask.getTexture());
    fboBg.draw(rect.getX(), rect.getY());
    
    // draw string on top of the icon
    if (name != "" && font != NULL && !icon.isAllocated()) {
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
void ofxClickable::draw(ofEventArgs& e) {
    draw();
}

//--------------------------------------------------------------
void ofxClickable::buttonClicked() {
    if (!isEnabled) return;
    ofNotifyEvent(clickEvent, this);
}

//--------------------------------------------------------------
void ofxClickable::setPosition(int x, int y) {
    rect.setX(x);
    rect.setY(y);
}

//--------------------------------------------------------------
void ofxClickable::setBackgroundGradient(int bGradientAmt) {
    this->bGradientAmt = bGradientAmt;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setCornerRounded(int roundCorners) {
    this->roundCorners = roundCorners;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setActiveColor(ofColor active) {
    cActive=active;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setHoverColor(ofColor hover) {
    cHover = hover;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setPressedColor(ofColor pressed) {
    cPressed = pressed;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setBackgroundColor(ofColor cbg) {
    cBackground = cbg;
    updateFbo();
}
//--------------------------------------------------------------
void ofxClickable::setActiveBackgroundColor(ofColor cbg) {
    cActiveBackground = cbg;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setStringColor(ofColor cstr) {
    cString = cstr;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setMargin(int mgn) {
    margin = mgn;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::setFont(ofTrueTypeFont *font_) {
    this->font = font_;
    updateFbo();
}

//--------------------------------------------------------------
void ofxClickable::mouseMoved(int x, int y){
    if (!isEnabled) return;
    isHover = rect.inside(x, y);
}

//--------------------------------------------------------------
void ofxClickable::mouseDragged(int x, int y){
    if (!isEnabled) return;
}

//--------------------------------------------------------------
void ofxClickable::mousePressed(int x, int y){
    if (!isEnabled) return;
    if (isHover) {
        isPressed = true;
    }
}

//--------------------------------------------------------------
void ofxClickable::mouseReleased(int x, int y){
    if (!isEnabled) return;
    if (isPressed) {
        isPressed = false;
        buttonClicked();
    }
}

//--------------------------------------------------------------
void ofxClickable::mouseMoved(ofMouseEventArgs &e) {
    mouseMoved(e.x, e.y);
}

//--------------------------------------------------------------
void ofxClickable::mousePressed(ofMouseEventArgs &e) {
    mousePressed(e.x, e.y);
}

//--------------------------------------------------------------
void ofxClickable::mouseDragged(ofMouseEventArgs &e) {
    mouseDragged(e.x, e.y);
}

//--------------------------------------------------------------
void ofxClickable::mouseReleased(ofMouseEventArgs &e) {
    mouseReleased(e.x, e.y);
}

