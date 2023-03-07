#pragma once


#include "AudioVisualizer.hpp"
#include "ofMain.h"


class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;
    bool repeat = false;
    bool playing = false;
    bool pause = false;
    bool looping = false;
    char mode = '1';
    char curMode = 'x';
    int soundID = 0; //added sound ID to identify songs 
    std::string Cur_song[4] = {"beat.wav","geesebeat.wav","pigeon-coo.wav","rock-song.wav"};
    int randomint = 1+ (rand() % 4); // added code to get random int 

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
    void drawMode4(vector<float> amplitudes);

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
