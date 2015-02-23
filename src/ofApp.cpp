#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

    ofLoadImage(meshTexture, "texture.jpg");
    
    //--------------------------------------------------------------
    ofMesh customMesh;
    customMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    customMesh.addVertex(ofVec3f(-100, -100));
    customMesh.addVertex(ofVec3f(-100, 100));
    customMesh.addVertex(ofVec3f(100, -100));
    customMesh.addVertex(ofVec3f(100, 100));
    
    customMesh.addTexCoord(ofVec2f(0, 0));
    customMesh.addTexCoord(ofVec2f(0, 1));
    customMesh.addTexCoord(ofVec2f(1, 0));
    customMesh.addTexCoord(ofVec2f(1, 1));
    
    customMesh.addIndex(0);
    customMesh.addIndex(3);
    customMesh.addIndex(1);
    
    customMesh.addIndex(0);
    customMesh.addIndex(2);
    customMesh.addIndex(3);
    
    //--------------------------------------------------------------
    ofSpherePrimitive sphere(100, 10, OF_PRIMITIVE_TRIANGLES);
   
    //--------------------------------------------------------------
    //model.loadModel("head.dae");
    model.loadModel("dinosaur.dae");

	//--------------------------------------------------------------
    meshes.push_back(customMesh);
    meshes.push_back(sphere.getMesh());
    meshes.push_back(model.getMesh(0));
    
    //--------------------------------------------------------------
    fftLive.setup();

	fftFile.setup();

	player.loadSound("techno.mp3");
	player.setLoop(true);
	player.play();
	
	fftFile.player = &player;

    //--------------------------------------------------------------
    string guiPath = "audio.xml";
    gui.setup("audio", guiPath, 20, 20);
    gui.add(meshIndex.setup("meshIndex", 1, 0, meshes.size()-1));
    gui.add(bUseTexture.setup("bUseTexture", false));
    gui.add(bUseAudioInput.setup("bUseAudioInput", true));
    gui.add(audioPeakDecay.setup("audioPeakDecay", 0.915, 0.9, 1.0));
    gui.add(audioMaxDecay.setup("audioMaxDecay", 0.995, 0.9, 1.0));
    gui.add(audioMirror.setup("audioMirror", true));
    gui.loadFromFile(guiPath);

    cameraDist = 400;

	rgbaFboFloat.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
	//rgbaFboFloat.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
	
	rgbaFboFloat.begin();
	ofClear(255,255,255, 0);
    rgbaFboFloat.end();
}

//--------------------------------------------------------------
void ofApp::update(){

    float scale = 50.0f;

	fftFile.setPeakDecay(audioPeakDecay);
    fftFile.setMaxDecay(audioMaxDecay);
    fftFile.setMirrorData(audioMirror);
    fftFile.update();
	
	fftLive.setPeakDecay(audioPeakDecay);
    fftLive.setMaxDecay(audioMaxDecay);
    fftLive.setMirrorData(audioMirror);
    fftLive.update();

    //---------------------------------------------------------- dispacing mesh using audio.
    ofMesh & meshOriginal = meshes[meshIndex];
    meshWarped = meshOriginal;
    
    if(bUseAudioInput == false) {
        return;
    }
    
    vector<ofVec3f> & vertsOriginal = meshOriginal.getVertices();
    vector<ofVec3f> & vertsWarped = meshWarped.getVertices();
    int numOfVerts = meshOriginal.getNumVertices();
    
    float * audioData = new float[numOfVerts];
    //fftLive.getFftPeakData(audioData, numOfVerts);

	fftFile.getFftPeakData(audioData, numOfVerts);
    
   
	float meshDisplacement = 100;
    meshWarped.clearColors();
    for(int i=0; i<numOfVerts; i++) {

		float t = (2 + ofGetElapsedTimef()) * .1;

		float audioValue = audioData[i];
		ofVec3f & vertOriginal = vertsOriginal[i] * scale;
        ofVec3f & vertWarped = vertsWarped[i];
        ofVec3f dir = vertOriginal;
		float mult = 100;
		dir.x = dir.x + ofNoise(vertOriginal.x + t,0,0) * mult;
		dir.y = dir.y + ofNoise(0,vertOriginal.y + t,0) * mult;
		dir.z = dir.z + ofNoise(0,0,vertOriginal.z + t) * mult;
		ofVec3f direction = dir.getNormalized();
        //ofVec3f direction = vertOriginal.getNormalized();
        vertWarped = vertOriginal + direction * meshDisplacement * audioValue;

		float r = ofNoise(t,0,0) * audioValue * vertOriginal.normalized().x * 2.0;
		float g = ofNoise(0,t,0) * audioValue * vertOriginal.normalized().y * 2.0;
		float b = ofNoise(0,0,t) * audioValue * vertOriginal.normalized().z * 2.0;
		r = MAX(0.1, r);
		g = MAX(0.1, g);
		b = MAX(0.1, b);
		meshWarped.addColor(ofFloatColor(r, g, b));
    }
    
    delete[] audioData;

 //   ofEnableAlphaBlending();
	//
 //   rgbaFboFloat.begin();
	//	//ofClear(255,255,255, 0);
	//	//drawScene();
	//	drawFboTest();
	//rgbaFboFloat.end();

}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
	//we clear the fbo if c is pressed. 
	//this completely clears the buffer so you won't see any trails
	if( ofGetKeyPressed('c') ){
		ofClear(255,255,255, 0);
	}	
	
	//some different alpha values for fading the fbo
	//the lower the number, the longer the trails will take to fade away.
	fadeAmnt = 40;
	if(ofGetKeyPressed('1')){
		fadeAmnt = 1;
	}else if(ofGetKeyPressed('2')){
		fadeAmnt = 5;
	}else if(ofGetKeyPressed('3')){
		fadeAmnt = 15;
	}  

	//1 - Fade Fbo
	
	//this is where we fade the fbo
	//by drawing a rectangle the size of the fbo with a small alpha value, we can slowly fade the current contents of the fbo. 
	ofFill();
	ofSetColor(255,255,255, fadeAmnt);
	ofRect(0,0,ofGetWidth(), ofGetHeight());

	//2 - Draw graphics
	
	ofNoFill();
	ofSetColor(255,255,255);

	drawScene();

}


//--------------------------------------------------------------
void ofApp::draw(){
	
	
	//ofBackground(0,0,0);

    //----------------------------------------------------------
    gui.draw();
	
	ofSetColor(255,255,255);
	
	//rgbaFboFloat.draw(0,0);

	drawScene();

	//ofSetColor(ofColor::white);
}



void ofApp::drawScene()
{

	ofSpherePrimitive sphere(2, 5, OF_PRIMITIVE_TRIANGLES);

    int w = 512;
    int h = 256;
    int x = 20;
    int y = ofGetHeight() - h - 20;
    //fftLive.draw(x, y, w, h);
    //fftFile.draw(x, y, w, h);
    
    //----------------------------------------------------------
    ofEnableDepthTest();

	// generate a noisy 3d position over time 
	float t = (2 + ofGetElapsedTimef()) * .1;
	//current.x = ofSignedNoise(t, 0, 0);
	//current.y = ofSignedNoise(0, t, 0);
	//current.z = ofSignedNoise(0, 0, t);
	//current *= 400; // scale from -1,+1 range to -400,+400
	current.x = 200 + ofNoise(t, 0, 0) * 200.0;
	current.y = 200 + ofNoise(0, t, 0) * 200.0;
	current.z = 200 + ofNoise(0, 0, t) * 200.0;

	//cameraDist = 200.0f + 200.0f * fftFile.getAveragePeak();

	camera.disableMouseInput();
    camera.setDistance(cameraDist);
    camera.setGlobalPosition(current);
	camera.lookAt(ofVec3f(0,0,0));

	camera.begin();
    
    if(bUseTexture == true) {
        ofEnableNormalizedTexCoords();
        meshTexture.bind();
    }

    ofSetColor(ofColor::white);
    //meshWarped.setMode(OF_PRIMITIVE_POINTS);
    meshWarped.setMode(OF_PRIMITIVE_LINES);
	meshWarped.draw();
    
	//for (int i = 0 ; i < meshWarped.getNumVertices() ; i++)
	//{
	//	ofPushMatrix();
	//	ofTranslate(meshWarped.getVertices()[i]);
	//	ofSetColor(meshWarped.getColors()[i]);
	//	sphere.drawWireframe();
	//	ofPopMatrix();
	//	//ofSphere(meshWarped.getVertices()[i],2);
	//}
    if(bUseTexture == true) {
        meshTexture.unbind();
        ofDisableNormalizedTexCoords();
    }
    
    //ofSetColor(ofColor::black);
    //meshWarped.drawWireframe();
    
    camera.end();
    
    ofDisableDepthTest();

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_LEFT) {
        meshIndex = meshIndex - 1;
        if(meshIndex < 0) {
            meshIndex = meshes.size() - 1;
        }
    } else if(key == OF_KEY_RIGHT) {
        meshIndex = meshIndex + 1;
        if(meshIndex > meshes.size() - 1) {
            meshIndex = 0;
        }
    } else if(key == ' ') {
        bUseAudioInput = !bUseAudioInput;
    } else if(key == 'e' || key == 'E') {
        ofxObjLoader::save("mesh_export.obj", meshWarped);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}