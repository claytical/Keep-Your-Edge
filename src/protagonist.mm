//
//  protagonist.cpp
//  AvoidSquares
//
//  Created by Clay Ewing on 7/9/11.

#include "protagonist.h"

int Protagonist::collectEdge() {
    for (int i = 0; i < 4; i++) {
        if (lineAnimation[i]) {
            switch (i) {
                case 0:
                    ofLine(edges[0].x, animatedLine[0], edges[1].x, animatedLine[0]);
                    animatedLine[0]+= LINE_ANIMATION_SPEED;
                    if (animatedLine[0] >= edges[0].y) {
                        lineAnimation[0] = false;
                        edgesCollected++;
                        collectableSound.play();
                        return 1;
                    }
                    break;
                case 1:
                    ofLine(animatedLine[1], edges[1].y, animatedLine[1], edges[2].y);
                    animatedLine[1]-= LINE_ANIMATION_SPEED;
                    if (animatedLine[1] <= edges[1].x) {
                        lineAnimation[1] = false;
                        collectableSound.play();

                        edgesCollected++;
                        return 1;
                    }
                    break;
                case 2:
                    ofLine(edges[2].x, animatedLine[2], edges[3].x, animatedLine[2]);
                    animatedLine[2]-= LINE_ANIMATION_SPEED;
                    if (animatedLine[2] <= edges[2].y) {
                        lineAnimation[2] = false;
                        collectableSound.play();

                        edgesCollected++;
                        return 1;
                    }
                    break;
                case 3:
                    ofLine(animatedLine[3], edges[3].y, animatedLine[3], edges[0].y);
                    animatedLine[3]+= LINE_ANIMATION_SPEED;
                    if (animatedLine[3] >= edges[3].x) {
                        lineAnimation[3] = false;
                        collectableSound.play();

                        edgesCollected++;
                        return 1;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
    
}

void Protagonist::display() {
    if (edgesCollected == 4) {
        collected++;
        width+=1;
        height+=1;
        edgesCollected = 0;
    }
    ofSetColor(r, g, b);
    ofNoFill();
    ofRectRounded(x, y, width, height, sides);
    ofSetRectMode(OF_RECTMODE_CENTER);
    for (int i = 0; i <= collected; i++) {

        float newSize = ofMap(i, 0, collected, 0, width);
        ofRectRounded(x + width/2, y + height/2, newSize, newSize, sides);
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofFill();
    ofSetColor(127);
    //collectEdge();

}

void Protagonist::moveTo(int xPos, int yPos) {
//creep up on the spot
    x += (xPos - x) * .2;
    y += (yPos - y) * .2;

    edges[0].set(x, y);
    edges[1].set(x+width, y);
    edges[2].set(x+width, y+height);
    edges[3].set(x, y+height);
    
}


void Protagonist::create(int _x, int _y, int _size) {
    r = 255;
    g = 255;
    b = 255;
    collectableSound.loadSound("edge.wav");
    
    collectableSound.setVolume(.2);

    x = _x;
    y = _y;
    collected = 0;
    edgesCollected = 0;
    for (int i = 0; i < 4; i++) {
        lineAnimation[i] = false;
    }
    width = _size;
    height = _size;
    sides = HEALTHY;

}


bool Protagonist::collide(Collectable c) {
    c.distanceToProtagonist = ofDist(c.x, c.y, x + width/2, y + height/2);
    if (x+width < c.x) { return false; }
    if (x > c.x+c.width) { return false; }
    if (y+height < c.y) { return false; }
    if (y > c.y+c.height) { return false; }
    animatedLine[0] = 0;
    animatedLine[1] = ofGetWidth();
    animatedLine[2] = ofGetHeight();
    animatedLine[3] = 0;
    for (int i = 0; i < 4; i++) {
        lineAnimation[i] = true;
    }
    
    
    return true;

 }

bool Protagonist::collide(Enemy e) {

    if (e.hit) {
        cout << "already hit enemy" << endl;
        return false;
    }
    //enemy is circle
    //protagonist is square

    if (ofDist(e.x, e.y, x, y) <= e.radius || ofDist(e.x, e.y, x + width, y + height) <= e.radius) {
        return true;
    }
    else {
        return false;
    }
 }

void Protagonist::change(int amount) {
    sides = sides + amount%20;
    if (sides < HEALTHY) {
        sides = HEALTHY;
    }
    if (sides > DEAD) {
        sides = DEAD;
    }
}

