
#include "ofMain.h"
#include "ofxGui.h"
#include "AVGSistPart.h"
#include "ColorUtil.h"

class Particulas
{

	public:
		
		void	setup				(float width, float height);
		void	update				(float average, float *soundData);
		void	draw				( );
		int		getAudioDataAmount	( );

		//ofxIntSlider	paramMaxLenght;
		ofxFloatSlider	paramMult;
		ofxIntSlider	paramLightDistance;
		//ofxFloatSlider	paramDamp;

		AVGSistPart		sistPart;

	protected:

		void	updateMesh			(float average, float *soundData);
		void	setupLigths();
		void	drawAsociaciones();

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
		};

		vector <int> pVivas;
		vector<ASOCIACION> asociaciones;
};