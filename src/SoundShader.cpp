
#include "SoundShader.h"

void SoundShader::setup(float width, float height, ofxBeatDetector *beatDetector)
{

	this->width = width;
	this->height = height;
	this->beatDetector = beatDetector;

	shader.load("shaders/GalacticDance");

}

void SoundShader::draw()
{
	ofSetColor(255,255,255);
	shader.begin();
		shader.setUniform2f("iResolution", width, height);
		shader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
		texturedQuad(0, 0, width, height);
	shader.end();
}

void SoundShader::update ()
{

}

void SoundShader::texturedQuad(float x, float y, float width, float height)
{
    // TODO: change to triangle fan/strip
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
        
    glTexCoord2f(1, 0);
    glVertex3f(x + width, y, 0);
        
    glTexCoord2f(1, 1);
    glVertex3f(x + width, y + height, 0);
        
    glTexCoord2f(0, 1);
    glVertex3f(x, y + height, 0);
    glEnd();
}
