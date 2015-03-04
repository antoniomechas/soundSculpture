
#include "ofMain.h"
#include "ofxGui.h"
#include "AVGSistPart.h"

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

	protected:

		void	setupLigths();

		float			width;
		float			height;

		ofMesh			mesh;
		
		ofLight			light;

		int				audioDataAmount;		//Cuantos valores de audio necesita de input
		
		AVGSistPart		sistPart;

};