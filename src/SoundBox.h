#include "SoundObject.h"

class SoundBox : public SoundObject
{
	public:
		void	setup			( ofVec3f pos, ofVec3f vel, float size );
		void	update			( float average, float *soundData, float multAmount );
		void	draw			( int drawMode );
		void	setLineWidth	( float lw );
	private:
		
		void	generateMesh();

		ofMesh	meshSrc;
		ofMesh  meshDst;
		float	lineWidth;

};