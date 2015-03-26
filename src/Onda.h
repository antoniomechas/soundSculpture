
#include "ofMain.h"
#include "ofxGui.h"
//#include "AVGSistPart.h"
#include "ColorUtil.h"
#include "ofxBeatDetector.h"
#include "ofxPostProcessing.h"

class Onda
{

	public:
		
		void	setup				(float width, float height, ofxBeatDetector *beatDetector, ofEasyCam *camera);
		void	update				(float average, float *audioData);
		void	draw				( );
		int		getAudioDataAmount	( );

		ofxFloatSlider	paramMult;

		float			beatHatValue;
		float			beatKickValue;
		float			beatSnareValue;
		float			beatLowValue;
		float			beatHighValue;
		float			beatMidValue;

		ofxBeatDetector *beatDetector;

	protected:

		void			generaOnda ( ofPolyline &pol, int intervalo, float *audioData, float maxHeight );
		void			generaOndaSin ( ofPolyline &pol, int divisiones, int indice, float *audioData, float maxHeight );

		float			width;
		float			height;

		ofMesh			mesh;
		ofPolyline		poly[4];

		int				audioDataAmount;		//Cuantos valores de audio necesita de input
		ColorUtil		colorUtil;

		ofxPostProcessing post;

		ofEasyCam		*camera;
};