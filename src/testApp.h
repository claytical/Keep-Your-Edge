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
        void loadPattern(int pattern);
        void exit();
        void guiEvent(ofxUIEventArgs &e);

        static bool consumed(Savior &savior);
        static bool collected(Collectable &collectable);
        static bool passedGateway(Enemy &enemy);
        
        
    
        vector<string>patterns;
        ofxUICanvas *gui;
        ofxUICanvas *gameOverGui;
        ofxUIDropDownList *ddl;
        ofxUILabel *titleLabel;
        ofxUILabelButton *playButton;
        ofxUILabelButton *mainMenuButton;
        ofxXmlSettings XML;
        ofxXmlSettings XMLLevel;
        ofDirectory dir;
    
        ofSoundPlayer movementSound;
        ofSoundPlayer movingSound;
        ofSoundPlayer enemySound;
        ofSoundPlayer collectableSound;
        ofSoundPlayer backgroundMusic;
    
        ofxCenteredTrueTypeFont textBig;
        ofxCenteredTrueTypeFont textSmall;
    
        Protagonist protagonist;
        vector<Enemy> enemies;
        vector<Collectable> collectables;
        vector<Savior> saviors;

    
        string selectedTrack;
    
        int progressMarker, completionAmount;
        int healCounter;
        int gameState;
        int currentPattern;

        float speed, multiplier;
        float score;
    
        bool won;
        bool achievedHighScore;


};
