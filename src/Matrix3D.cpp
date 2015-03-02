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
	for (int c = 0 ; c < cols ; c++)
		for (int r = 0 ; r < rows ; r++)
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

	audioDataAmount = cols * rows;

}

void Matrix3D::draw()
{
	ofEnableDepthTest();

	ofEnableLighting();
	light.enable();
	for (int i = 0; i < matrix.size() ; i++)
	{
		ofPushMatrix();
		ofSetColor(matrix[i].color);
		ofTranslate(matrix[i].pos.x, matrix[i].pos.y, matrix[i].length / 2.0);
		//ofTranslate(matrix[i].pos.x - cellWidth / 2.0, matrix[i].pos.y - cellHeight / 2.0);
		//ofTranslate(matrix[i].pos.x - cellWidth / 2.0, matrix[i].pos.y - cellHeight / 2.0, matrix[i].length / 2);
		ofSetLineWidth(1.0);
		ofFill();
		ofDrawBox(matrix[i].width-1, matrix[i].height-1, matrix[i].length);
		ofNoFill();
		ofSetLineWidth(2.0);
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
	for (int i = 0; i < matrix.size() ; i++)
	{
		//matrix[i].length = ofNoise((float)i*200.0f, ofGetElapsedTimef() * 0.1f) * 20;
		matrix[i].length = soundData[i] * paramMaxLenght * paramMult;
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