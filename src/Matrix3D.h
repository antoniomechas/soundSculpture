
#include "ofMain.h"
#include "ofxGui.h"

class Matrix3D
{

	public:
		
		void	setup				(float width, float height, int cols, int rows);
		void	update				(float average, float *soundData);
		void	draw				( );
		int		getAudioDataAmount	( );

		ofxIntSlider	paramMaxLenght;
		ofxFloatSlider	paramMult;
		ofxIntSlider	paramLightDistance;

	protected:

		void	setupLigths();

		struct MATRIX
		{
			ofVec2f pos;
			float	width;
			float	height;
			float	length;
			ofColor color;
		};

		vector<MATRIX>	matrix;

		float			width;
		float			height;
		int				cols;
		int				rows;
		float			cellWidth;
		float			cellHeight;
		ofMesh			mesh;
		
		ofLight			light;

		int				audioDataAmount;		//Cuantos valores de audio necesita de input

};