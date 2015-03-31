#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableAntiAliasing();
    
    
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
	//box2d.registerGrabbing();
	box2d.createBounds();
	box2d.createGround();	

	//anchor.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 20);
	//anchor.setPhysics(3.0, 0.53, 0.1);
	ofxBox2dJoint a;
	
	// first we add just a few circles
	float n_segments = 20;
	float radius = 300;        // Current angle
	// The greater the number, the more springy
	float springiness = 1.0;
	for (int i=0; i<n_segments; i++) {
		
    
		// Delta angle to step by
		float deltaAngle = (2.f * PI) / n_segments;
    
		// Radius of the wheel
		float theta = deltaAngle*i;
        
		// Calcualte the x and y based on theta 
		float x = ofGetWidth() / 2. + radius*cosf(theta);
		float y = ofGetHeight() / 2. + radius*sinf(theta);

		ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		circle.get()->setPhysics(3.0, 0.53, 0.1);
		circle.get()->setup(box2d.getWorld(), x, y, 8);
		circles.push_back(circle);
	}
	rect = ofRectangle(ofGetWidth() / 2 - 50, ofGetHeight() / 2 - 100, 100, 200);
	for (int i = 0 ; i < 4 ; i++)
		mouseJoint[i].setWorld(box2d.getWorld());
	
	mouseJoint[0].addJoint(box2d.ground, circles[0].get()->body);
	mouseJoint[1].addJoint(box2d.ground, circles[n_segments/4 ].get()->body);
	mouseJoint[2].addJoint(box2d.ground, circles[n_segments/4 * 2].get()->body);
	mouseJoint[3].addJoint(box2d.ground, circles[n_segments/4 * 3].get()->body);

	// now connect each circle with a joint
	for (int i=0; i<circles.size(); i++) {
		
		ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
		
		//joint.get()->setup(box2d.getWorld(), anchor.body, circles[i].get()->body);
		//joint.get()->setFrequency(2);
		//joint.get()->setLength(radius);
		//joints.push_back(joint);

		//joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
		b2Vec2 v1, v2;
		if(i == 0)
		{
			joint.get()->setup(box2d.getWorld(), circles[0].get()->body, circles[circles.size()-1].get()->body);
			v1 = circles[0].get()->body->GetPosition();
			v2 = circles[circles.size()-1].get()->body->GetPosition();
		}
		else
		{
			joint.get()->setup(box2d.getWorld(), circles[i-1].get()->body, circles[i].get()->body);
			v1 = circles[i-1].get()->body->GetPosition();
			v2 = circles[i].get()->body->GetPosition();
		}
		ofVec2f vv1 (v1.x, v1.y);
		ofVec2f vv2 (v2.x, v2.y);
		float dist = vv1.distance(vv2);

		joint.get()->setFrequency(springiness);
		joint.get()->setLength(dist);
		joints.push_back(joint);

	}
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();	
}


//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetHexColor(0xf2ab01);
	ofNoFill();
	ofRect(rect);
	//anchor.draw();
	
	//for(int i=0; i<circles.size(); i++) {
	//	ofFill();
	//	ofSetHexColor(0x01b1f2);
	//	circles[i].get()->draw();
	//}
	
	//for(int i=0; i<joints.size(); i++) {
	//	ofSetHexColor(0x444342);
	//	joints[i].get()->draw();
	//}
	ofPolyline poly;
	//poly.addVertex(ofPoint(joints[0].get()->joint->GetAnchorA().x, joints[0].get()->joint->GetAnchorA().y) * OFX_BOX2D_SCALE);
	//for(int i=0; i<joints.size(); i++) {
	//	poly.curveTo(ofPoint(joints[i].get()->joint->GetAnchorB().x, joints[0].get()->joint->GetAnchorB().y) * OFX_BOX2D_SCALE);
	//}
	poly.addVertex(circles[0].get()->getPosition());
	poly.curveTo(circles[0].get()->getPosition());
	ofCircle(circles[0].get()->getPosition(),3);
	for(int i=1; i<circles.size(); i++) {
		poly.curveTo(circles[i].get()->getPosition());
		ofCircle(circles[i].get()->getPosition(),3);
	}
	poly.curveTo(circles[0].get()->getPosition());
	poly.curveTo(circles[0].get()->getPosition());
	//poly.close();
	ofSetColor(255,0,0);
	poly.draw();
	string info = "";
	info += "Press [n] to add a new joint\n";
	info += "click and pull the chain around\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	if(key == 'n') {
		
		// add a new circle
		ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		circle.get()->setPhysics(3.0, 0.53, 0.1);
		circle.get()->setup(box2d.getWorld(), circles.back().get()->getPosition().x+ofRandom(-30, 30), circles.back().get()->getPosition().y-30, 8);
		circles.push_back(circle);
	
		// get this cirlce and the prev cirlce
		int a = (int)circles.size()-2;
		int b = (int)circles.size()-1; 

		// now connect the new circle with a joint
		ofPtr<ofxBox2dJoint> joint = ofPtr<ofxBox2dJoint>(new ofxBox2dJoint);
		joint.get()->setup(box2d.getWorld(), circles[a].get()->body, circles[b].get()->body);
		joint.get()->setLength(25);
		joints.push_back(joint);
	}
	
	if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

	//mouseJoint.
	mouseJoint[0].setTarget(rect.getTopLeft()/ OFX_BOX2D_SCALE);
	mouseJoint[1].setTarget(rect.getTopRight()/ OFX_BOX2D_SCALE);
	mouseJoint[2].setTarget(rect.getBottomRight()/ OFX_BOX2D_SCALE);
	mouseJoint[3].setTarget(ofVec2f(x / OFX_BOX2D_SCALE, y / OFX_BOX2D_SCALE));
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) { 
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

