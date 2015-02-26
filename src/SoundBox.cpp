#include "SoundBox.h"

void SoundBox::setup( ofVec3f pos, ofVec3f vel, float size )
{
	
	this->pos = pos;
	this->vel = vel;
	this->size = size;

	meshSrc.clear();
	
	ofBoxPrimitive box(size, size, size);
	//meshSrc.addVertices(box.getMesh().getVertices());
	meshSrc = box.getMesh();
	
	audioDataAmount = meshSrc.getNumVertices();

}

void SoundBox::update( float average, float *soundData, float multAmount )
{
	meshDst.clear();
    for(int i=0; i<meshSrc.getNumVertices(); i++) {

		float t = (2 + ofGetElapsedTimef()) * .1;

		float audioValue = soundData[i];
		ofVec3f & vertOriginal = meshSrc.getVertices()[i]; //* scale;
        //ofVec3f & vertWarped = vertsWarped[i];
        ofVec3f dir = vertOriginal;
		float mult = 10;
		dir.x = dir.x + ofNoise(vertOriginal.x + t,0,0);
		dir.y = dir.y + ofNoise(0,vertOriginal.y + t,0);
		dir.z = dir.z + ofNoise(0,0,vertOriginal.z + t);
		ofVec3f direction = dir.getNormalized() * mult;
        //ofVec3f direction = vertOriginal.getNormalized();
        ofVec3f vertWarped = vertOriginal + direction * (audioValue * multAmount);
		meshDst.addVertex(vertWarped);
		
		float r = ofNoise(t,0,0) * audioValue * vertOriginal.normalized().x * 2.0;
		float g = ofNoise(0,t,0) * audioValue * vertOriginal.normalized().y * 2.0;
		float b = ofNoise(0,0,t) * audioValue * vertOriginal.normalized().z * 2.0;
		r = MAX(0.1, r);
		g = MAX(0.1, g);
		b = MAX(0.1, b);
		meshDst.addColor(ofFloatColor(r, g, b));
		meshDst.addIndices(meshSrc.getIndices());
    }
}

void SoundBox::draw( int drawMode )
{
	
	ofEnableDepthTest();

	ofSetColor(255,255,255);
	switch (drawMode)
	{
		case 1:
			meshDst.drawVertices();
			break;
		case 2:
			//meshDst.setMode(OF_PRIMITIVE_TRIANGLES);
			meshDst.drawWireframe();
			break;
		case 3:
			//meshDst.setMode(OF_PRIMITIVE_TRIANGLES);
			meshDst.drawFaces();
			break;
	}
}
