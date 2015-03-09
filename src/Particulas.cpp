#include "Particulas.h"


void Particulas::setup(float width, float height)
{
	
	this->width = width;
	this->height = height;
	
	setupLigths();

	//audioDataAmount = cols * rows;
	audioDataAmount = 255;
	
	sistPart.setup();
	sistPart.CargaTextura("spark.png");

	colorUtil.setup();
	for (int i = 0 ; i < 4 ; i++)
	{
		emitter[i].pos = ofPoint( 0, 0, 0 );	//Start from center of coordinate
		emitter[i].axeX = ofPoint( 1, 0, 0 );	//Set initial coordinate system
		emitter[i].axyY = ofPoint( 0, 1, 0 );
		emitter[i].axyZ = ofPoint( 0, 0, 1 );
		emitter[i].dir = ofVec2f(0,0);
	}
}

void Particulas::draw()
{
	//ofEnableDepthTest();

	//ofEnableLighting();
	//ofSetSmoothLighting(true);
	//light.setPosition(300,-300,paramLightDistance);
	//light.enable();
	drawAsociaciones();
	ofNoFill();
	ofRect(-width/2,-height/2,width,height);
	sistPart.dibuja();
	
	//draw

	//light.disable();
	
	//ofDisableLighting();

}

void Particulas::drawAsociaciones()
{
	ofSetColor(255,255,255);
	for (int i = 0 ; i < asociaciones.size() ; i++)
	{
		float alpha = sistPart.particulas[asociaciones[i].nodo1].a + 
						sistPart.particulas[asociaciones[i].nodo2].a +
						sistPart.particulas[asociaciones[i].nodo3].a;
		alpha = (alpha / 3.0) * 255.0;
		ofSetColor(asociaciones[i].color1, alpha);
		ofSetLineWidth(asociaciones[i].lineWidth);
		ofLine(sistPart.particulas[asociaciones[i].nodo1].pos, 
				sistPart.particulas[asociaciones[i].nodo2].pos);
		ofSetColor(asociaciones[i].color2, alpha);
		ofLine(sistPart.particulas[asociaciones[i].nodo2].pos, 
				sistPart.particulas[asociaciones[i].nodo3].pos);
		ofSetColor(asociaciones[i].color3, alpha);
		ofLine(sistPart.particulas[asociaciones[i].nodo3].pos, 
				sistPart.particulas[asociaciones[i].nodo1].pos);
	}

}

void Particulas::update(float average, float *soundData)
{
	//for (int i = 0 ; i < audioDataAmount ; i++)
	int a = MAX(1,(int)(average * 10.0f));
	for (int i = 0 ; i < a ; i++)
	{
		//float vel = sistPart.part2ColorAutoDelay * 100.0f;
		//ofVec2f velo = ofVec2f(punto - centro);
		//velo.rescale(vel);
		// se crean 3 particulas para formar el triángulo
		//ofVec3f punto(ofRandom(-width/2, width/2), ofRandom(-height/2, height/2), 0);
		for (int iEmitter = 0 ; iEmitter < 4 ; iEmitter++)
		{
			ofVec3f punto = emitter[iEmitter].pos;
		 
			ofVec3f punto2 = punto;
			int pOrg[3];
			for (int k = 0 ; k < 3 ; k++)
			{
				float vz = ofRandom(sistPart.partVelZ1, sistPart.partVelZ2);
				int p = addParticula(punto2, ofVec3f( ofRandom(-1,1),ofRandom(-1,1),vz), average);
				pOrg[k] = p;
				punto2 = punto + ofVec3f(ofRandom(5,5 + 10 * average), ofRandom(5,5 + 10 * average),0);
			}
			addAsociacion(pOrg, 6.0f * average); //añade una asociacion a partir del indice de partícula especificada
		}
	}

	sistPart.actualiza();

	updateMesh( average, soundData);
	
	updatePosicion();

}

int Particulas::addParticula(ofVec3f pos, ofVec3f vel, float audioAverage)
{
	int p = sistPart.añadeParticula(pos, vel);
	sistPart.particulas[p].tipo = sistPart.partTipo;
	sistPart.particulas[p].clicksMuerte = ofRandom(sistPart.partVidaIni, sistPart.partVidaFin) ;
	sistPart.particulas[p].bUseSize = false;
	sistPart.particulas[p].setAlpha( ofRandom(sistPart.partAlphaIni1, sistPart.partAlphaIni2), ofRandom(sistPart.partAlphaFin1, sistPart.partAlphaFin2) );
	//sistPart.particulas[p].size = ofRandom(sistPart.partSizeIni, sistPart.partSizeFin) * soundData[i] * paramMult;
	sistPart.particulas[p].size = ofRandom(sistPart.partSizeIni, sistPart.partSizeFin) * audioAverage * paramMult;
	sistPart.particulas[p].viva = true;
	sistPart.particulas[p].fPorcentajeEspecial = sistPart.partPorcentajeEspecial;
	sistPart.particulas[p].setDamping(sistPart.partDamping);
	sistPart.particulas[p].setGravity(sistPart.partGravedad);
	sistPart.particulas[p].setScreenLimits(width, height);
	ofColor c1,c2;
		
	if (sistPart.partColorAuto)
	{
		c1 = colorUtil.getNoiseColor(ofGetElapsedTimef() * sistPart.partColorAutoDelay);
		c2 = colorUtil.getNoiseColor(40.0f + ofGetElapsedTimef() * sistPart.partColorAutoDelay);
	}
	else
	{		
		c1 = sistPart.partColorIni;
		c2 = sistPart.partColorFin;
	}
	c1.setHue(c1.getHue() * audioAverage);
	c2.setHue(c2.getHue() * audioAverage);
	sistPart.particulas[p].setColorRange(c1, c2);
	return p;

}

void Particulas::updatePosicion()
{
	float time = ofGetElapsedTimef();	//Time
	/*
	//Parameters – twisting and rotating angles and color
	float twistAngle = 5.0 * ofSignedNoise( time * 0.3 + 332.4 );
	float rotateAngle = 1.5;
	ofFloatColor colorPosicion( ofNoise( time * 0.05 ),
		ofNoise( time * 0.1 ),
		ofNoise( time * 0.15 ));
	emitter.color = colorPosicion;
	emitter.color.setSaturation( 1.0 );			//Make the color maximally colorful

	//Rotate the coordinate system of the circle
	emitter.axeX.rotate( twistAngle, emitter.axyZ );
	emitter.axyY.rotate( twistAngle, emitter.axyZ );

	emitter.axeX.rotate( rotateAngle, emitter.axyY );
	emitter.axyZ.rotate( rotateAngle, emitter.axyY );

	//Move the circle on a step
	float circleStep = 3;		//Step size for circle motion
	ofPoint move = emitter.axyZ * circleStep;
	//emitter.pos += move;
	*/
	for (int i = 0 ; i < 4 ; i ++)
	{
		emitter[i].dir.x = ofSignedNoise(time * 0.1,i);
		emitter[i].dir.y = ofSignedNoise(i,time * 0.1);

		emitter[i].pos += emitter[i].dir * 10.0f;

		if (emitter[i].pos.z < 100 || emitter[i].pos.z > 100)
			emitter[i].pos.z *= -1.0;

		if (emitter[i].pos.x < -width/2 || emitter[i].pos.x > width/2)
			emitter[i].pos.x *= -1.0;

		if (emitter[i].pos.y < -height/2 || emitter[i].pos.y > height/2)
			emitter[i].pos.y *= -1.0;
	}
}

void Particulas::addAsociacion(int *pos, float lineWidht)
{
		ASOCIACION a;
		
		a.lineWidth = MAX(1.0, lineWidht);		
		a.lineWidth = 1.0;

		a.nodo1 = pos[0];
		a.nodo2 = pos[1];
		a.nodo3 = pos[2];

		a.vida = ofRandom(400,600);
		a.color1 = sistPart.particulas[a.nodo1].getColor();
		a.color2 = sistPart.particulas[a.nodo2].getColor();
		a.color3 = sistPart.particulas[a.nodo3].getColor();
		//ofColor c1,c2;
		//if (sistPart.partColorAuto)
		//{
		//	c1 = colorUtil.getNoiseColor(ofGetElapsedTimef() * sistPart.partColorAutoDelay);
		//	c2 = colorUtil.getNoiseColor(40.0f + ofGetElapsedTimef() * sistPart.partColorAutoDelay);
		//}
		//else
		//{		
		//	c1 = sistPart.partColorIni;
		//	c2 = sistPart.partColorFin;
		//}
		//a.color = ofColor(ofRandom(c1.r,c2.r),ofRandom(c1.g,c2.g),ofRandom(c1.b,c2.b));
	
		//ofVec3f p1 = sistPart.particulas[a.nodo1].pos;
		//ofVec3f p2 = sistPart.particulas[a.nodo2].pos;
		//ofVec3f p3 = sistPart.particulas[a.nodo3].pos;
		//float dMax = 200;
	
		//if (p1.distance(p2) < dMax && p2.distance(p3) < dMax && p3.distance(p1) < dMax)
			asociaciones.push_back(a);
}

void Particulas::updateMesh(float average, float *soundData)
{
	/*
	pVivas.clear();

	for (int i = 0 ; i < sistPart.iLimiteParticulas ; i++)
		if (sistPart.particulas[i].viva)
			pVivas.push_back(i);

	//crear asociaciones entre nodos

	int maxP = sistPart.iLimiteParticulas;

	ASOCIACION a;
	for (int i = 0 ; i < 50 ; i++)
	{
		//int rnd1 = ofRandom(0, pVivas.size());
		//int rnd2 = ofRandom(0, pVivas.size());
		//int rnd3 = ofRandom(0, pVivas.size());
		//a.nodo1 = pVivas[rnd1];
		//a.nodo2 = pVivas[rnd2];
		//a.nodo3 = pVivas[rnd3];

		int rnd1 = ofRandom(1, pVivas.size()/3);
		a.nodo1 = pVivas[rnd1 * 3];
		a.nodo2 = a.nodo1 + 1;
		a.nodo3 = a.nodo1 + 2;

		a.vida = ofRandom(400,600);
		a.color1 = sistPart.particulas[a.nodo1].getColor();
		a.color2 = sistPart.particulas[a.nodo2].getColor();
		a.color3 = sistPart.particulas[a.nodo3].getColor();
		//ofColor c1,c2;
		//if (sistPart.partColorAuto)
		//{
		//	c1 = colorUtil.getNoiseColor(ofGetElapsedTimef() * sistPart.partColorAutoDelay);
		//	c2 = colorUtil.getNoiseColor(40.0f + ofGetElapsedTimef() * sistPart.partColorAutoDelay);
		//}
		//else
		//{		
		//	c1 = sistPart.partColorIni;
		//	c2 = sistPart.partColorFin;
		//}
		//a.color = ofColor(ofRandom(c1.r,c2.r),ofRandom(c1.g,c2.g),ofRandom(c1.b,c2.b));
	
		//ofVec3f p1 = sistPart.particulas[a.nodo1].pos;
		//ofVec3f p2 = sistPart.particulas[a.nodo2].pos;
		//ofVec3f p3 = sistPart.particulas[a.nodo3].pos;
		//float dMax = 200;
	
		//if (p1.distance(p2) < dMax && p2.distance(p3) < dMax && p3.distance(p1) < dMax)
			asociaciones.push_back(a);
	}
*/
	for (int i = 0 ; i < asociaciones.size() ; i++)
	{
		asociaciones[i].vida--;
		if (asociaciones[i].vida <= 0 || !sistPart.particulas[asociaciones[i].nodo1].viva
										|| !sistPart.particulas[asociaciones[i].nodo2].viva 
										|| !sistPart.particulas[asociaciones[i].nodo3].viva )
			asociaciones.erase(asociaciones.begin() + i);
	}

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


