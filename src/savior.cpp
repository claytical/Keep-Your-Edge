//
//  savior.cpp
//  AvoidSquares
//
//  Created by Clay Ewing on 7/9/11.
//

#include "savior.h"

void Savior::display() {
    ofNoFill();
    ofSetColor(r, g, b, 200);
    ofRect(x + SAVIOR_RADIUS/2, y + SAVIOR_RADIUS/2, SAVIOR_RADIUS/4, SAVIOR_RADIUS/4);
}


void Savior::create(int _x, int _y) {
    r = 127;
    g = 127;
    b = 127;
    x = _x;
    y = _y;
    consumed = false;
}