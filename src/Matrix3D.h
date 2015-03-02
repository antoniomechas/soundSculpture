
#include "ofMain.h"

class Matrix3D
{

	public:
		
		void	setup	(float width, float height, int cols, int rows);
		void	update	();
		void	draw	();

	protected:

		struct MATRIX
		{
			ofVec2f pos;
			float	width;
			float	height;
			float	length;
			ofColor color;
		};

		vector<MATRIX> matrix;

		float	width;
		float	height;
		int		cols;
		int		rows;
		float	cellWidth;
		float	cellHeight;
		ofMesh	mesh;

};