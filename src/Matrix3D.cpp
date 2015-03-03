#include "Matrix3D.h"

void Matrix3D::setup(float width, float height, int cols, int rows)
{
	
	this->width = width;
	this->height = height;
	this->rows = rows;
	this->cols = cols;

	cellWidth = width /  cols;
	cellHeight = height / rows;
	ofColor cl = ofColor::fromHsb(ofRandom(128,255), 255, 255);
	MATRIX m;
	for (int r = 0 ; r < rows ; r++)
		for (int c = 0 ; c < cols ; c++)
		{
			m.height = cellHeight;
			m.width = cellWidth;
			m.pos.x = (-width / 2.0) + (c * cellWidth) + cellWidth / 2.0;
			m.pos.y = (-height / 2.0) + (r * cellHeight) + cellHeight / 2.0;
			m.length = 30;
			m.color = cl;
			matrix.push_back(m);
		}
	
	setupLigths();

	//audioDataAmount = cols * rows;
	audioDataAmount = MAX(cols , rows);

}

void Matrix3D::draw()
{
	ofEnableDepthTest();

	ofEnableLighting();
	ofSetSmoothLighting(true);
	light.setPosition(300,-300,paramLightDistance);
	light.enable();
	for (int i = 0; i < matrix.size() ; i++)
	{
		ofPushMatrix();
		ofSetColor(matrix[i].color);
		ofTranslate(matrix[i].pos.x, matrix[i].pos.y, matrix[i].length/2 );
		ofSetLineWidth(1.0);
		ofFill();


		ofVec3f start = matrix[i].pos;
		start.z = 0;
		ofVec3f end = start;
		end.z = matrix[i].length;
		//ofSetLineWidth(20);
		//ofDrawArrow(start,end,cellWidth/2);
		//ofDrawSphere(end,cellWidth/2);
		
		//ofRotateX(-90);
		//ofDrawCone(cellWidth / 2, matrix[i].length);

		ofRotateX(90);
		ofDrawCylinder(cellWidth, matrix[i].length);

		//ofDrawBox(matrix[i].width-1, matrix[i].height-1, matrix[i].length);
		ofNoFill();
		ofSetLineWidth(1.0);
		ofSetColor(0,0,0);
		//ofDrawBox(matrix[i].width, matrix[i].height, matrix[i].length);
		ofPopMatrix();
	}
	light.disable();
	
	ofDisableLighting();

	//ofRect(-width/2, -height/2, width, height);


}

void Matrix3D::update(float average, float *soundData)
{

	//mesh.clear();
	int p = 0;
	//int step = 14;
	//for (int k = 0 ; k < step ; k++)
	//{
	//	for (int i = k; i < matrix.size() ; i = i + step)
	//	{
	//		//matrix[i].length = ofNoise((float)i*200.0f, ofGetElapsedTimef() * 0.1f) * 20;
	//		matrix[p++].length = soundData[i] * paramMaxLenght * paramMult;
	//	}
	//}

	int centroX = cols / 2;
	int centroY = rows / 2;
	
	for (int i = 1 ; i < (cols / 2) - 1 && i < audioDataAmount ; i++)
		circle(centroX, centroY, i, soundData[i]);

	//for (int i = 0 ; i < rows ; i++)
	//	lineHorizontal( i, soundData[i]);
	
	//for (int i = 0 ; i < matrix.size() ; i++)
	//	matrix[i].length = 0;

	//for (int i = 0 ; i < matrix.size() ; i++)
	//{
	//	if (matrix[i].length < 1)
	//		matrix[i].length = 0;
	//	else
	//		matrix[i].length *= paramDamp;
	//}

	//circle(centroX, centroY, ofNoise(ofGetElapsedTimef()) * (cols/2), average);


	p = 0;
	for (int co = 0; co < cols ; co++)
		for (int ro = 0; ro < rows ; ro++)
		{
			float t = (2 + ofGetElapsedTimef()) ;
			float col = ofMap(co,0,cols-1,0,.5);
			float row = ofMap(ro,0,rows-1,0,.5);
			//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
			float r = ofNoise(row,col, t*.1);
			float g = ofNoise(row,col, 100.0 + t*.1);
			float b = ofNoise(row,col, 200.0 + t*.1);
			matrix[p++].color = ofFloatColor(r,g,b);
		}

}

void Matrix3D::setupLigths() {
    
    light.setAmbientColor( ofFloatColor( 0.0f, 0.0f, 0.0f, 1.0f ) );
    light.setDiffuseColor( ofFloatColor( 0.9f, 0.9f, 0.9f, 1.0f ) );
    light.setSpecularColor( ofFloatColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    light.setPosition( 0,0, 200.0f);
	light.lookAt(ofVec3f(0,0,0));
    
    ofSetGlobalAmbientColor( ofFloatColor( 0.05f, 0.05f, 0.05f ) );
}

int Matrix3D::getAudioDataAmount ()
{
	return audioDataAmount;
}


void Matrix3D::circle(int centroX, int centroY, int radius, float value)
{

    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
	
	setMatrixValue(centroX, centroY + radius, value * paramMaxLenght * paramMult);
	setMatrixValue(centroX, centroY - radius, value * paramMaxLenght * paramMult);
	setMatrixValue(centroX + radius, centroY, value * paramMaxLenght * paramMult);
	setMatrixValue(centroX - radius, centroY, value * paramMaxLenght * paramMult);

	while(x < y) 
    {
        if(f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;    
		
		setMatrixValue(centroX + x, centroY + y, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX - x, centroY + y, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX + x, centroY - y, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX - x, centroY - y, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX + y, centroY + x, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX - y, centroY + x, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX + y, centroY - x, value * paramMaxLenght * paramMult);
		setMatrixValue(centroX - y, centroY - x, value * paramMaxLenght * paramMult);

    }
}

void Matrix3D::lineHorizontal(int y, float value)
{
	for (int x = 0 ; x < cols ; x++)
		setMatrixValue(x, y, value * paramMaxLenght * paramMult);
}


void Matrix3D::setMatrixValue (int x, int y, float value)
{
	if (x < cols && x >= 0 && y >= 0 && y < rows)
		matrix[MPOS(x,y)].length = value;
}