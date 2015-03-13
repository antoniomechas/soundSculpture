#include "ofMain.h"
#include "ColorUtil.h"

class Emitter
{
	public:

		void			setup					( float width, float height, ofPoint pos, ofVec3f dir, ofFloatColor color, ColorUtil *colorUtil );
		void			update					( );
		void			setColorNoiseMult		( float noiseMult );
		void			setSpeedInc				( float speedInc );
		void			setMoveNoise			( float moveNoise );
		float			getMoveSeed				( );
		void			setMoveSeed				( float seed );

		ofPoint			pos;	
		ofVec3f			dir;
		ofFloatColor	color;
	
	protected:
		
		float			width;
		float			height;
		ofFloatColor	colorIni;
		float			seedMove;
		float			seedColor;
		ColorUtil		*colorUtil;
		float			colorNoiseMult;
		float			speedInc;
		float			moveNoise;
};