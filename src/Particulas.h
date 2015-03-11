
#include "ofMain.h"
#include "ofxGui.h"
#include "AVGSistPart.h"
#include "ColorUtil.h"
#include "ofxBeatDetector.h"

class Particulas
{

	public:
		
		void	setup				(float width, float height, ofxBeatDetector *beatDetector);
		void	update				(float average, float *soundData);
		void	draw				( );
		int		getAudioDataAmount	( );

		//ofxIntSlider	paramMaxLenght;
		ofxFloatSlider	paramMult;
		ofxIntSlider	paramLightDistance;
		ofxIntSlider	paramDrawMode;

		//ofxFloatSlider	paramDamp;

		AVGSistPart		sistPart;

	protected:

		void	updateMesh			( float average, float *soundData );
		void	setupLigths			( );
		void	drawAsociaciones	( );
		void	addAsociacion		( int *pos, float lineWidth );
		void	updatePosicion		( );
		int		addParticula		( ofVec3f pos, ofVec3f vel, float audioAverage, ofColor color );

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
		};

		vector <int> pVivas;
		vector<ASOCIACION> asociaciones;

		struct CIRCULO
		{
			ofPoint		centro;
			float		radio;
			ofColor		color;
			int			vida;
		};
		vector<CIRCULO> circulos;

		struct EMITTER
		{
			ofFloatColor color;
			//Current circle state
			ofPoint pos;				//Circle center
			ofPoint axeX, axyY, axyZ;	//Circle's coordinate system
			ofVec2f dir;
		};
		EMITTER emitter[4];

		ofxBeatDetector *beatDetector;
};