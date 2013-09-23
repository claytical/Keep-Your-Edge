//
//  collectable.h
//  WellRounded
//
//  Created by Clay Ewing on 5/3/13.
//
//

#pragma once
#include "ofMain.h"

class Collectable {
public:
	
	void display();
	void create(int x, int y, int speed, float _size);
	int x, y;
    int r,g,b;
	float width, height;
    float distanceToProtagonist;
    int speed;
    bool collected;
};
