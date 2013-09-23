//
//  savior.h
//  AvoidSquares
//
//  Created by Clay Ewing on 7/9/11.
//

#pragma once
#include "ofMain.h"
#define SAVIOR_RADIUS   20

class Savior {
public:
	
	void display();
	void create(int x, int y);
	int x, y;
    int r,g,b;
	int width, height;
    int strength;
    bool consumed;
};
