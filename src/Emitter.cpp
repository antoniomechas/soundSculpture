#include "Emitter.h"

void Emitter::setup(float width, float height, ofPoint pos, ofVec3f dir, ofFloatColor color, ColorUtil *colorUtil, ofxBeatDetector *beat)
{
	this->height = height;
	this->width = width;
	this->pos = pos;
	this->dir = dir;
	this->colorIni = color;
	this->colorUtil = colorUtil;
	this->beatDetector = beat;

	//posAnt = pos;
	colorNoiseMult = 1.0f;
	speedInc = 10.0f;
	moveNoise = 1.0f;
	seedColor = ofRandom(100,5000);
	seedMove = ofRandom(100,5000);

	drawMode = EMITTER_DRAW_TRIANGLES;

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
	{
		pos.x -= dir.x * speedInc;
		pos.x *= -1.0;

	}

	if (pos.y < -height/2 || pos.y > height/2)
	{
		pos.y -= dir.y * speedInc;
		pos.y *= -1.0;
	}

	//posAnt = pos;

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

void Emitter::setDrawMode( DrawMode drawMode)
{
	this->drawMode = drawMode;
}

Emitter::DrawMode Emitter::getDrawMode( )
{
	return drawMode;
}

bool Emitter::isBeat()
{
	//cout << "BeatReaction: " << (int)beatReaction << endl;

	switch (beatReaction)
	{
		case BEAT_REACTION_HAT:
			beatDetector->setBeatValue(beatHatValue);
			//cout << "Hatvalue: " << beatHatValue << endl;
			if (beatDetector->isHat())
				return true;
			break;

		case BEAT_REACTION_KICK:
			beatDetector->setBeatValue(beatKickValue);
			//cout << "Kickvalue: " << beatHatValue << endl;
			if (beatDetector->isKick())
				return true;
			break;

		case BEAT_REACTION_SNARE:
			beatDetector->setBeatValue(beatSnareValue);
			//cout << "Snarevalue: " << beatHatValue << endl;
			if (beatDetector->isSnare())
				return true;
			break;

		case BEAT_REACTION_LOW:
			beatDetector->setBeatValue(beatLowValue);
			if (beatDetector->isLow())
				return true;
			break;

		case BEAT_REACTION_MID:
			beatDetector->setBeatValue(beatMidValue);
			if (beatDetector->isMid())
				return true;
			break;

		case BEAT_REACTION_HIGH:
			beatDetector->setBeatValue(beatHighValue);
			if (beatDetector->isHigh())
				return true;
			break;
	}

	return false;
}

void Emitter::setBeatLowValue ( float value )
{
	beatLowValue = value;
}

void Emitter::setBeatMidValue ( float value )
{
	beatMidValue = value;
}

void Emitter::setBeatHighValue ( float value )
{
	beatHighValue = value;
}

void Emitter::setBeatSnareValue ( float value )
{
	beatSnareValue = value;
}

void Emitter::setBeatKickValue ( float value )
{
	beatKickValue = value;
}

void Emitter::setBeatHatValue ( float value )
{
	beatHatValue = value;
}