#include "ofMain.h"
#include "ColorUtil.h"
#include "ofxBeatDetector.h"

class Emitter
{
	public:

		// Draw Mode
		enum DrawMode{
			EMITTER_DRAW_TRIANGLES = 0,
			EMITTER_DRAW_CIRCLES = 1,
			EMITTER_DRAW_ELLIPSES = 2,
			EMITTER_DRAW_RECTANGLES = 3
		};

		void			setup					( float width, float height, ofPoint pos, ofVec3f dir, ofFloatColor color, ColorUtil *colorUtil, ofxBeatDetector *beat );
		void			update					( );
		void			setColorNoiseMult		( float noiseMult );
		void			setSpeedInc				( float speedInc );
		void			setMoveNoise			( float moveNoise );
		float			getMoveSeed				( );
		void			setMoveSeed				( float seed );
		void			setDrawMode				( DrawMode drawMode);
		DrawMode		getDrawMode				( );

		bool			isBeat					( );
		void			setBeatLowValue			( float value );
		void			setBeatHighValue		( float value );
		void			setBeatMidValue			( float value );
		void			setBeatSnareValue		( float value );
		void			setBeatHatValue			( float value );
		void			setBeatKickValue		( float value );

		ofPoint			pos;	
		ofVec3f			dir;
		ofFloatColor	color;

		DrawMode		drawMode;
		
		// Beat reaction 
		enum BeatReaction{
			BEAT_REACTION_LOW = 0,
			BEAT_REACTION_MID = 1,
			BEAT_REACTION_HIGH = 2,
			BEAT_REACTION_KICK = 3,
			BEAT_REACTION_SNARE = 4,
			BEAT_REACTION_HAT = 5
		};

		BeatReaction	beatReaction;
		ofxBeatDetector *beatDetector;


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
		float			beatLowValue;
		float			beatMidValue;
		float			beatHighValue;
		float			beatSnareValue;
		float			beatKickValue;
		float			beatHatValue;
		//ofPoint			posAnt;	


};