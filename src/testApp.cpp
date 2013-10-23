#include "testApp.h"
#define WAITING_TO_PLAY 0
#define TUTORIAL        1
#define PLAYING         2
#define GAME_OVER       3
#define NEW_GAME        4
#define CREDITS         5
#define GAME_CENTER     6
#define WON_TRACK       7
#define SPACE_BETWEEN_PATTERNS  -300

//--------------------------------------------------------------
void testApp::setup(){
    
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320;
    gui = new ofxUICanvas();
    gui->setFont("cdb.ttf");
    dir.allowExt("level"); //only allow .level files
    dir.listDir("levels/");
	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    vector<string> levels;
    
	// run through each level file and add it to the levels vector
	for(int i = 0; i < (int)dir.size(); i++){
        levels.push_back(dir.getFile(i).getBaseName());
	}

    gui->autoSizeToFitWidgets();
    gui->setPosition(0, ofGetHeight()/2);
    gui->setWidth(ofGetWidth());
    gameOverGui = new ofxUICanvas();
    gameOverGui->setPosition(0, ofGetHeight()/2 + 60);
    gameOverGui->setWidth(ofGetWidth());
    mainMenuButton = gameOverGui->addLabelButton("main menu", false);
    gameOverGui->setTheme(OFX_UI_THEME_BERLIN);
    gameOverGui->autoSizeToFitWidgets();
    gameOverGui->setVisible(false);

    playButton = gui->addLabelButton("play", false);
    ddl = gui->addDropDownList("levels", levels);

    ddl->setAllowMultiple(false);
    ddl->setAutoClose(true);
    ddl->setShowCurrentSelected(true);
    gui->setTheme(OFX_UI_THEME_COOLCLAY);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    ofAddListener(gameOverGui->newGUIEvent, this, &testApp::guiEvent);
	ofEnableSmoothing();
    ofSetRectMode(OF_RECTMODE_CORNER);
    textBig.loadFont("cdb.ttf",30);
    textSmall.loadFont("cdb.ttf",11);
    textBig.setLetterSpacing(1);
    ofEnableTextureEdgeHack();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
/* load sound effects */
    enemySound.loadSound("bad.aif");
    movementSound.loadSound("click.wav");
    collectableSound.loadSound("square.wav");
    movingSound.loadSound("click.wav");
/* turn the volume down for effects */
    movementSound.setVolume(.2);
    movingSound.setVolume(.2);
    collectableSound.setVolume(.2);
    
/* load the background music */
    backgroundMusic.loadSound("loop.wav");
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(1);

    gameState = WAITING_TO_PLAY;
    currentPattern = 0;

}


//--------------------------------------------------------------
void testApp::loadLevel(string levelName) {
    //initialize our protagonist in the center of the screen
    protagonist.create(ofGetWidth()/2, ofGetHeight()/2, 25);
    //clear any existing patterns, enemies, and collectables
    patterns.clear();
    enemies.clear();
    collectables.clear();
    //load the level
    if (XML.loadFile(levelName)) {

        //load values from the xml files, use defaults if they don't exist
        speed = XML.getValue("speed", -1);
//        backgroundMusic.setSpeed(abs(speed));
        multiplier = XML.getValue("multiplier", 1.08);
        completionAmount = XML.getValue("complete", 10);
        for (int i = 0; i < XML.getNumTags("file"); i++) {
            string filename = XML.getValue("file", "error.xml", i);
            cout << "Loading " << filename << endl;
            patterns.push_back("levels/" + filename);
        }
    }
}

//--------------------------------------------------------------

void testApp::loadPattern(int pattern) {
    if( XML.loadFile(patterns[pattern]) ){
        // if successful, run any additional code here
    }
    
    speed *= multiplier;
  //  backgroundMusic.setSpeed(abs(speed));

    //load enemies

    for (int i = 0; i < XML.getNumTags("enemy"); i++) {
        Enemy tmpEnemy;
        tmpEnemy.create(XML.getValue("enemy:x", 0, i), XML.getValue("enemy:y", 0, i) + SPACE_BETWEEN_PATTERNS, speed, XML.getValue("enemy:size", 0, i));
        enemies.push_back(tmpEnemy);
        
    }
    
    //load collectables
    for (int i = 0; i < XML.getNumTags("collectable"); i++) {
        Collectable tmpCollectable;
        tmpCollectable.create(XML.getValue("collectable:x", 0, i), XML.getValue("collectable:y", 0, i) + SPACE_BETWEEN_PATTERNS, speed, XML.getValue("collectable:size", 0, i));
        collectables.push_back(tmpCollectable);
        
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    //if we allow more saviors to be created, this creates a pretty interesting and ... possibly confusing control scheme
    //saviors are what get placed when you touch the screen and the protagonist is attracted to them.
    if (saviors.size() > 0) {
        
        protagonist.moveTo(saviors[0].x, saviors[0].y);
        if (ofDist(protagonist.x, protagonist.y, saviors[0].x, saviors[0].y) <= 1) {
            // movingSound.play();
            saviors[0].consumed = true;
        }
    }
    //remove the point once reached
    ofRemove(saviors, consumed);

    //now we go for specific states
    switch (gameState) {
        case WAITING_TO_PLAY:
            speed = -1;
            backgroundMusic.stop();
            break;
        case CREDITS:
            break;
        case GAME_CENTER:
            break;
        case NEW_GAME:
            gui->setVisible(false);
            won = false;
            currentPattern = 0;
            progressMarker = 0;
            achievedHighScore = false;
            backgroundMusic.play();
            gameState = PLAYING;
            break;
        case PLAYING:
            ofRemove(collectables, collected);
            ofRemove(enemies, passedGateway);
            if (enemies.size() <= 0 && collectables.size() <= 0) {
                loadPattern(currentPattern%patterns.size());
                currentPattern++;
            }
            
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].distanceToProtagonist = ofDist(enemies[i].x, enemies[i].y, protagonist.x + protagonist.width/2, protagonist.y + protagonist.height/2);
                
                if (protagonist.collide(enemies[i])) {
                    protagonist.change(3);
                    enemies[i].hit = true;
                    enemySound.play();
                }
            }
            for (int i = 0; i < collectables.size(); i++) {
                collectables[i].distanceToProtagonist = ofDist(collectables[i].x + collectables[i].width/2, collectables[i].y + collectables[i].height/2, protagonist.x + protagonist.width/2, protagonist.y + protagonist.height/2);
                
                if (collectables[i].collected == false) {
                    if (protagonist.collide(collectables[i])) {
                        float pitch = ofMap(collectables[i].width, 5, ofGetWidth(), 5, .02);
                        collectableSound.setSpeed(pitch);
                        collectableSound.play();
                        collectables[i].collected = true;
                    }
                }
            }
            
            
            if (protagonist.sides == DEAD) {
                gameState = GAME_OVER;
                gameOverGui->setVisible(true);

            }
            
            if (progressMarker >= completionAmount) {
                gameState = WON_TRACK;
                gameOverGui->setVisible(true);

            }
            
            
            
            break;
        case WON_TRACK:
            won = true;
        case GAME_OVER:
            enemies.clear();
            collectables.clear();
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
    
    switch (gameState) {
        case WAITING_TO_PLAY:
            ofSetColor(127, 127, 127);
            textSmall.drawStringCentered("keep your edge", ofGetWidth()/2, 50);
            break;
        case CREDITS:
            
            break;
        case GAME_CENTER:
            break;
        case PLAYING:
            protagonist.display();
            progressMarker += protagonist.collectEdge();
            for (int i = 0; i < saviors.size(); i++) {
                saviors[i].display();
            }
            
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].display();
            }
            for (int i = 0; i < collectables.size(); i++) {
                collectables[i].display();
            }
            
            ofSetColor(0, 0, 0);
            ofFill();
            //going extra long in case of retina
            ofRect(0, ofGetHeight() - 40, ofGetWidth()*2, 60);
            ofSetColor(255, 255, 255);
            textSmall.drawString("EDGES " + ofToString(progressMarker) + " / " + ofToString(completionAmount), 20, ofGetHeight() - 30);
            break;
            
        case GAME_OVER:

            ofSetColor(127, 127, 127);
            if (won) {
                textSmall.drawStringCentered("you won!", ofGetWidth()/2, 60);
            }
            else {
                textSmall.drawStringCentered("game over", ofGetWidth()/2, 60);
                
            }

            break;
        default:
            break;
    }
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //our crazy control scheme. create spots that we move the protagonist to... everywhere.
    if (y <= ofGetHeight() - 60) {
        Savior tmpSavior;
        tmpSavior.create(x,y);
        //comment this out for a weird control scheme :)
        saviors.clear();
        // end
        saviors.push_back(tmpSavior);
       // movementSound.play();
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    switch (gameState) {
        case WAITING_TO_PLAY:
            //gameState = PLAYING;
            
            break;
        case PLAYING:
            break;
        case GAME_OVER:
            gameState = WAITING_TO_PLAY;
            protagonist.sides = HEALTHY;
            enemies.clear();
            collectables.clear();
            saviors.clear();
            
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void testApp::exit()
{
    delete gui;
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    if(name == "play") {

        vector<ofxUIWidget *> &selected = ddl->getSelected();
        for(int i = 0; i < selected.size(); i++)
        {
            if (selected[i]->getName() != "levels") {
                loadLevel("levels/" + selected[i]->getName() + ".level");
                cout << "SELECTED: " << selected[i]->getName() << endl;
                gameState = NEW_GAME;

            }
        }
    }
    else if(name == "main menu") {
        gameState = WAITING_TO_PLAY;
        gameOverGui->setVisible(false);
        gui->setVisible(true);
    }
}
bool testApp::consumed(Savior &savior){
	return (savior.consumed);
}

bool testApp::passedGateway(Enemy &enemy){
	return (enemy.y >= ofGetHeight() + enemy.radius);
}

bool testApp::collected(Collectable &collectable) {
    return (collectable.y > ofGetHeight() + collectable.height);
    
}


