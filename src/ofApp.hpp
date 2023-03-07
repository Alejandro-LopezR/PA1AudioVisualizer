#pragma once


#include "AudioVisualizer.hpp"
#include "ofMain.h"


class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;
    bool repeat = false; // Used in 'r' case
    bool drag = false; // Used for dragging function
    bool playing = false;
    bool pause = false; // Used in 'a' case
    bool looping = false; // Used in 'l' case
    char mode = '1';
    char curMode = 'x'; // Used in 'l', 'r', and 'b' cases
    int soundID = 0; // Added sound ID to identify songs 
    std::string Cur_song[4] = {"beat.wav","geesebeat.wav","pigeon-coo.wav","rock-song.wav"}; // Used in 'l' case
    int randomint = 1 + (rand() % 4); // Used in 'b' case, gives random int 

    int cur_x, cur_y = 0;
    float sound_length;

    float progress = 0;
    float lastPos = 0;

  public:
    void setup();
    void update();
    void draw();

    void drawMode1(vector<float> amplitudes);
    void drawMode2(vector<float> amplitudes);
    void drawMode3(vector<float> amplitudes);
    void drawMode4(vector<float> amplitudes); // Added for drawMode4

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
