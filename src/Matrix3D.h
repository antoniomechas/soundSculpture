
#include "ofMain.h"
#include "ofxGui.h"

#define MPOS(x,y) (((y) * cols) + x)

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
		ofxFloatSlider	paramDamp;
		ofxFloatSlider	paramWidthMult;

	protected:

		void	setupLigths();
		void	circle(int centroX, int centroY, int radio, float value);
		void	lineHorizontal(int y, float value);
		void	setMatrixValue (int x, int y, float value);

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