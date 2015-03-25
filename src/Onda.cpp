#include "Onda.h"

void Onda::setup(float width, float height, ofxBeatDetector *beat, ofEasyCam *camera)
{
	
	this->width = width;
	this->height = height;
	this->beatDetector = beat;
	this->camera = camera;

	audioDataAmount = 255;
	
	colorUtil.setup();

	post.init(width, height);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);

	for (int i = 0 ; i < audioDataAmount ; i++)
	{
		mesh.addVertex(ofVec3f(ofMap(i,0,audioDataAmount,0,width), height / 2.0,0));
	}

}

void Onda::draw()
{
	mesh.setMode(OF_PRIMITIVE_LINE_STRIP);

	ofBackground(0,0,0);
	ofSetColor(255,255,255);
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	post.begin();
		//camera->begin();
		ofSetLineWidth(2.0);	
		poly[0].draw();
		ofSetColor(255,0,0);
		poly[1].draw();
		ofSetColor(0,255,0);
		poly[2].draw();
		//mesh.draw();
			//drawAsociaciones(true);
		//camera->end();
	post.end();

}

void Onda::update(float average, float *audioData)
{

	//int a = MAX(1,(int)(average * paramMult));
	if (average > 0.3)
		post[0]->setEnabled(true);
	if (average > 0.8)
		post[1]->setEnabled(true);
	
	post[2]->setEnabled(false);

	float   t = ofGetElapsedTimef() * 1.2;
	float maxH = 300;
	for (int i = 0 ; i < audioDataAmount ; i++)
	{
	    float mult = 1.0;
		//if (i % 2)
		//	mult *= -1.0;
	    //float   y = ofSignedNoise(t) * 200 + (sin(t)* 100);
		mesh.getVertices()[i].y = (height / 2.0) + (maxH / 2.) - (audioData[i] * 300.0f) * mult;
    
     //   float newHeight = ofGetHeight()/2 + y;
     //   int n = (int)groundLine.size();
     //  
     //   groundTimer = ofGetElapsedTimef();
        
    }
		//float newHeight = average * 200.0f;
  //      for(int i = mesh.getNumVertices()-1 ; i>=1 ; i--) {
  //          mesh.getVertices()[i].y = mesh.getVertices()[i-1].y;
  //      }
  //      mesh.getVertices()[0].y = newHeight;
	generaOnda(poly[0], 4, audioData, 300);
	generaOnda(poly[1], 8, audioData, 300);
	generaOnda(poly[2], 16, audioData, 300);

}

int Onda::getAudioDataAmount ()
{
	return audioDataAmount;
}

//
// Genera una onda a partir del audio
//
void Onda::generaOnda ( ofPolyline &pol, int intervalo, float *audioData, float maxHeight )
{

	pol.clear();
	pol.addVertex(0, height/2.);
	float mult = 1.0;
	for (int i = 0 ; i < audioDataAmount / intervalo ; i++)
	{
		mult *= -1.;
		float x = ofMap(i * intervalo, 0, audioDataAmount, 0, width);
		float audioV = 0;
		for (int k = 0 ; k < intervalo ; k++)
			audioV += (audioData[i*intervalo] + k) / (float)intervalo;

		audioV = audioData[i * 4];
		//float audioV = beatDetector->getSmoothedFFT()[i];
		pol.curveTo(x, (height / 2.0) - (maxHeight / 2.) + (audioV * maxHeight) * mult);
    }
}