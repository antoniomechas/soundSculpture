#include "Particulas.h"

void Particulas::setup(float width, float height)
{
	
	this->width = width;
	this->height = height;
	
	setupLigths();

	//audioDataAmount = cols * rows;
	audioDataAmount = 0;
	
	sistPart.setup();
	sistPart.CargaTextura("texCirculoStar.bmp");

}

void Particulas::draw()
{
	ofEnableDepthTest();

	ofEnableLighting();
	ofSetSmoothLighting(true);
	light.setPosition(300,-300,paramLightDistance);
	light.enable();

	//draw

	light.disable();
	
	ofDisableLighting();

}

void Particulas::update(float average, float *soundData)
{

}

void Particulas::setupLigths() {
    
    light.setAmbientColor( ofFloatColor( 0.0f, 0.0f, 0.0f, 1.0f ) );
    light.setDiffuseColor( ofFloatColor( 0.9f, 0.9f, 0.9f, 1.0f ) );
    light.setSpecularColor( ofFloatColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    light.setPosition( 0,0, 200.0f);
	light.lookAt(ofVec3f(0,0,0));
    
    ofSetGlobalAmbientColor( ofFloatColor( 0.05f, 0.05f, 0.05f ) );
}

int Particulas::getAudioDataAmount ()
{
	return audioDataAmount;
}


