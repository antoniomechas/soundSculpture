#pragma once  
//based on Todd Vanderlin's ofxBox2dJoint class  

#include "ofxBox2d.h"

class ofxBox2dMouseJoint {  

public:  

	b2World * world;  
	//b2Joint * joint;  
	bool alive;  

	b2MouseJoint *mj;

	ofxBox2dMouseJoint() {  
		world = NULL;  
		alive = false;  
	}  

	void setWorld(b2World * w) {  
		if(w == NULL) {  
			ofLog(OF_LOG_NOTICE, "- box2d world needed -");	  
			return;  
		}  
		world = w;  
		alive = true;  
	}  

	void destroyJoint() {  
		world->DestroyJoint(mj);  
		mj = NULL;  
	}  

	void addJoint(b2Body * a, b2Body * b) {  

		if(world == NULL) {  
			ofLog(OF_LOG_NOTICE, "- no joint added - box2d world needed -");	  
			return;  
		}  
		
		b2MouseJointDef mj_def;
		
		mj_def.bodyA = a;
		mj_def.bodyB = b;
		mj_def.collideConnected = true;
		mj_def.target = b->GetPosition();
		mj_def.maxForce = 10;

		mj = (b2MouseJoint*)world->CreateJoint(&mj_def);
	}  

	void setTarget(ofVec2f t)
	{
		mj->SetTarget(b2Vec2(t.x, t.y));
	}

};  
