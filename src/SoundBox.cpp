#include "SoundBox.h"

void SoundBox::setup( ofVec3f pos, ofVec3f vel, float size )
{
	
	this->pos = pos;
	this->vel = vel;
	this->size = size;
	
	lineWidth = 1.0f;

	meshSrc.clear();
	
	//ofBoxPrimitive box(size, size, size);
	//meshSrc.addVertices(box.getMesh().getVertices());
	//meshSrc = box.getMesh();
	
	generateMesh();

	audioDataAmount = meshSrc.getNumVertices();

}

void SoundBox::generateMesh()
{
	float t = (2 + ofGetElapsedTimef()) * .07;
	int w = 4 + ofNoise(t,0,0) * 5.0f;
	int h = 4 + ofNoise(0,t,0) * 5.0f;
	int z = 4 + ofNoise(0,0,t) * 5.0f;
	ofBoxPrimitive box(size, size, size,w,h,z);
	//meshSrc.addVertices(box.getMesh().getVertices());
	meshSrc = box.getMesh();
}

void SoundBox::update( float average, float *soundData, float multAmount )
{
	generateMesh();
	meshDst.clear();
    for(int i=0; i<meshSrc.getNumVertices(); i++) {

		float t = (2 + ofGetElapsedTimef()) ;

		float audioValue = soundData[i];
		ofVec3f & vertOriginal = meshSrc.getVertices()[i]; //* scale;
        //ofVec3f & vertWarped = vertsWarped[i];
        ofVec3f dir = vertOriginal;
		float mult = 10;
		dir.x = ofSignedNoise(vertOriginal.x + t,0,0);
		dir.y = ofSignedNoise(0,vertOriginal.y + t,0);
		dir.z = ofSignedNoise(0,0,vertOriginal.z + t);
		dir = dir * mult;
        //ofVec3f direction = vertOriginal.getNormalized();
        float audio = MAX(1.0,(audioValue * multAmount));
		ofVec3f vertWarped = vertOriginal + dir + vertOriginal.getNormalized() * audio * 100.0f; //* audio;
		meshDst.addVertex(vertWarped);
		
		float r = ofNoise(t*.1,0,0) * audioValue * vertOriginal.normalized().x * 2.0;
		float g = ofNoise(0,t*.1,0) * audioValue * vertOriginal.normalized().y * 2.0;
		float b = ofNoise(0,0,t*.1) * audioValue * vertOriginal.normalized().z * 2.0;
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
	
	ofSetLineWidth(lineWidth);

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

void SoundBox::setLineWidth( float lw )
{
	lineWidth = lw;
}
