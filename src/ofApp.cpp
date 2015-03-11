#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

    ofLoadImage(meshTexture, "texture.jpg");
    //ofLoadImage(meshTexture, "estuco2.jpg");
    
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
    
	//creo un box en vez de un plano
	customMesh.clear();
	ofBoxPrimitive box(10,10,10);
	customMesh = box.getMesh();

    //--------------------------------------------------------------
    ofSpherePrimitive sphere(100, 10, OF_PRIMITIVE_POINTS);
    ofPlanePrimitive plane(200,300,20,30, OF_PRIMITIVE_POINTS);
	icoSphere = new ofIcoSpherePrimitive(100,5);
    //--------------------------------------------------------------
	//--------------------------------------------------------------
    meshes.push_back(icoSphere->getMesh());
    meshes.push_back(customMesh);
    meshes.push_back(sphere.getMesh());
    //meshes.push_back(plane.getMesh());

	//model.loadModel("dinosaur.dae");
 //   meshes.push_back(model.getMesh(0));
 //   
	//model.clear();
	//model.loadModel("head.dae");
 //   meshes.push_back(model.getMesh(0));
 //   
	//model.clear();
	//model.loadModel("Medusa.3DS");
	//meshes.push_back(model.getMesh(2));

	//model.clear();
	//model.loadModel("BigFish/fish.dae");
	//meshes.push_back(model.getMesh(0));
	//ofMesh tmp;
	//for (int i = 0; i < model.getMeshCount() ; i++)
	//{
	//	//tmp.addVertices(model.getMesh(i).getVertices());
	//	meshes.push_back(model.getMesh(i));
	//}
    
    //--------------------------------------------------------------
    fftLive.setup();

	fftFile.setup();

	player.loadSound("music/3.mp3");
	player.setLoop(true);
	//player.setVolume(0.05);
	player.play();
	fftFile.player = &player;
	beatDetector.enableBeatDetect();

	cameraDist = 400;

	rgbaFboFloat.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
	//rgbaFboFloat.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); // with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
	
	rgbaFboFloat.begin();
	ofClear(255,255,255, 0);
    rgbaFboFloat.end();

	// Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<FxaaPass>()->setEnabled(true);
    //post.createPass<DofPass>()->setEnabled(false);
    //post.createPass<KaleidoscopePass>()->setEnabled(false);
    //post.createPass<NoiseWarpPass>()->setEnabled(false);
    //post.createPass<PixelatePass>()->setEnabled(false);
    //post.createPass<EdgePass>()->setEnabled(false);
    //post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    //post.createPass<GodRaysPass>()->setEnabled(false);
	SoundBox *s;
	for (int i = 0 ; i < 3 ; i++)
	{
		s = new SoundBox;
		s->setup(ofVec3f(ofRandom(-100,100),ofRandom(-100,100),ofRandom(-100,100)),ofVec3f(0,0,0),ofRandom(30,80));
		soundBoxes.push_back(*s);
		delete s;
	}

	//s.setup(ofVec3f(100,50,100),ofVec3f(0,0,0),50);
	//soundBoxes.push_back(s);

	//s.setup(ofVec3f(200,200,200),ofVec3f(0,0,0),80);
	//soundBoxes.push_back(s);
	int cols = 120;
	int rows = (float)cols * (float)((float)ofGetHeight() / (float)ofGetWidth());
	matrix3D.setup(ofGetWidth(),ofGetHeight(),cols, rows);
	
	//m_cam.setupPerspective( false, 45.0f, 0.1f, 100.0f );
 //   m_cam.setDistance(40.0f);
 //   m_cam.setGlobalPosition( 30.0f, 15.0f, 20.0f );
    
    m_cam.lookAt( ofVec3f( 0.0f, 0.0f, 0.0f ) );
	m_shader.load( "shaders/mainScene.vert", "shaders/mainScene.frag" );
    m_bPaused = false;
	m_angle = 0;
    setupLights();

	iPresetActual = 1;
	setupGui();
	loadSettings(iPresetActual);

	particulas.setup(ofGetWidth(),ofGetHeight(), &beatDetector);
}

void ofApp::setupGui()
{
	//--------------------------------------------------------------
	bGuiVisible = false;
    gui.setup("audio");
    gui.add(presetType.setup("presetType", 1, 1, PRESET_MAX - 1));
    gui.add(drawMode.setup("drawMode", 1, 1, 3));
    gui.add(meshIndex.setup("meshIndex", 1, 1, meshes.size()-1));
    gui.add(bUseDepthTest.setup("use Depth Test", false));
    gui.add(bUseTexture.setup("use Texture", false));
    gui.add(scale.setup("scale", 1.0, 0.1f, 100.0));
    gui.add(bUseAudioInput.setup("bUseAudioInput", true));
    gui.add(audioMult.setup("audioMult", 1.0, 0.11, 5.0));
    gui.add(audioPeakDecay.setup("audioPeakDecay", 0.915, 0.9, 1.0));
    gui.add(audioMaxDecay.setup("audioMaxDecay", 0.995, 0.9, 1.0));
    gui.add(audioMirror.setup("audioMirror", true));
    gui.add(lineWidth.setup("linewidth", 1.0, 0.5, 10.0));
    gui.add(bFXBloom.setup("FX Bloom", true));
    gui.add(bFXFxaa.setup("FX fxaa", true));
	gui.add(matrix3D.paramLightDistance.setup("matrix Light Dist",100,50,1000));
	gui.add(matrix3D.paramMaxLenght.setup("matrix Max Lenght",100,5,500));
	gui.add(matrix3D.paramMult.setup("matrix Mult",1,1,20));
	gui.add(matrix3D.paramDamp.setup("matrix Damp", 0.9,0.01,1.0));
	gui.add(matrix3D.paramWidthMult.setup("matrix width mult", 1.0,0.1,2.0));
	
    gui2.setup("Particulas");
	gui2.setPosition(gui.getPosition() + ofPoint(gui.getWidth() + 20, 0));
	gui2.add(particulas.paramDrawMode.setup( "DrawMode", 1, 0, 2 ));
	gui2.add(particulas.paramMult.setup( "Multiplicador", 1, 0.1, 20.0 ));
	gui2.add(particulas.sistPart.partTipo.setup( "part Tipo", 0, 0, 4 ));
	gui2.add(particulas.sistPart.partColorAuto.setup( "part Color Auto", false));
	gui2.add(particulas.sistPart.partColorAutoDelay.setup( "part Color A Delay", 0.1, 0.001, 1.0 ));
	gui2.add(particulas.sistPart.partColorIni.setup( "part Color Ini",ofColor(127,127,127),ofColor(0,0),ofColor(255,255)));
	gui2.add(particulas.sistPart.partColorFin.setup( "part Color Fin",ofColor(127,127,127),ofColor(0,0),ofColor(255,255)));
	gui2.add(particulas.sistPart.partVidaIni.setup( "part Vida Ini", 1, 1, 1000 ));
	gui2.add(particulas.sistPart.partVidaFin.setup( "part Vida Fin", 1, 1, 1000 ));
	gui2.add(particulas.sistPart.partSizeIni.setup( "part Size Ini", 1, 1, 100 ));
	gui2.add(particulas.sistPart.partSizeFin.setup( "part Size Fin", 1, 1, 100 ));
	gui2.add(particulas.sistPart.partAlphaIni1.setup( "part Alpha Ini 1", 1, 0.0, 1.0 ));
	gui2.add(particulas.sistPart.partAlphaIni2.setup( "part Alpha Ini 2", 1, 0.0, 1.0 ));
	gui2.add(particulas.sistPart.partAlphaFin1.setup( "part Alpha Fin 1", 1, 0.0, 1.0 ));
	gui2.add(particulas.sistPart.partAlphaFin2.setup( "part Alpha Fin 2", 1, 0.0, 1.0 ));
	gui2.add(particulas.sistPart.partDamping.setup( "part damping",  0.9f, 0.9f, 1.0f ));
	gui2.add(particulas.sistPart.partGravedad.setup( "part gravedad", 0, -0.1f, 0.1f ));
	gui2.add(particulas.sistPart.partPorcentajeEspecial.setup( "part Porcentaje Esp", 1, 0.0, 1.0 ));
	gui2.add(particulas.sistPart.partVelXmin.setup( "part vel x min", -2.0, -2.0, 2.0 ));
	gui2.add(particulas.sistPart.partVelXmax.setup( "part vel x max", 2.0, -2.0, 2.0 ));
	gui2.add(particulas.sistPart.partVelYmin.setup( "part vel y min", -2.0, -2.0, 2.0 ));
	gui2.add(particulas.sistPart.partVelYmax.setup( "part vel y max", 2.0, -2.0, 2.0 ));
	gui2.add(particulas.sistPart.partVelZ1.setup( "part Vel Z 1", 0, -2, 2 ));
	gui2.add(particulas.sistPart.partVelZ2.setup( "part Vel Z 2", 0, -2, 2 ));

}

void ofApp::setupLights() {
    //// ofxShadowMapLight extends ofLight - you can use it just like a regular light
    //// it's set up as a spotlight, all the shadow work + lighting must be handled in a shader
    //// there's an example shader in
    //
    //// shadow map resolution (must be power of 2), field of view, near, far
    //// the larger the shadow map resolution, the better the detail, but slower
    //m_shadowLight.setup( 2048, 45.0f, 0.1f, 80.0f );
    //m_shadowLight.setBlurLevel(4.0f); // amount we're blurring to soften the shadows
    //
    //m_shadowLight.setAmbientColor( ofFloatColor( 0.0f, 0.0f, 0.0f, 1.0f ) );
    //m_shadowLight.setDiffuseColor( ofFloatColor( 0.9f, 0.9f, 0.9f, 1.0f ) );
    //m_shadowLight.setSpecularColor( ofFloatColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
    //
    //m_shadowLight.setPosition( 100.0f, 100.0f, 150.0f );
    //
    //ofSetGlobalAmbientColor( ofFloatColor( 0.05f, 0.05f, 0.05f ) );
}

void ofApp::loadSettings(int preset)
{
	stringstream filename;
	filename << "settings_" << preset << ".xml";
	gui.loadFromFile(filename.str()); 
	gui2.loadFromFile(filename.str()); 

	stringstream filename2;
	filename2 << "camera_" << preset << ".xml";
	ofxLoadCamera(camera, filename2.str());

}

void ofApp::saveSettings(int preset)
{
	stringstream filename;
	filename << "settings_" << preset << ".xml";
	gui.saveToFile(filename.str()); 
	gui2.saveToFile(filename.str()); 
	
	stringstream filename2;
	filename2 << "camera_" << preset << ".xml";
	ofxSaveCamera(camera, filename2.str());
}

//--------------------------------------------------------------
void ofApp::update(){

	fftFile.setPeakDecay(audioPeakDecay);
    fftFile.setMaxDecay(audioMaxDecay);
    fftFile.setMirrorData(audioMirror);
    fftFile.update();
	//fftLive.setPeakDecay(audioPeakDecay);
 //   fftLive.setMaxDecay(audioMaxDecay);
 //   fftLive.setMirrorData(audioMirror);
 //   fftLive.update();

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
    
	float average = fftFile.getAveragePeak();

  
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
        vertWarped = vertOriginal + direction * meshDisplacement * (audioValue * audioMult);

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
	////
 //   rgbaFboFloat.begin();
	//	post.begin();
	//		//ofClear(255,255,255, 0);
	//		drawFboTest();
	//		drawLine();
	//	post.end();
	//rgbaFboFloat.end();
	
	audioData = new float[beatDetector.getFFTSize()];
	fftFile.getRawFftData(audioData, beatDetector.getFFTSize());

	//for (int i = 0; i < beatDetector.getFFTSize() ; i++)
	//	audioData[i] *= 255.0f;
	beatDetector.update(audioData);

	post[0]->setEnabled(false);
	post[1]->setEnabled(false);
	post[2]->setEnabled(false);
	post[3]->setEnabled(bFXFxaa);
	beatDetector.setBeatValue(1.0f);
	if (bFXBloom)
	{
		//if (average < 0.33)
		//	post[0]->setEnabled(true);
		//if (average < 0.66)
		//	post[1]->setEnabled(true);
		//if (average <= 1.0)
		//	post[2]->setEnabled(true);
		if (beatDetector.isBeat(0))
			post[0]->setEnabled(true);
	}

	delete [] audioData;

	updateSoundObjects();
}

void ofApp::drawShadow()
{
    glEnable( GL_DEPTH_TEST );
    
    ofDisableAlphaBlending();
    
    if (!m_bPaused) {
        //m_angle += 0.25f;
        m_angle += 2;
    }
    
    m_shadowLight.lookAt( ofVec3f(0.0,0.0,0.0) );
    m_shadowLight.orbit( m_angle, 0, 100.0f, ofVec3f(0.0,0.0,0.0) );

    m_shadowLight.enable();
   
    // render linear depth buffer from light view
    m_shadowLight.beginShadowMap();
	    glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		matrix3D.draw();
    m_shadowLight.endShadowMap();
    
    // render final scene
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
    m_shader.begin();

    m_shadowLight.bindShadowMapTexture(0); // bind shadow map texture to unit 0
    m_shader.setUniform1i("u_ShadowMap", 0); // set uniform to unit 0
    m_shader.setUniform1f("u_LinearDepthConstant", m_shadowLight.getLinearDepthScalar()); // set near/far linear scalar
    m_shader.setUniformMatrix4f("u_ShadowTransMatrix", m_shadowLight.getShadowMatrix(m_cam)); // specify our shadow matrix
    
    m_cam.begin();
    
    m_shadowLight.enable();
        glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		matrix3D.draw();
    m_shadowLight.disable();
    
    if ( m_bDrawLight ) {
        glDisable(GL_CULL_FACE);
        m_shadowLight.draw();
        glEnable(GL_CULL_FACE);
    }
    
    m_cam.end();
    
    m_shadowLight.unbindShadowMapTexture();

    m_shader.end();
    

    // Debug shadowmap
    if ( m_bDrawDepth ) {
        m_shadowLight.debugShadowMap();
    }
    
    // draw info string
    ofDisableLighting();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    ofSetColor(255, 0, 0, 255);
    ofDrawBitmapString("Press SPACE to toggle rendering the shadow map texture (linear depth map)\nPress L to toggle drawing the light\nPress P to toggle pause", ofPoint(15, 20));

}

void ofApp::updateSoundObjects()
{
	int amount = soundBoxes[0].getAudioDataAmount();
	float * audioData = new float[amount];
	fftFile.getFftPeakData(audioData, amount);
    
	float average = fftFile.getAveragePeak();
	for (int i = 0 ; i < soundBoxes.size() ; i++)
		soundBoxes[i].update(average, audioData, audioMult);

	delete [] audioData;

	amount = matrix3D.getAudioDataAmount();
	audioData = new float[amount];
	fftFile.getFftPeakData(audioData, amount);
	matrix3D.update(average, audioData);    

	amount = particulas.getAudioDataAmount();
	audioData = new float[amount];
	fftFile.getFftPeakData(audioData, amount);
	matrix3D.update(average, audioData);    

	if (presetType == PRESET_PARTICLES)
		particulas.update(average, audioData);

	

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

	//drawScene();

}


//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(0,0,0);
	ofSetColor(255,255,255);
    if (bGuiVisible)
	{
		gui.draw();
		gui2.draw();
	}

	//return;
	//drawShadow();
	//return;
	//ofBackground(0,0,0);

    //----------------------------------------------------------
	
	ofSetColor(255,255,255);
	
	//rgbaFboFloat.draw(0,0);
	ofPushMatrix();
	
	post.begin();
	
		switch (presetType)
		{
			case PRESET_MODEL:
				drawScene();
				break;
			
			case PRESET_MATRIX3D:
				drawPresetMatrix3D();
				break;

			case PRESET_PARTICLES:
				drawPresetParticles();
				break;

			case PRESET_AUDIO_OBJECTS:
				drawPresetAudioObjects();
				break;
		}

	post.end();
	ofPopMatrix();
	ofSetColor(255,255,255);
	
	int w = OFX_FFT_WIDTH;
    int h = OFX_FFT_HEIGHT;
    int x = 20;
    int y = ofGetHeight() - h - 20;
    //fftFile.draw(x, y, w, h);
	//beatDetector.drawBeats();
	//cout << "HAT: " << beatDetector.isHat() << ","
	//	<< "SNARE: " << beatDetector.isSnare() << ","
	//	<< "Kick: " << beatDetector.isKick() << "," << endl;

	if (bGuiVisible)
	{
		gui.draw();
		gui2.draw();
	}

	//ofSetColor(ofColor::white);
}


void ofApp::drawPresetParticles()
{
    if (bUseDepthTest)
		ofEnableDepthTest();

	camera.begin();
    
    if(bUseTexture == true) {
        ofEnableNormalizedTexCoords();
        meshTexture.bind();
    }

    ofSetColor(ofColor::white);

	particulas.draw();

	if(bUseTexture == true) {
        meshTexture.unbind();
        ofDisableNormalizedTexCoords();
    }

    camera.end();
    
    ofDisableDepthTest();	
}

void ofApp::drawPresetAudioObjects()
{
	if (bUseDepthTest)
		ofEnableDepthTest();

	camera.begin();
    
    if(bUseTexture == true) {
        ofEnableNormalizedTexCoords();
        meshTexture.bind();
    }

    ofSetColor(ofColor::white);

	drawSoundObjects();

	if(bUseTexture == true) {
        meshTexture.unbind();
        ofDisableNormalizedTexCoords();
    }

    camera.end();
    
    ofDisableDepthTest();	
}

void ofApp::drawPresetMatrix3D()
{
	if (bUseDepthTest)
	    ofEnableDepthTest();

	camera.begin();
    
    if(bUseTexture == true) {
        ofEnableNormalizedTexCoords();
        meshTexture.bind();
    }

    ofSetColor(ofColor::white);

	matrix3D.draw();

	if(bUseTexture == true) {
        meshTexture.unbind();
        ofDisableNormalizedTexCoords();
    }
    

    camera.end();
    
    ofDisableDepthTest();

}


void ofApp::drawSoundObjects()
{	
	for (int i = 0 ; i < soundBoxes.size() ; i++)
	{
		soundBoxes[i].setLineWidth(lineWidth);
		soundBoxes[i].draw(drawMode);
	}
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
	if (bUseDepthTest)
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

	//camera.disableMouseInput();
 //   camera.setDistance(cameraDist);
 //   camera.setGlobalPosition(current);
	//camera.lookAt(ofVec3f(0,0,0));

	camera.begin();
    
    if(bUseTexture == true) {
        ofEnableNormalizedTexCoords();
        meshTexture.bind();
    }

    ofSetColor(ofColor::white);
    //meshWarped.setMode(OF_PRIMITIVE_POINTS);
    //meshWarped.setMode(OF_PRIMITIVE_LINES);
	//meshWarped.draw();
	if (drawMode == 1)
		meshWarped.drawVertices();
	else if (drawMode == 2)
   		meshWarped.drawWireframe();
	else if (drawMode == 3)
   		meshWarped.drawFaces();

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

void ofApp::drawLine()
{
	ofSetColor(255,255,255);  
	ofNoFill();  

	int spacing = 50;   
	int amount = ofGetWidth() / spacing;
	int i = 0;
	float * audioData = new float[amount];
	fftFile.getFftPeakData(audioData, amount);

	post.begin();
		ofSetLineWidth(lineWidth);
		//for (int z = 0 ; z >= -5 ; z = z - 5)
		float z = ofNoise((2 + ofGetElapsedTimef()) * .1) * 150.0;
		{
			//ofPushMatrix();
			//ofTranslate(0,0,z);
			ofBeginShape();   
			for(int x=0; x<ofGetWidth(); x+= spacing) {   
				float audioValue = audioData[i] * audioMult;
				audioValue = MAX(0.1, audioValue);
				ofCurveVertex(x, ofGetHeight()/2 + (ofGetHeight()/2.0) * 0.3f * audioValue * sin(x*0.01f + ofGetFrameNum() * 0.02f), z);   
				i++;
			}   
			ofEndShape(false);   
			//ofPopMatrix();
		}
		
	post.end();
	delete [] audioData;
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
        bGuiVisible = !bGuiVisible;
    } else if(key == 'e' || key == 'E') {
        ofxObjLoader::save("mesh_export.obj", meshWarped);
    } else if(key == 's' ) {
        saveSettings(iPresetActual);
    } else if(key > '0' && key < '9')
	{
		iPresetActual = key - '0';
		loadSettings(iPresetActual);
	}	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	    if ( key == ' ' ) {
        m_bDrawDepth = !m_bDrawDepth;
    } else if ( key == 'l' ) {
        m_bDrawLight = !m_bDrawLight;
    } else if ( key == 'p' ) {
        m_bPaused = !m_bPaused;
    }
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