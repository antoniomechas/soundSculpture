#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofxFFTLive.h"
#include "ofxFFTFile.h"
#include "ofxObjLoader.h"

class ofApp : public ofBaseApp{

public:

    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxPanel gui;
    ofxSlider<int> meshIndex;
    ofxToggle bUseTexture;
    ofxToggle bUseAudioInput;
    ofxSlider<float> audioPeakDecay;
    ofxSlider<float> audioMaxDecay;
    ofxToggle audioMirror;
    
    ofxFFTLive fftLive;
    ofxFFTFile fftFile;

    ofEasyCam camera;
    
    ofTexture meshTexture;
    ofxAssimpModelLoader model;
    vector<ofMesh> meshes;
    ofMesh meshWarped;

	ofSoundPlayer player;

	float cameraDist;
	float cameraRotation;

	ofVec3f current;


};
