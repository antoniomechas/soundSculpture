#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofxFFTLive.h"
#include "ofxFFTFile.h"
#include "ofxObjLoader.h"
#include "ofxPostProcessing.h"
#include "SoundBox.h"
#include "Matrix3D.h"
#include "shadowMapLight.h"
#include "AVGSistPart.h"
#include "ofxCameraSaveLoad.h"
#include "Particulas.h"
#include "ofxBeatDetector.h"
#include "SoundShader.h"
#include "Onda.h"

#define PRESET_MODEL 1
#define PRESET_MATRIX3D 2
#define PRESET_PARTICLES 3
#define PRESET_AUDIO_OBJECTS 4
#define PRESET_AUDIO_SHADER 5
#define PRESET_ONDA 6
#define PRESET_MAX 7

class ofApp : public ofBaseApp{

public:

    void setup();
    void setupGui();
	void update();
    void draw();
	void setNormals( ofMesh &mesh );
	void setupLigths();

	void drawPresetMatrix3D();
	void drawPresetModel();
	void drawPresetParticles();
	void drawPresetAudioObjects();

	void setupLights();
	void drawShadow();

	void drawScene();

	void drawFboTest();
	void drawLine();
	void updateSoundObjects();
	void drawSoundObjects();

	void loadSettings( int preset );
	void saveSettings( int preset );

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxPanel			gui;
    ofxPanel			gui2;
	ofxIntSlider		presetType;
	ofxIntSlider		drawMode;
    ofxSlider<int>		meshIndex;
    ofxToggle			bUseDepthTest;
    ofxToggle			bUseTexture;
    ofxToggle			bUseAudioInput;
    ofxSlider<float>	audioPeakDecay;
    ofxSlider<float>	audioMaxDecay;
    ofxToggle			audioMirror;
    ofxFloatSlider		scale;
	ofxFloatSlider		audioMult;
	ofxFloatSlider		lineWidth;
	ofxToggle			bFXBloom;
	ofxToggle			bFXFxaa;
	ofxFloatSlider		paramBeatHatValue;
	ofxFloatSlider		paramBeatSnareValue;
	ofxFloatSlider		paramBeatKickValue;
	ofxFloatSlider		paramBeatLowValue;
	ofxFloatSlider		paramBeatMidValue;
	ofxFloatSlider		paramBeatHighValue;
	ofxToggle			paramLightEnable;
	ofxFloatSlider		paramLightDistance;

    ofxFFTLive			fftLive;
    ofxFFTFile			fftFile;
	ofxBeatDetector		beatDetector;

    ofEasyCam			camera;
    
    ofTexture			meshTexture;
    ofxAssimpModelLoader model;
    vector<ofMesh>		meshes;
    ofMesh				meshWarped;

	ofSoundPlayer		player;

	float				cameraDist;
	float				cameraRotation;

	ofVec3f				current;
	
	ofFbo				rgbaFboFloat;
	int					fadeAmnt;

	bool				bGuiVisible;

	ofxPostProcessing	post;
	ofIcoSpherePrimitive *icoSphere;

	vector<SoundBox>	soundBoxes;

	Matrix3D			matrix3D;

    ofEasyCam			m_cam;
    ShadowMapLight		m_shadowLight;
    
    ofShader			m_shader;
    
    float				m_angle;    
    bool				m_bDrawDepth;
    bool				m_bDrawLight;
	bool				m_bPaused;

	int					iPresetActual;

	Particulas			particulas;
	ofLight				light;

	SoundShader			soundShader;
	bool				bFullScreen;

	Onda				onda;
};
