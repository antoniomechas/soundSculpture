
#include "ofMain.h"
#include "ofxGui.h"
#include "AVGSistPart.h"
#include "ColorUtil.h"
#include "ofxBeatDetector.h"
#include "Emitter.h"
#include "ofxPostProcessing.h"

class Particulas
{

	public:
		
		void	setup				(float width, float height, ofxBeatDetector *beatDetector, ofEasyCam *camera);
		void	update				(float average, float *soundData);
		void	draw				( );
		int		getAudioDataAmount	( );

		//ofxIntSlider	paramMaxLenght;
		ofxFloatSlider	paramMult;
		ofxIntSlider	paramLightDistance;
		ofxIntSlider	paramDrawMode;
		ofxFloatSlider	paramSpeedInc;
		ofxFloatSlider	paramColorNoiseMult;
		ofxFloatSlider	paramMoveNoiseMult;

		float			beatHatValue;
		float			beatKickValue;
		float			beatSnareValue;
		float			beatLowValue;
		float			beatHighValue;
		float			beatMidValue;
		//ofxFloatSlider	paramDamp;

		AVGSistPart		sistPart;

	protected:

		void	updateMesh			( float average, float *soundData );
		void	setupLigths			( );
		void	drawAsociaciones	( bool postPass );
		void	addAsociacion		( Emitter &emitter, int *pos, float lineWidth );
		void	updatePosicion		( );
		int		addParticula		( ofVec3f pos, ofVec3f vel, ofVec3f dirIni, float audioAverage, ofColor color );

		float			width;
		float			height;

		ofMesh			mesh;
		
		ofLight			light;

		int				audioDataAmount;		//Cuantos valores de audio necesita de input
		ColorUtil		colorUtil;

		struct ASOCIACION
		{
			int		nodo1;
			int		nodo2;
			int		nodo3;
			int		vida;
			ofColor	color1;
			ofColor	color2;
			ofColor	color3;
			float	lineWidth;
			int		bloomLife;
		};

		vector <int> pVivas;
		vector<ASOCIACION> asociaciones;

		struct CIRCULO
		{
			ofVec3f		direccion;
			ofPoint		centro;
			float		radio;
			ofColor		color;
			int			vida;
		};
		vector<CIRCULO> circulos;

		vector<Emitter> emitters;

		ofxBeatDetector *beatDetector;
		ofxPostProcessing post;
		ofxPostProcessing post2;
		ofEasyCam		*camera;
};