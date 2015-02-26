#include "SoundObject.h"

class SoundBox : public SoundObject
{
	public:
		void	setup	( ofVec3f pos, ofVec3f vel, float size );
		void	update	( float average, float *soundData, float multAmount );
		void	draw	( int drawMode );
	
	private:
		ofMesh	meshSrc;
		ofMesh  meshDst;
};