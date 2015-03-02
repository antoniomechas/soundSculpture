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
		ofTranslate(matrix[i].pos.x, matrix[i].pos.y, matrix[i].length );
		//ofTranslate(matrix[i].pos.x - cellWidth / 2.0, matrix[i].pos.y - cellHeight / 2.0);
		//ofTranslate(matrix[i].pos.x - cellWidth / 2.0, matrix[i].pos.y - cellHeight / 2.0, matrix[i].length / 2);
		ofSetLineWidth(1.0);
		ofFill();
		ofDrawBox(matrix[i].width, matrix[i].height, matrix[i].length);
		ofNoFill();
		ofSetLineWidth(1.0);
		ofSetColor(0,0,0);
		ofDrawBox(matrix[i].width, matrix[i].height, matrix[i].length);
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

	ofPoint centro( floor(cols / 2), floor(rows / 2));
	ofPoint pos;
	for (int grados = 0 ; grados < 360 ; grados ++)
	{
		float rad = 2*PI*grados / 360.0;
		pos.x = floor(centro.x + 5 * cos(rad));
		pos.y = floor(centro.y + 5 * sin(rad));
		matrix[(int)pos.y * cols + (int)pos.x].length = average * paramMaxLenght * paramMult;
	}




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