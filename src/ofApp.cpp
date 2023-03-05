#include "ofApp.hpp"
//--------------------------------------------------------------
void ofApp::setup() {
    sound.load("beat.wav");           // Loads a sound file (in bin/data/)
    sound.setLoop(true);              // Makes the song loop indefinitely
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
}

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(256);
    ofFill();
    for (int i = 0; i < ofGetWindowWidth(); i++){
    ofDrawRectangle(0,ofGetWindowHeight()-25,i*progress,ofGetWindowHeight());
    }

    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);

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
    }

    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
}
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(0, 0, ofRandom(0,256));
    ofSetBackgroundColor(174,198,207);
    for (int i=0; i < 64; i++){
        ofDrawRectangle(i*ofGetWindowWidth()/64, ofGetHeight() - 100, ofGetWindowWidth()/64 , amplitudes[0+i]);
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


// void ofApp::drawMode3(vector<float> amplitudes) {
//     ofSetColor(256); // This resets the color of the "brush" to white
//     ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
//     ofSetBackgroundColor(155,17,30);
//     // YOUR CODE HERE
    
// } 

/// skull
void ofApp::drawMode3(vector<float> amplitudes) {
    // Set the background color to black
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Now presenting THE LIQUIDATOR SKULL covering Bad To The Bone", 0, 15);
    ofSetBackgroundColor(155,17,30);

    // Draw the skull
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    // Draw the cranium (top part of skull)
    ofSetColor(255, 255, 255);
    ofDrawCircle(0, -100, 100);

    // Draw the mandible (bottom part of skull)
    ofSetColor(200, 200, 200);
    for(int i = 5 ;i > 0; i--){
    ofDrawRectangle(-50, -(amplitudes[0+i]), 100, 50);
    }
    // Draw the eye sockets
    ofSetColor(0);
    ofDrawCircle(-30, -60, 20);
    ofDrawCircle(30, -60, 20);

    // Draw the nasal cavity
    ofDrawTriangle(-20, -30, 0, -60, 20, -30);

    // Draw the teeth
    ofSetColor(255, 255, 255);
    for(int i = 5 ;i > 0; i--){
    ofDrawRectangle(-40, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(-20, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(0, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(20, -(amplitudes[0+i]), 10, 10);
    ofDrawRectangle(40, -(amplitudes[0+i]), 10, 10);
    }
    ofPopMatrix();
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
        sound.load("Bad To The Bone.wav");
        sound.play();
        break;
    case 'a':
        if(pause){
            pause = false;
        } else {
            pause = true;
        }
        break;
    case 'd':
     if (playing){
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
        sound.setLoop(true);
        sound.play();
     }
        break;
      
    case '-':
        if (sound.getVolume() > 0.1){
        sound.setVolume(sound.getVolume() - 0.1);
        break;
    }
    case '=':
        if (sound.getVolume() < 1){
        sound.setVolume(sound.getVolume() + 0.1);
        break;
        }
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
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
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