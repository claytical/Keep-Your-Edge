//
//  collectable.cpp
//  WellRounded
//
//  Created by Clay Ewing on 5/3/13.
//
//

#include "collectable.h"

void Collectable::create(int _x, int _y, int _speed, float _size) {
    x = _x;
    y = _y;
    width = _size;
    height = _size;
    speed = _speed;
    r = 0;
    g = ofRandom(255);
    b = ofRandom(255);
    collected = false;
    
}

void Collectable::display() {
    ofFill();
    if (distanceToProtagonist < width*2) {
        ofSetColor(r, g, b, ofMap(distanceToProtagonist, 0, width*2, 255, 175));
    }
    else {
        ofSetColor(r, g, b, 150);
    }
    if (collected) {
    }
    else {
        ofRect(x, y, width, height);

    }

    y = y - speed;

    
}