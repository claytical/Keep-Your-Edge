//
//  enemy.cpp
//  AvoidSquares
//
//  Created by Clay Ewing on 7/9/11.

#include "enemy.h"

void Enemy::create(float _x, float _y, float _speed, int _radius) {
    x = _x;
    y = _y;
    hit = false;
    radius = _radius;
    speed = _speed;
    r = ofRandom(127,255);
    g = 0;
    b = ofRandom(0,127);
    distanceToProtagonist = 999999;
}

void Enemy::display() {
    if (hit) {
        radius--;
        if (radius <= 1) {
            radius = 1;
        }
    }
    if (distanceToProtagonist < radius*2) {
        ofSetColor(r, g, b, ofMap(distanceToProtagonist, 0, radius*2, 255, 175));
    }
    else {
        ofSetColor(r, g, b, 150);
    }
    ofFill();
    ofCircle(x, y, radius);
    y = y - speed;
    
}

