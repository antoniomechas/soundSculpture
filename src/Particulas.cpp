#include "Particulas.h"


void Particulas::setup(float width, float height)
{
	
	this->width = width;
	this->height = height;
	
	setupLigths();

	//audioDataAmount = cols * rows;
	audioDataAmount = 255;
	
	sistPart.setup();
	sistPart.CargaTextura("texCirculoStar.bmp");

}

void Particulas::draw()
{
	//ofEnableDepthTest();

	//ofEnableLighting();
	//ofSetSmoothLighting(true);
	//light.setPosition(300,-300,paramLightDistance);
	//light.enable();
	ofNoFill();
	ofRect(-width/2,-height/2,width,height);
	sistPart.dibuja();
	//draw

	//light.disable();
	
	//ofDisableLighting();

}

void Particulas::update(float average, float *soundData)
{
	for (int i = 0 ; i < audioDataAmount ; i++)
	{
		float vz = ofRandom(sistPart.partVelZ1, sistPart.partVelZ2);
		//float vel = sistPart.part2ColorAutoDelay * 100.0f;
		//ofVec2f velo = ofVec2f(punto - centro);
		//velo.rescale(vel);
		ofVec3f punto(ofRandom(-width/2, width/2), ofRandom(-height/2, height/2), 0);
		int p = sistPart.añadeParticula(punto, ofVec3f(ofRandom(-1,1),ofRandom(-1,1),0));
		sistPart.particulas[p].tipo = sistPart.partTipo;
		sistPart.particulas[p].clicksMuerte = ofRandom(sistPart.partVidaIni, sistPart.partVidaFin) ;
		sistPart.particulas[p].bUseSize = false;
		sistPart.particulas[p].setAlpha( ofRandom(sistPart.partAlphaIni1, sistPart.partAlphaIni2), ofRandom(sistPart.partAlphaFin1, sistPart.partAlphaFin2) );
		sistPart.particulas[p].size = ofRandom(sistPart.partSizeIni, sistPart.partSizeFin) * soundData[i] * 5.0f;
		sistPart.particulas[p].viva = true;
		sistPart.particulas[p].fPorcentajeEspecial = sistPart.partPorcentajeEspecial;
		sistPart.particulas[p].setDamping(sistPart.partDamping);
		sistPart.particulas[p].setGravity(sistPart.partGravedad);
		sistPart.particulas[p].setScreenLimits(width, height);

		if (sistPart.partColorAuto)
			sistPart.particulas[p].setColorRange(colorUtil.getNoiseColor(ofGetElapsedTimef() * sistPart.partColorAutoDelay), 
												colorUtil.getNoiseColor(40.0f + ofGetElapsedTimef() * sistPart.partColorAutoDelay));
		else
			sistPart.particulas[p].setColorRange(sistPart.partColorIni, sistPart.partColorFin);
	}

	sistPart.actualiza();

}

void Particulas::setupLigths() {
    
    light.setAmbientColor( ofFloatColor( 0.0f, 0.0f, 0.0f, 1.0f ) );
    light.setDiffuseColor( ofFloatColor( 0.9f, 0.9f, 0.9f, 1.0f ) );
    light.setSpecularColor( ofFloatColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
    
    light.setPosition( 0,0, 200.0f);
	light.lookAt(ofVec3f(0,0,0));
    
    ofSetGlobalAmbientColor( ofFloatColor( 0.05f, 0.05f, 0.05f ) );
}

int Particulas::getAudioDataAmount ()
{
	return audioDataAmount;
}


