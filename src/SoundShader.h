
#include "ofMain.h"
#include "ofxBeatDetector.h"

class SoundShader
{
	public:
		
		void			setup (float width, float height, ofxBeatDetector *beatDetector);
		void			update ( );
		void			draw ();

	protected:

		void			texturedQuad(float x, float y, float width, float height);

		float			width;
		float			height;
		ofxBeatDetector *beatDetector;

		ofShader		shader;

};