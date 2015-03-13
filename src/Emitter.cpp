#include "Emitter.h"

void Emitter::setup(float width, float height, ofPoint pos, ofVec3f dir, ofFloatColor color, ColorUtil *colorUtil)
{
	this->height = height;
	this->width = width;
	this->pos = pos;
	this->dir = dir;
	this->colorIni = color;
	this->colorUtil = colorUtil;
	
	colorNoiseMult = 1.0f;
	speedInc = 10.0f;
	moveNoise = 1.0f;
	seedColor = ofRandom(100,5000);
	seedMove = ofRandom(100,5000);
}

void Emitter::update()
{

	color = colorUtil->getNoiseAround(colorIni, 255, seedColor + ofGetElapsedTimef() * 0.1f * colorNoiseMult);

	float time = ofGetElapsedTimef();	//Time

	dir.x = ofSignedNoise(time * 0.1 * moveNoise, seedMove);
	dir.y = ofSignedNoise(seedMove,time * 0.1 * moveNoise);

	pos += dir * speedInc;

	if (pos.z < 100 || pos.z > 100)
		pos.z *= -1.0;

	if (pos.x < -width/2 || pos.x > width/2)
		pos.x *= -1.0;

	if (pos.y < -height/2 || pos.y > height/2)
		pos.y *= -1.0;

}

void Emitter::setColorNoiseMult( float noiseMult )
{
	this->colorNoiseMult = noiseMult;
}

void Emitter::setSpeedInc( float speedInc )
{
	this->speedInc = speedInc;
}

void Emitter::setMoveNoise( float moveNoise )
{
	this->moveNoise = moveNoise;
}

void Emitter::setMoveSeed( float seed )
{
	this->seedMove = seed;
}

float Emitter::getMoveSeed( )
{
	return(seedMove);
}