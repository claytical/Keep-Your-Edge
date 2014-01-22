//
//  enemy.h
//  AvoidSquares
//
//  Created by Clay Ewing on 7/9/11.

#pragma once
#include "ofMain.h"
//#include "ofxRetinaImage.h"

class Enemy {
public:
	
	void display();
	void create(float x, float y, float speed, int radius);
	float x, y;
    ofPoint seek;
    int r,g,b;
	int radius;
    float distanceToProtagonist;
    bool hit;
//    ofxRetinaImage *image;

    int speed;
};
