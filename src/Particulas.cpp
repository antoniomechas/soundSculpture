#include "Particulas.h"


void Particulas::setup(float width, float height, ofxBeatDetector *beat, ofEasyCam *camera)
{
	
	this->width = width;
	this->height = height;
	this->beatDetector = beat;
	this->camera = camera;

	setupLigths();

	//audioDataAmount = cols * rows;
	audioDataAmount = 255;
	
	sistPart.setup();
	sistPart.CargaTextura("spark.png");

	colorUtil.setup();
	Emitter *e;
	for (int i = 0 ; i < 6 ; i++)
	{
		e = new Emitter;
		e->setup(width, height, ofPoint( 0, 0, 0 ), ofVec2f(0,0), colorUtil.getRandomBrightColor(), &colorUtil);
		e->beatReaction = (Emitter::BeatReaction)((i % 3) + 3);
		//e->beatReaction = (Emitter::BeatReaction::BEAT_REACTION_HAT);
		emitters.push_back(*e);
	}

	post.init(width, height);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);
	post2.init(width, height);
}

void Particulas::draw()
{
	//ofEnableDepthTest();

	//ofEnableLighting();
	//ofSetSmoothLighting(true);
	//light.setPosition(300,-300,paramLightDistance);
	//light.enable();
	ofBackground(0,0,0);
	ofSetColor(255,255,255);
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	post.begin();
		camera->begin();
			drawAsociaciones(true);
		camera->end();
	post.end();

	post2.begin();
		camera->begin();
			drawAsociaciones(false);
			ofNoFill();
			ofRect(-width/2,-height/2,width,height);
			sistPart.dibuja();
		camera->end();	
	post2.end();
	//draw

	//light.disable();
	
	//ofDisableLighting();

}

void Particulas::drawAsociaciones(bool postPass)
{
	mesh.clear();
	ofSetColor(255,255,255);
	//ofSetCircleResolution(100);
	//for (int i = 0 ; i < asociaciones.size() ; i++)
	//{
	//	float alpha = sistPart.particulas[asociaciones[i].nodo1].a + 
	//					sistPart.particulas[asociaciones[i].nodo2].a +
	//					sistPart.particulas[asociaciones[i].nodo3].a;
	//	alpha = (alpha / 3.0) * 255.0;
	//	if (!postPass || (postPass && asociaciones[i].bloomLife > 0))
	//	{
	//		mesh.addVertex(sistPart.particulas[asociaciones[i].nodo1].pos);
	//		float dist = sistPart.particulas[asociaciones[i].nodo1].pos.distance(sistPart.particulas[asociaciones[i].nodo1].posIni); 
	//		float dist2 = sistPart.particulas[asociaciones[i].nodo1].pos.distance(sistPart.particulas[asociaciones[i].nodo2].pos); 
	//		ofSetColor(ofColor(asociaciones[i].color1, alpha));
	//		ofEllipse(sistPart.particulas[asociaciones[i].nodo1].posIni, dist, dist2);
	//		ofCircle(sistPart.particulas[asociaciones[i].nodo1].posIni, dist);
	//	}
	//}
	//return;
	for (int i = 0 ; i < asociaciones.size() ; i++)
	{
		float alpha = sistPart.particulas[asociaciones[i].nodo1].a + 
						sistPart.particulas[asociaciones[i].nodo2].a +
						sistPart.particulas[asociaciones[i].nodo3].a;
		alpha = (alpha / 3.0) * 255.0;
		if (!postPass || (postPass && asociaciones[i].bloomLife > 0))
		{
			mesh.addVertex(sistPart.particulas[asociaciones[i].nodo1].pos);
			mesh.addVertex(sistPart.particulas[asociaciones[i].nodo2].pos);
			mesh.addVertex(sistPart.particulas[asociaciones[i].nodo3].pos);
			mesh.addColor(ofColor(asociaciones[i].color1, alpha));
			mesh.addColor(ofColor(asociaciones[i].color2, alpha));
			mesh.addColor(ofColor(asociaciones[i].color3, alpha));
			mesh.addTriangle(mesh.getNumVertices()-3, mesh.getNumVertices()-2, mesh.getNumVertices()-1);
		}
		//mesh.addIndex(mesh.getNumVertices()-1);
		//mesh.addIndex(mesh.getNumVertices());
	}
	switch (paramDrawMode)
	{
		case 0: //puntos
			//mesh.setMode(OF_PRIMITIVE_TRIANGLES);
			mesh.drawVertices();
			break;

		case 1: //wireframe
			mesh.setMode(OF_PRIMITIVE_TRIANGLES);
			mesh.drawWireframe();
			break;

		case 2: //puntos
			mesh.setMode(OF_PRIMITIVE_TRIANGLES);
			mesh.drawFaces();
			break;
	}
}

void Particulas::update(float average, float *soundData)
{
	//for (int i = 0 ; i < audioDataAmount ; i++)
	int a = MAX(1,(int)(average * paramMult));
	//if (beatDetector->isHigh())
	//	a = 1;
	for (int i = 0 ; i < a ; i++)
	{
		//float vel = sistPart.part2ColorAutoDelay * 100.0f;
		//ofVec2f velo = ofVec2f(punto - centro);
		//velo.rescale(vel);
		// se crean 3 particulas para formar el triángulo
		//ofVec3f punto(ofRandom(-width/2, width/2), ofRandom(-height/2, height/2), 0);
		for (int iEmitter = 0 ; iEmitter < emitters.size() ; iEmitter++)
		{
			ofVec3f punto = emitters[iEmitter].pos;
			ofVec3f punto2 = punto;
			int pOrg[3];
			for (int k = 0 ; k < 3 ; k++)
			{
				float velX = ofRandom(sistPart.partVelXmin,sistPart.partVelXmax);
				float velY = ofRandom(sistPart.partVelYmin,sistPart.partVelYmax);
				float velZ = ofRandom(sistPart.partVelZ1, sistPart.partVelZ2);
				//if (beatDetector->isHigh())
				//{
				//	velX *= 2.0;
				//	velY *= 2.0;
				//}
				int p = addParticula(punto2, ofVec3f( velX, velY, velZ), average, emitters[iEmitter].color);
				//if (beatDetector->isHigh())
				//{
				//	sistPart.particulas[p].clicksMuerte = ofRandom(30,40);
				//	sistPart.particulas[p].setColor(1.0,1.0,1.0);
				//}
				pOrg[k] = p;
				float maxDist = 5;
				float minDist = 2;
				punto2 = punto + ofVec3f(ofRandom(minDist, maxDist * average), ofRandom(minDist, maxDist * average),0);
			}
			addAsociacion(emitters[iEmitter], pOrg, 6.0f * average); //añade una asociacion a partir del indice de partícula especificada
		}
	}

	sistPart.actualiza();

	updateMesh( average, soundData);
	
	updatePosicion();

}

int Particulas::addParticula(ofVec3f pos, ofVec3f vel, float audioAverage, ofColor color)
{
	int p = sistPart.añadeParticula(pos, vel);
	sistPart.particulas[p].tipo = sistPart.partTipo;
	sistPart.particulas[p].clicksMuerte = ofRandom(sistPart.partVidaIni, sistPart.partVidaFin) ;
	sistPart.particulas[p].bUseSize = false;
	sistPart.particulas[p].setAlpha( ofRandom(sistPart.partAlphaIni1, sistPart.partAlphaIni2), ofRandom(sistPart.partAlphaFin1, sistPart.partAlphaFin2) );
	//sistPart.particulas[p].size = ofRandom(sistPart.partSizeIni, sistPart.partSizeFin) * soundData[i] * paramMult;
	sistPart.particulas[p].size = ofRandom(sistPart.partSizeIni, sistPart.partSizeFin);// * audioAverage * paramMult;
	sistPart.particulas[p].viva = true;
	sistPart.particulas[p].fPorcentajeEspecial = sistPart.partPorcentajeEspecial;
	sistPart.particulas[p].setDamping(sistPart.partDamping);
	sistPart.particulas[p].setGravity(sistPart.partGravedad);
	sistPart.particulas[p].setScreenLimits(width, height);
	ofColor c1,c2;
		
	if (sistPart.partColorAuto)
	{
		c1 = colorUtil.getNoiseColor(ofGetElapsedTimef() * sistPart.partColorAutoDelay + audioAverage * 100);
		c2 = colorUtil.getNoiseColor(40.0f + ofGetElapsedTimef() * sistPart.partColorAutoDelay + audioAverage * 100);
	}
	else
	{		
		c1 = sistPart.partColorIni;
		c2 = sistPart.partColorFin;
	}
	//c1.setHue(c1.getHue() * audioAverage);
	//c2.setHue(c2.getHue() * audioAverage);
	c1.setBrightness(c1.getBrightness() + audioAverage);
	c2.setBrightness(c2.getBrightness() + audioAverage);
	//sistPart.particulas[p].setColorRange(c1, c2);
	sistPart.particulas[p].setColorRange(color, color);

	return p;

}

void Particulas::updatePosicion()
{
	for (int i = 0 ; i < emitters.size(); i++)
	{
		if (beatDetector->isLow())
			emitters[i].setMoveSeed( emitters[i].getMoveSeed() + 1);

		emitters[i].setSpeedInc(paramSpeedInc);
		emitters[i].setMoveNoise(paramMoveNoiseMult);
		emitters[i].setColorNoiseMult(paramColorNoiseMult);
		emitters[i].update();
	}
}

void Particulas::addAsociacion(Emitter &emitter, int *pos, float lineWidht)
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
		bool bloom = false;
		//cout << "beatReaction: " << emitter.beatReaction << endl;
		switch (emitter.beatReaction)
		{
			case Emitter::BeatReaction::BEAT_REACTION_HAT:
				beatDetector->setBeatValue(beatHatValue);
				//cout << "Hatvalue: " << beatHatValue << endl;
				if (beatDetector->isHat())
					bloom = true;
				break;
			case Emitter::BeatReaction::BEAT_REACTION_KICK:
				beatDetector->setBeatValue(beatKickValue);
				//cout << "Kickvalue: " << beatHatValue << endl;
				if (beatDetector->isKick())
					bloom = true;
				break;
			case Emitter::BeatReaction::BEAT_REACTION_SNARE:
				beatDetector->setBeatValue(beatSnareValue);
				//cout << "Snarevalue: " << beatHatValue << endl;
				if (beatDetector->isSnare())
					bloom = true;
				break;
			//case Emitter::BeatReaction::BEAT_REACTION_LOW:
			//	if (beatDetector->isLow())
			//		bloom = true;
			//	break;
			//case Emitter::BeatReaction::BEAT_REACTION_MID:
			//	if (beatDetector->isMid())
			//		bloom = true;
			//	break;
			//case Emitter::BeatReaction::BEAT_REACTION_HIGH:
			//	if (beatDetector->isHigh())
			//		bloom = true;
			//	break;

		}
		
		if (bloom)
			a.bloomLife = sistPart.particulas[a.nodo1].clicksMuerte;
		else
			a.bloomLife = 0;

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
		asociaciones[i].bloomLife--;
		if (asociaciones[i].vida <= 0 || !sistPart.particulas[asociaciones[i].nodo1].viva
										|| !sistPart.particulas[asociaciones[i].nodo2].viva 
										|| !sistPart.particulas[asociaciones[i].nodo3].viva )
			asociaciones.erase(asociaciones.begin() + (i--));
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


