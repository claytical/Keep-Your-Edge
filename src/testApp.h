#pragma once

#include "ofMain.h"
#include "enemy.h"
#include "protagonist.h"
#include "savior.h"
#include "collectable.h"
#include "ofxXmlSettings.h"
#include "ofxCenteredTrueTypeFont.h"
#include "ofxUI.h"

//#include "Flurry.h"
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadLevel(string levelName);
//        NSString * getLevelName(NSString *levelFile);
        vector<string>patterns;
        
        static bool consumed(Savior &savior);
        static bool collected(Collectable &collectable);
        static bool passedGateway(Enemy &enemy);
        
        
        void loadPattern(int pattern);
        ofxUICanvas *gui;
        ofxUICanvas *gameOverGui;
        ofxUIDropDownList *ddl;
        ofxUILabel *titleLabel;
        ofxUILabelButton *playButton;
        ofxUILabelButton *mainMenuButton;
        void exit();
        void guiEvent(ofxUIEventArgs &e);

    
        ofxXmlSettings XML;
        ofxXmlSettings XMLLevel;
        Protagonist protagonist;
        vector<Savior> saviors;
    
        ofSoundPlayer movementSound;
        ofSoundPlayer movingSound;
        
        vector<Enemy> enemies;
        ofSoundPlayer enemySound;
        
        vector<Collectable> collectables;
        ofSoundPlayer collectableSound;
        ofSoundPlayer backgroundMusic;
        
        int progressMarker, completionAmount;
        float speed, multiplier;
        int healCounter;
        ofxCenteredTrueTypeFont textBig;
        ofxCenteredTrueTypeFont textSmall;
        bool won;
        int gameState;
        string selectedTrack;
        int currentPattern;
        bool achievedHighScore;
        ofDirectory dir;

};
