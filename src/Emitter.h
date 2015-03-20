#include "ofMain.h"
#include "ColorUtil.h"
#include "ofxBeatDetector.h"

class Emitter
{
	public:

		void			setup					( float width, float height, ofPoint pos, ofVec3f dir, ofFloatColor color, ColorUtil *colorUtil, ofxBeatDetector *beat );
		void			update					( );
		void			setColorNoiseMult		( float noiseMult );
		void			setSpeedInc				( float speedInc );
		void			setMoveNoise			( float moveNoise );
		float			getMoveSeed				( );
		void			setMoveSeed				( float seed );
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

		ofxBeatDetector *beatDetector;

};