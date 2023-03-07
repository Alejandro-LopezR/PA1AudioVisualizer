#include "ofApp.hpp"
//--------------------------------------------------------------
void ofApp::setup() {
    sound.load("beat.wav");           // Loads a sound file (in bin/data/)
    sound.setLoop(false);              // Makes the song loop indefinitely (incorrect); changed so that songs do NOT loop at start
    sound.setVolume(1);               // Sets the song volume
    ofSetBackgroundColor(136,232, 156); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();               // Updates all sound players
    if(!pause){visualizer.updateAmplitudes();} // Updates Amplitudes for visualizer
    progress = sound.getPosition();
    // Looping function for case 'l'
    if(looping){
            if(sound.getPosition() >= .99){
              soundID++;
              if(soundID == 4){
                soundID = 0;
            }
              sound.load(Cur_song[soundID]);
              sound.play();
        }
          
    }
    }

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(256);
    ofFill();
    for (int i = 0; i < ofGetWindowWidth(); i++){ // Creates progress bar
    ofDrawRectangle(0,ofGetWindowHeight()-25,i*progress,ofGetWindowHeight());
    }
    
    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);

    // Indicator that shows which mode user is in
    if(playing && mode != '3' && mode != '4'){
    if(curMode == 'l'){
        ofDrawBitmapString("Mode: Loop", 0, 45);
    }
    if(curMode == 'r'){
        ofDrawBitmapString("Mode: Repeat", 0, 45);
    }
    if(curMode == 'b'){
        ofDrawBitmapString("Mode: Shuffle", 0, 45);
        }
    }

    // Instructions for user to follow
    if(playing){
    ofDrawBitmapString("Instructions: ", ofGetWidth()-320, 15);
    ofDrawBitmapString("Press numbers 1 through 5 to activate \ndifferent visualizer modes ", ofGetWidth()-320, 30);
    ofDrawBitmapString("Press 'l' to loop through all songs \nPress 'r' to repeat current song \nPress 'b' to shuffle through songs ", ofGetWidth()-320, 60);
    ofDrawBitmapString("Press 'a' to pause visualizer \nPress 'd' to switch to next song \nPress '-' to lower volume \nPress '=' to raise volume", ofGetWidth()-320, 105);
    }

    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        drawMode1(amplitudes);
    } else if (mode == '2') {
        drawMode2(amplitudes);
    } else if (mode == '3') {
        drawMode3(amplitudes);
    } else if (mode == '4') { // Added for drawMode4 to use amplitudes
        drawMode4(amplitudes);
    }


    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
}
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(0, 0, ofRandom(0,256)); //ofRandom gives random shade of blue
    ofSetBackgroundColor(174,198,207);
    for (int i=0; i < 64; i++){ // Used to divide amplitudes with all rectangles; used in all other drawModes
        ofDrawRectangle(i*ofGetWindowWidth()/64, ofGetHeight() - 100, ofGetWindowWidth()/64 , amplitudes[0+i]); // amplitudes[0+i] makes rectangles move with sound, used in other drawModes
    }
}
void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    ofSetBackgroundColor(245,226,227);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }

}

// Custom Mode 3; Singing Skull visualizer
void ofApp::drawMode3(vector<float> amplitudes) {
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Now presenting THE LIQUIDATOR SKULL covering Bad To The Bone", 0, 15);
    ofSetBackgroundColor(155,17,30);

    if(playing){
    // Draws the skull
    ofPushMatrix(); // Used alongside ofTranslate and ofPopMatrix to facilitate drawing of complex figures, used in other drawModes, allows changing of coordinates
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // Changes origin coordinates of screen to middle to facilitate drawing in terms of center of screen

    // Draws the cranium (top part of skull)
    ofSetColor(255, 255, 255);
    ofDrawCircle(0, -100, 100);

    // Draws the mandible (bottom part of skull)
    ofSetColor(200, 200, 200);
    for(int i = 1 ;i > 0; i--){ // See drawMode1
    ofDrawRectangle(-50, -(amplitudes[0+i]), 100, 50);
    }
    // Draws the eye sockets
    ofSetColor(0);
    ofDrawCircle(-30, -60, 20);
    ofDrawCircle(30, -60, 20);

    // Draws the nasal cavity
    ofDrawTriangle(-20, -30, 0, -60, 20, -30);

    // Draws the teeth
    ofSetColor(255, 255, 255);
    for(int i = 1 ;i > 0; i--){ // See drawMode1
    ofDrawRectangle(-40, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(-20, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(0, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(20, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(40, -(amplitudes[0+i]), 10, 10);
    }
    ofPopMatrix(); // Used alongside ofPushMatrix to facilitate drawing, resets to original coordinate system
}
}

// Custom Mode 4; DSOTM Visualizer
void ofApp::drawMode4(vector<float> amplitudes) {
    ofSetColor(256);
    ofDrawBitmapString("Any Colour You Like as recorded in Pink Floyd's Dark Side Of The Moon", 0, 15);
    ofSetBackgroundColor(0,0,0);
    if (playing) {
    ofPushMatrix(); // See drawMode3
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // See drawMode3
    
    //White
    ofFill();
    ofRotateDeg(-10);
    ofSetColor(256, 256, 256);
    ofDrawRectangle(-42, -35, -ofGetWidth(), 5);
    ofRotateDeg(10);

    
    ofRotateDeg(10);
    for(int i = 1 ;i > 0; i--){ // See drawMode1
    //Red
    ofSetColor(255, 0, 0);
    ofDrawRectangle(30.5, -50, -(amplitudes[0+i]) + ofGetWidth()/4, 7.5); // See drawMode1

    //Orange
    ofSetColor(255, 165, 0);
    ofDrawRectangle(35.7, -42.5, -(amplitudes[0+i])  + ofGetWidth()/4, 7.5); // See drawMode1

    //Yellow
    ofSetColor(256, 256, 0);
    ofDrawRectangle(43, -35, -(amplitudes[0+i]) + ofGetWidth()/4, 7.5); // See drawMode1

    //Green
    ofSetColor(0, 256, 0);
    ofDrawRectangle(50, -27.5, -(amplitudes[0+i]) + ofGetWidth()/4, 7.5); // See drawMode1

    //Blue
    ofSetColor(0, 150, 255);
    ofDrawRectangle(56, -20, -(amplitudes[0+i]) + ofGetWidth()/4, 7.5); // See drawMode1

    //Purple
    ofSetColor(221,160,221);
    ofDrawRectangle(64, -12.5, -(amplitudes[0+i]) + ofGetWidth()/4, 7.5); // See drawMode1
    }
    ofRotateDeg(-10);

    //Triangle
    ofSetLineWidth(5);
    ofNoFill();
    ofSetColor(256, 256, 256);
    ofDrawTriangle(-125, 100, 0, -100, 125, 100);

    ofPopMatrix(); // See drawMode3
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        if(playing && mode == '3'){ // Makes loaded song play exclusively for drawMode3
        sound.load("Bad To The Bone.wav");
        sound.play();
        }
        break;
    case '4':
        mode = '4';
        if (playing && mode == '4'){ // Makes loaded song play exclusively for drawMode4
        sound.load("Any Colour You Like.wav");
        sound.play();
        }
        break;

    case 'a': // Pause visualizer function
        if(pause){
            pause = false;
        } else {
            pause = true;
        }
        break;

    case 'd': // Play next song function
     if (playing && mode != '3' && mode != '4'){
        soundID += 1;
        if (soundID == 1){
            sound.load("geesebeat.wav");             
                }
        else if (soundID == 2){
            sound.load("pigeon-coo.wav");
                }
        else if (soundID == 3){
            sound.load("rock-song.wav");
                }
        else if(soundID == 4){
            soundID = 0;
            sound.load("beat.wav");
            }
        sound.setLoop(repeat);
        sound.play();
     }
        break;

    case 'b': // Shuffle mode function, plays random song
    if (playing && mode != '3' && mode != '4' && curMode != 'l' && curMode != 'r'){ // Makes it so that no more than one mode can be selected at a time
        curMode = 'b';
        int randomint = 1 + (rand() % 4);
        soundID = randomint; 
        if (soundID == 1){
            sound.load("geesebeat.wav");             
                }
        else if (soundID == 2){
            sound.load("pigeon-coo.wav");
                }
        else if (soundID == 3){
            sound.load("rock-song.wav");
                }
        else if(soundID == 4){
            soundID = 0;
            sound.load("beat.wav");
            }
        sound.setLoop(repeat);
        sound.play();
    }
    break;

    case 'l': // Loop mode function, once song ends the next one is played
    if(playing && mode != '3' && mode != '4' && curMode != 'r'){ // Makes it so that no more than one mode can be selected at a time
    curMode = 'l';
        if(looping){
            looping = false;
            curMode = 'x'; // Resets curMode variable, used in main ifs in 'l', 'r', and 'b' modes
        } else {
            looping = !looping;
        }
        }
    break;
      
    case '-': // Lowers volume
        if (sound.getVolume() > 0.1){
        sound.setVolume(sound.getVolume() - 0.1);
        }
        sound.setLoop(repeat);
        break;
    case '=': // Increases volume
        if (sound.getVolume() < 1){
        sound.setVolume(sound.getVolume() + 0.1);
        }
        sound.setLoop(repeat);
        break;
    
    case 'r': // Repeat mode function, once song ends it is played again
        if(playing && mode != '3' && mode != '4' && curMode != 'l'){ // Makes it so that no more than one mode can be selected at a time
        curMode = 'r';
        if (repeat){
            sound.setLoop(false);
            curMode = 'x'; // Resets curMode variable, used in main ifs in 'l', 'r', and 'b' modes
        } else {
            sound.setLoop(true);
        }
        repeat = !repeat;
        }
        break;
                }
            }
    

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    cur_x = x;
    cur_y = y;
    if(cur_y >= ofGetHeight() - 25 && ofGetWidth() && playing){
        sound.setPosition(round(ofGetMouseX()*100/ofGetWidth())/100);
        update();
}   

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if(cur_y >= ofGetHeight() - 25 && ofGetWidth() && playing){
        sound.setPaused(true);

    } 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    sound.setPaused(false);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------