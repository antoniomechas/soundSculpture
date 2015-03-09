#include "part.h"
#include "ofMain.h"

#define OF_ADDON_USING_OFXVECTORMATH

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

//------------------------------------------------------------
part::part(){
	setInitialCondition( ofVec3f(0,0,0), ofVec3f(0,0,0) );
	damping = 0.006f;
}

//------------------------------------------------------------
void part::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
	//updateArray();
}

//------------------------------------------------------------
void part::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void part::addRepulsionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void part::addAttractionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();

		//cout<<frc.x<<" "<<diff.x<<" "<<scale<<" "<<pct<<endl;
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void part::addRepulsionForce(part *p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p->pos.x,p->pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p->frc.x = p->frc.x - diff.x * scale * pct;
        p->frc.y = p->frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void part::addAttractionForce(part *p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p->pos.x,p->pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
		p->frc.x = p->frc.x + diff.x * scale * pct;
        p->frc.y = p->frc.y + diff.y * scale * pct;
    }
	
}


//------------------------------------------------------------
void part::setGravity( float fGravity){
	gravity = fGravity;
}

//------------------------------------------------------------
void part::setDamping( float fDamping){
	damping = fDamping;
}


void part::setScreenLimits(float width, float height)
{
	screenW = width;
	screenH = height;
}

//------------------------------------------------------------
void part::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
    frc.z = frc.z - vel.z * damping;
}

//------------------------------------------------------------
void part::setInitialCondition(ofVec3f p, ofVec3f v){
    
	pos = p;
	vel = v;
	
	tipo = 0;
	viva = true;
	clicksVida = 0;
	r = 255 ; g = 255 ; b = 0;
	bUseSize = false; //por defecto la particula siempre tiene el mismo tamaño
	anclaX=0;anclaY=0;anclaF=0.0f;

	iEspecial = 0;
}

//------------------------------------------------------------
void part::update(){	

	int i;
	float rnd;

	iEspecial = 0;  //Si está en un estado especial, se decidirá después

	clicksVida++;
	if (bPerlin)
	{
		ofVec2f noise;
		double time = ofGetElapsedTimef();
		noise.x = (float)perlinRadio * ofNoise(perlinSeed + time * multVelocidad);
		noise.y = (float)perlinRadio * ofNoise(perlinSeed + 2.0f + time * multVelocidad);
		//if (frc.x < 0)
		//	noise.x = noise.x * -1.0f;
		//if (frc.y < 0)
		//	noise.y = noise.y * -1.0f;
		noise = noise - ofVec2f(perlinRadio/2,perlinRadio/2); //* frc.normalized();
		pos = posIni + noise;
	}

	switch (tipo)
	{
		case 1:
			addDampingForce();
			frc.y = frc.y + gravity;
			vel = vel + frc;
			pos = pos + vel;
			//pos.z = pos.z + ofNoise(
			//if (pos.y > screenH)
			//{
			//	vel.y = -1.0f * vel.y;
			//	pos.y = screenH;
			//}


			//r = ofRandom(r1,r2);
			//g = ofRandom(g1,g2);
			//b = ofRandom(b1,b2);
			
			rnd = ofRandom(0.0f, 1.0f);
			if (rnd > fPorcentajeEspecial)
				iEspecial = 1;

			if (clicksVida > clicksMuerte)
				viva = false;

			a = a1 + (incAlpha * clicksVida);
			if ( (a < 0) || (a > 1) ) 
				viva = false;
			
			break;

		case 2:

			vel = vel + frc;
			pos = pos + vel;

	        a = a1 + (incAlpha * clicksVida);
	        
			if (bUseSize)
				size = s1 + (incSize * clicksVida);

			if ( (a < 0) || (a > 1) ) 
				viva = false;

			break;

		//  Particulas que brillan
		case 3:

			addDampingForce();
			frc.y = frc.y + gravity;
			vel = vel + frc;
			pos = pos + vel;
			//pos.z = pos.z + ofNoise(
			//if (pos.y > screenH)
			//{
			//	vel.y = -1.0f * vel.y;
			//	pos.y = screenH;
			//}


			//r = ofRandom(r1,r2);
			//g = ofRandom(g1,g2);
			//b = ofRandom(b1,b2);
			
			rnd = ofRandom(0.0f, 1.0f);
			if (rnd > fPorcentajeEspecial)
				iEspecial = 1;

			if (clicksVida > clicksMuerte)
				viva = false;

			a = a1 + (incAlpha * clicksVida);
			if ( (a < 0) || (a > 1) ) 
				viva = false;
			
			break;

		case TIPO_PARTICULA_MOSAICO:

			//Verifica si ha llegado al destino, o bien porque esta muy cerca, o bien porque se ha pasado (el signo ha cambiado en y o x)
			ofVec2f posAnt(pos);
			bool llego = false;

			if (pos != posFin)
				pos = pos + vel;

			if ( (sgn(posFin.x - posAnt.x) != sgn(posFin.x - pos.x) ) || (sgn(posFin.y - posAnt.y) != sgn(posFin.y - pos.y) ) )
				llego = true;

			if (pos.distance(posFin) < 10)		
				llego = true;
			
			if (llego)
			{
				pos = posFin;
				viva = false;
			}

			a = a1 + (incAlpha * clicksVida);
			if ( a < 0.0 ) a = 0.0;
			if (a > 1.0) a = 1.0; 
	
	}

	if ( (!viva) && (tipo != TIPO_PARTICULA_MOSAICO) )
	{
		a=0;r=0;g=0;b=0;
		pos.x=0;pos.y=0;
	}

	/*
	if (anclaF > 0.0f)
	{
		addAttractionForce(anclaX, anclaY, anclaF, 0);
		addDampingForce();
	}
	*/
//	_partPos[0] = pos.x;
//	_partPos[1] = pos.y;
//	_partPos[2] = 0;
//
//	//colores de los vertices o puntos
//	int a=0;
//	for (int k=0 ; k < 4 ; k ++)
//	{
//		
//		_partCol[a++] = r;
//		_partCol[a++] = g;
//		_partCol[a++] = b;
//		_partCol[a++] = a;
///*		
//		_partCol[a++] = 1.0f;
//		_partCol[a++] = 1.0f;
//		_partCol[a++] = 1.0f;
//		_partCol[a++] = 1.0f;
//*/
//	}
//
//	//quads
//	_partQuads[0] = pos.x - size;
//	_partQuads[1] = pos.y - size;
//	_partQuads[2] = 0;
//	_partQuads[3] = pos.x - size;
//	_partQuads[4] = pos.y + size;
//	_partQuads[5] = 0;
//	_partQuads[6] = pos.x + size;
//	_partQuads[7] = pos.y + size;
//	_partQuads[8] = 0;
//	_partQuads[9] = pos.x + size;
//	_partQuads[10] = pos.y - size;
//	_partQuads[11] = 0;


}

//------------------------------------------------------------
void part::draw(){

	int radio;
	float f;
	if ( !viva )
		return; 

	switch (tipo)
	{
		case 1:
			glColor4f(r, g, b, a);

			glPushMatrix();

			// Place the quad and rotate to face the viewer
			glTranslatef(pos.x, pos.y, 0);
        
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f); glVertex3f(-size, size,0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(-size,-size,0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f( size,-size,0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f( size, size,0.0f);
			glEnd();

			glPopMatrix();
			break;

		case 2:
			
			glColor4f(r, g, b, a);

			glPushMatrix();

			// Place the quad and rotate to face the viewer
			glTranslatef(pos.x, pos.y, 0);
        
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f); glVertex3f(-size, size,0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(-size,-size,0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f( size,-size,0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f( size, size,0.0f);
			glEnd();

			glPopMatrix();
   
/*
			//Lila
			r = 0;g=0;
			b = 255 - (clicksVida / 1);
			//if (b < 100)
			//	viva = false;

			//Se muere si se vuelve muy oscura
			ofSetColor(r,g,b);
			//ofLine(pos.x,pos.y,pos.x+3,pos.y);
			ofCircle(pos.x, pos.y, 1);
			
			*/
			break;

		case 3:
				//r=1.0f;g=1.0f;b=1.0f;a=1.0f;
				glColor4f(r, g, b, a);
				//glPushMatrix();
				//	glPointSize(3.0f);
				//	glBegin(GL_POINTS);
				//		glVertex2f(pos.x, pos.y);
				//	glEnd();
				//glPopMatrix();
				//ofSetColor(r*255.0f,g*255.0f,b*255.0f,a*255.0f);
				ofCircle(pos, size);
			break;


	}
		//ofLine(pos.x,pos.y,pos.x+2,pos.y+2);
}


//------------------------------------------------------------
void part::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}


void part::ancla(float px, float py, float fuerza, float escala)
{
	anclaX = px;
	anclaY = py;
	anclaF = fuerza;
	addAttractionForce(px, py, fuerza, escala);
}

//Hay que pasar los colores que vienen en el rango 0...255 a 0.0...1.0
void part::setColorRange(ofColor ini, ofColor fin)
{
	r1 = (float)ini.r / 255.0;
	r2 = (float)fin.r / 255.0;

	g1 = (float)ini.g / 255.0;
	g2 = (float)fin.g / 255.0;

	b1 = (float)ini.b / 255.0;
	b2 = (float)fin.b / 255.0;

	r = ofRandom(r1,r2);
	g = ofRandom(g1,g2);
	b = ofRandom(b1,b2);

}

void part::setColorRange(float _r1, float _r2, float _g1, float _g2, float _b1, float _b2)
{
	r1 = _r1;
	r2 = _r2;

	g1 = _g1;
	g2 = _g2;

	b1 = _b1;
	b2 = _b2;

	r = ofRandom(r1,r2);
	g = ofRandom(g1,g2);
	b = ofRandom(b1,b2);

}

void part::setColor(float r, float g, float b)
{
	this -> r = r;
	this -> g = g;
	this -> b = b;
}

ofColor part::getColor()
{
	return ofColor(r * 255.0,g * 255.0,b *255.0);
}

void part::setPos(float x, float y)
{
	pos.set(x, y);
}

float part::getR()
{
	return r;
}
float part::getG()
{
	return g;
}
float part::getB()
{
	return b;
}
float part::getA()
{
	return a;
}


ofVec2f part::getPos()
{
	return(pos);
}
//------------------------------------------------------------
void part::setAlpha(float alphaIni, float alphaFin){
    //Recalcula los parámetros necesarios para el movimiento de la partícula
    a1 = alphaIni;
	a2 = alphaFin;
	
	incAlpha = fabs(a2 - a1) / clicksMuerte ;
	if (a2 < a1)
		incAlpha = incAlpha * -1.0f; 
}

//------------------------------------------------------------
void part::setEndSize(float sizeIni, float sizeFin){
    
	//Ajusta el incremento de tamaño para que sea coherente con la vida de la partícula
	s1 = sizeIni;
	s2 = sizeFin;

	incSize = fabs(sizeFin - sizeIni) / clicksMuerte ;
	if (sizeFin < sizeIni)
		incSize = incSize * -1.0f; 

	//printf("ini=%3.3f,fin=%3.3f,incSize = %3.3f\n",sizeIni,sizeFin,incSize);

	bUseSize = true;
}


void part::updateArray(){
	/*
	int offset, offsetc, offsetq, offsett;

	if (!viva)
	{
		pos.x = 0; 
		pos.y = 0;
		a = 0;
	}

	//printf("particula %i - ",iNumParticula);

	offset = iNumParticula * 3;
	offsetc = iNumParticula * 4;
	offsetq = iNumParticula * 4 * 3;
	offsett = iNumParticula * 4 * 2;

	_partPos[offset] = pos.x;
	_partPos[offset+1] = pos.y;
	_partPos[offset+2] = 0;

	_partCol[offsetc] = r;
	_partCol[offsetc+1] = g;
	_partCol[offsetc+2] = b;
	_partCol[offsetc+3] = a;

	_partQuads[offsetq] = pos.x - size;
	_partQuads[offsetq+1] = pos.y + size;
	_partQuads[offsetq+2] = 0;
	_partQuads[offsetq+3] = pos.x - size;
	_partQuads[offsetq+4] = pos.y - size;
	_partQuads[offsetq+5] = 0;
	_partQuads[offsetq+6] = pos.x + size;
	_partQuads[offsetq+7] = pos.y - size;
	_partQuads[offsetq+8] = 0;
	_partQuads[offsetq+9] = pos.x + size;
	_partQuads[offsetq+10] = pos.y + size;
	_partQuads[offsetq+11] = 0;

	_partTex[offsett] = 0;
	_partTex[offsett+1] = 0;
	_partTex[offsett+2] = 0;
	_partTex[offsett+3] = 1;
	_partTex[offsett+4] = 1;
	_partTex[offsett+5] = 1;
	_partTex[offsett+6] = 1;
	_partTex[offsett+7] = 0;
	
	*/
	/*
	glTexCoord2f(0.0f,0.0f); glVertex3f(-size, size,0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(-size,-size,0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f( size,-size,0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f( size, size,0.0f);
	_partPos[offset] = pos.x;
	_partPos[iNumParticula][1] = pos.y;
	_partPos[iNumParticula][2] = 0;

	_partCol[iNumParticula][0] = r;
	_partCol[iNumParticula][1] = g;
	_partCol[iNumParticula][2] = b;
	_partCol[iNumParticula][3] = a;

	_partQuads[iNumParticula][0] = pos.x - size;
	_partQuads[iNumParticula][1] = pos.y + size;
	_partQuads[iNumParticula][2] = 0;
	_partQuads[iNumParticula][3] = pos.x - size;
	_partQuads[iNumParticula][4] = pos.y - size;
	_partQuads[iNumParticula][5] = 0;
	_partQuads[iNumParticula][6] = pos.x + size;
	_partQuads[iNumParticula][7] = pos.y - size;
	_partQuads[iNumParticula][8] = 0;
	_partQuads[iNumParticula][9] = pos.x + size;
	_partQuads[iNumParticula][10] = pos.y + size;
	_partQuads[iNumParticula][11] = 0;


*/

}