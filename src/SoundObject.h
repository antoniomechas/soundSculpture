
#pragma once

#include "ofMain.h"

class SoundObject
{

	public:
		
		virtual void	setup				( ofVec3f pos, ofVec3f vel, float size );
		virtual void	update				( float average, float *soundData );
		virtual void	draw				( int drawMode );
		int				getAudioDataAmount	( );
	
	protected:
		
		ofVec3f		pos;
		ofVec3f		vel;
		float		size;
		int			audioDataAmount;		//Cuantos valores de audio necesita de input
};