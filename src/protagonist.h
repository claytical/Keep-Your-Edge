//
//  protagonist.h
//  AvoidSquares
//
//  Created by Clay Ewing on 7/9/11.

#pragma once
#include "ofMain.h"
//#include "ofxRetinaImage.h"
#include "collectable.h"
#include "enemy.h"

#define HEALTHY     0
#define DEAD        12
#define LINE_ANIMATION_SPEED 1.5

class Protagonist {
    
public:
	
	void display();
	void create(int x, int y, int radius);
    void change(int amount);
    void moveTo(int x, int y);
    bool collide(Collectable c);
    bool collide(Enemy e);
    int collectEdge();
    void loseEdge();
	float x, y;
    int r,g,b;
	int width, height;
    int spacer;
    int sides;
    int collected;
    int edgesCollected;
    float lineAnimationSpeed;
    bool lineAnimation[4];
    ofPoint edges[4];
    float animatedLine[4];
    float reverseAnimatedLine[4];
    ofSoundPlayer collectableSound;
};
