#include "SoundObject.h"

void SoundObject::setup( ofVec3f pos, ofVec3f vel, float size )
{
	
	this->pos = pos;
	this->vel = vel;
	this->size = size;

	audioDataAmount = 0;

}

void SoundObject::update ( float average, float *soundData )
{}

void SoundObject::draw ( int drawMode )
{}

int SoundObject::getAudioDataAmount ()
{
	return audioDataAmount;
}