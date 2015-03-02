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
	
	update();

}

void Matrix3D::draw()
{
	ofEnableDepthTest();
	for (int i = 0; i < matrix.size() ; i++)
	{
		ofPushMatrix();
		ofSetColor(matrix[i].color);
		ofTranslate(matrix[i].pos.x, matrix[i].pos.y, matrix[i].length / 2.0);
		//ofTranslate(matrix[i].pos.x - cellWidth / 2.0, matrix[i].pos.y - cellHeight / 2.0);
		//ofTranslate(matrix[i].pos.x - cellWidth / 2.0, matrix[i].pos.y - cellHeight / 2.0, matrix[i].length / 2);
		ofSetLineWidth(1.0);
		ofFill();
		ofDrawBox(matrix[i].width-2, matrix[i].height-2, matrix[i].length);
		ofNoFill();
		ofSetLineWidth(2.0);
		ofSetColor(0,0,0);
		ofDrawBox(matrix[i].width-2, matrix[i].height-2, matrix[i].length);
		ofPopMatrix();
	}

	ofRect(-width/2, -height/2, width, height);


}

void Matrix3D::update()
{

	//mesh.clear();
	for (int i = 0; i < matrix.size() ; i++)
	{
		matrix[i].length = ofNoise(i + ofGetElapsedTimef() * 1.0) * 300;
	}

}