
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
		void	update				(float average);
		void	draw				( );
		int		getAudioDataAmount	( );

		ofxToggle		paramDrawParticles;
		ofxFloatSlider	paramMult;
		ofxIntSlider	paramLightDistance;
		ofxIntSlider	paramDrawMode;
		ofxFloatSlider	paramSpeedInc;
		ofxFloatSlider	paramColorNoiseMult;
		ofxFloatSlider	paramMoveNoiseMult;
		ofxFloatSlider	paramMoveBeatMult;

		float			beatHatValue;
		float			beatKickValue;
		float			beatSnareValue;
		float			beatLowValue;
		float			beatHighValue;
		float			beatMidValue;
		//ofxFloatSlider	paramDamp;

		AVGSistPart		sistPart;
		ofxBeatDetector *beatDetector;
		vector<Emitter> emitters;

	protected:
		//bool	isEmitterBeat		( Emitter *emitter );
		void	updateMesh			( float average);
		void	setupLigths			( );
		void	drawAsociaciones	( bool postPass );
		void	addAsociacion		( Emitter *emitter, int *pos, float lineWidth );
		void	updatePosicion		( );
		int		addParticula		( ofVec3f pos, ofVec3f vel, ofVec3f dirIni, float audioAverage, ofColor color );

		float			width;
		float			height;

		ofMesh			mesh;
		
		ofLight			light;

		int				audioDataAmount;		//Cuantos valores de audio necesita de input
		ColorUtil		colorUtil;

		vector <int>			pVivas;


		//struct CIRCULO
		//{
		//	ofVec3f		direccion;
		//	ofPoint		centro;
		//	float		radio;
		//	ofColor		color;
		//	int			vida;
		//};
		//vector<CIRCULO> circulos;


		ofxPostProcessing post;
		ofxPostProcessing post2;
		ofEasyCam		*camera;
};