
#include "AVGSistPart.h"

void AVGSistPart::inicializa()
{
	for (int i = 0 ; i < MAXPART ; i ++)
	{
		particulas[i].viva = false;
		particulas[i].setPos(0,0);
		particulas[i].setColor(0,0,0);
		particulas[i].setAlpha(0,0);
		particulas[i].size=0;
		particulas[i].iNumParticula = i;
		particulas[i]._partCol = partCol[i];
		particulas[i]._partPos = partPos[i];
		particulas[i]._partQuads = partQuads[i];
		particulas[i]._partTex = partTex[i];
	
		partPos[i][0] = 0;
		partPos[i][1] = 0;
		partPos[i][2] = 0;


		for (int k = 0 ; k < 8 ; k++)
		{
			partTex[i][k]=0;
			partQuads[i][k]=0;
			partCol[i][k] = 0;
		}
		for (int k = 8 ; k < 12 ; k++)
		{
			partQuads[i][k]=0;
			partCol[i][k] = 0;
		}
	}

	iParticulaActual = 0;
	iLimiteParticulas = 999999;
}


void AVGSistPart::setup()
{
	
	bUseVBO = false;
	bDrawQuads = false;

	inicializa();

	glGenBuffersARB(4, &vboP[0]);
				
	// vbo for vertex positions
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[0]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(partPos), partPos, GL_STREAM_DRAW_ARB);

	// vbo for vertex colors
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[1]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(partCol), partCol, GL_STREAM_DRAW_ARB);

	// vbo for quads
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[2]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(partQuads), partQuads, GL_STREAM_DRAW_ARB);

	// vbo for textures
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[3]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(partTex), partTex, GL_STREAM_DRAW_ARB);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	// Por defecto el sistema de particulas funciona como particulas
	modo = MODO_NORMAL;
	// El mosaico no se ha inicializado
	mosaico_params.estado = mosaico_params.ESTADO_MOSAICO_IDLE;

}

void AVGSistPart::resetMosaico()
{
	mosaico_params.estado = mosaico_params.ESTADO_MOSAICO_IDLE;
}


void AVGSistPart::actualiza()
{
	switch (modo)
	{
		case MODO_NORMAL:
			break;
		
		case MODO_MOSAICO:
			//Hay que ver si el mosaico se ha inicializado, o sea, que las particulas deberán dirigirse hacia su lugar en el mosaico
			if (mosaico_params.estado == mosaico_params.ESTADO_MOSAICO_IDLE)
			{
				initMosaico();
				mosaico_params.estado = mosaico_params.ESTADO_MOSAICO_WORKING;
			}
			break;
	}

	for (int i=0 ; (i < MAXPART) && (i < iLimiteParticulas); i++)
		if ( particulas[i].viva )
			particulas[i].update();

	//actualizaArray();
	//printf("Actualiza ");
}

//--------------------------------------
//Inicializa las particulas para que se comporten en modo mosaico
void AVGSistPart::initMosaico()
{

	//ofVec2f imageSize(mosaico_params.width, mosaico_params.height);

	//mosaico_params.partVivas.clear();
	//// Mira cuantas particulas hay en el sistema
	//for (int i=0 ; (i < MAXPART) && (i < iLimiteParticulas) ; i++)
	//	if ( particulas[i].viva )
	//		mosaico_params.partVivas.push_back(i);
	//
	//// Calcula en cuantas filas y columnas hay que dividir la imagen para que quepan todas las partículas
	//// teniendo en cuenta el aspect ratio de la imagen

	//mosaico_params.aspectratio = (float)mosaico_params.height / (float)mosaico_params.width;
	//mosaico_params.rows = sqrt( mosaico_params.aspectratio * (float)mosaico_params.partVivas.size() );
	//mosaico_params.columns = (float)mosaico_params.partVivas.size() / mosaico_params.rows;
	//mosaico_params.cellW = (float)mosaico_params.width / mosaico_params.columns;
	//mosaico_params.cellH = (float)mosaico_params.height / mosaico_params.rows;
	//float xx = 0;
	//float yy = 0;
	//printf("num particulas: (%i)\n", mosaico_params.partVivas.size());
	//printf("Imagen: (%i,%i)\n", mosaico_params.width, mosaico_params.height);
	//printf("aspect ratio: %1.3f\n",mosaico_params.aspectratio);
	//printf("columns, rows: (%1.3f,%1.3f)\n",mosaico_params.columns, mosaico_params.rows);

	//for(int c = 0; c < mosaico_params.partVivas.size(); c++) 
	//{
	//	part *p = &particulas[mosaico_params.partVivas[c]];
	//	p->posFin = ofVec2f(xx, yy);
	//	p->vel = p->posFin - p->pos;
	//	p->vel.normalize();
	//	p->vel = p->vel * ofRandom(partMosaicoVelIni, partMosaicoVelFin);
	//	p->tipo = TIPO_PARTICULA_MOSAICO;

	//	xx += mosaico_params.cellW;
	//	if (xx >= mosaico_params.width)
	//	{
	//		xx = 0;
	//		yy += mosaico_params.cellH;
	//	}
	//}

}

void AVGSistPart::resetForce()
{
	for (int i=0 ; (i < MAXPART) && (i < iLimiteParticulas); i++)
		if ( particulas[i].viva )
			particulas[i].resetForce();
}

//------------------------------------------------------------------
//Dibuja el sistema de partículas dependiendo del modo activo
//
void AVGSistPart::dibuja()
{
	ofPushStyle();

	//switch (modo)
	//{
	//	case MODO_MOSAICO:
	//		dibujaMosaico();
	//		break;
	//	
	//	case MODO_NORMAL:
	//		if (bUseVBO)
	//			dibujaVBO();
	//		else
	//			dibujaParticulas();
	//
	//		dibujaEspeciales();
	//		
	//		break;
	//}

	dibujaEspeciales();

	ofPopStyle();

}

//------------------------------------------------------------------
//Dibuja las particulas como quads que contiene cada una una parte de la imagen fotoMosaico
//
void AVGSistPart::dibujaMosaico()
{
	//return;
	mosaico_params.mesh.clear();
	mosaico_params.mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	

	ofVec2f imageSize(mosaico_params.width,mosaico_params.height);
	
	float xx = 0;
	float yy = 0;
	for(int c = 0; c < mosaico_params.partVivas.size(); c++) 
	{
		part *p = &particulas[mosaico_params.partVivas[c]];
		ofVec3f nw = ofVec3f(p->pos.x - (mosaico_params.cellW / 2.0) , p->pos.y - (mosaico_params.cellH / 2.0), 0);
		ofVec3f ne = ofVec3f(p->pos.x + (mosaico_params.cellW / 2.0) , p->pos.y - (mosaico_params.cellH / 2.0), 0);
		ofVec3f sw = ofVec3f(p->pos.x - (mosaico_params.cellW / 2.0) , p->pos.y + (mosaico_params.cellH / 2.0), 0);
		ofVec3f se = ofVec3f(p->pos.x + (mosaico_params.cellW / 2.0) , p->pos.y + (mosaico_params.cellH / 2.0), 0);
		//ofVec3f nw = ofVec3f(p->pos.x - (p->size / 2) , p->pos.y - (p->size / 2), 0);
		//ofVec3f ne = ofVec3f(p->pos.x + (p->size / 2) , p->pos.y - (p->size / 2), 0);
		//ofVec3f sw = ofVec3f(p->pos.x - (p->size / 2) , p->pos.y + (p->size / 2), 0);
		//ofVec3f se = ofVec3f(p->pos.x + (p->size / 2) , p->pos.y + (p->size / 2), 0);
		ofVec2f nwi(xx, yy);
		ofVec2f nei(xx + mosaico_params.cellW, yy);
		ofVec2f swi(xx, yy + mosaico_params.cellH);
		ofVec2f sei(xx + mosaico_params.cellW, yy + mosaico_params.cellH);
			
		addFace(mosaico_params.mesh, nw, ne, se, sw);

		// Normalize our texture coordinates if normalized 
		// texture coordinates are currently enabled.
		if(ofGetUsingNormalizedTexCoords()) 
		{
			nwi /= imageSize;
			nei /= imageSize;
			sei /= imageSize;
			swi /= imageSize;
		}

		addTexCoords(mosaico_params.mesh, nwi, nei, sei, swi);
		
		xx += mosaico_params.cellW;
		if (xx >= mosaico_params.width)
		{
			xx = 0;
			yy+=mosaico_params.cellH;
		}

	}
	ofBackground(0,0,0);
	ofSetColor(255,255,255);
	
	mosaico_params.fotoMosaico.bind();
	mosaico_params.mesh.draw();
	mosaico_params.fotoMosaico.unbind();

}

//------------------------------------------------------------------
//Dibuja el sistema de particulas como partículas
//
void AVGSistPart::dibujaParticulas()
{
	//glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBindTexture(GL_TEXTURE_2D, gltexture[0]);
	glEnable( GL_POINT_SMOOTH );
	float p;
	float r,g,b,a;
	float s;

	for (int i=0 ; (i < MAXPART) && (i < iLimiteParticulas) ; i++)
		if ( particulas[i].viva )
		{
			r = particulas[i].r;
			g = particulas[i].g;
			b = particulas[i].b;
			a = particulas[i].a;
			s = 1.0f;
			glColor4f(r, g, b, a);
			glPointSize(s);
			glBegin(GL_POINTS);
				glVertex2f(particulas[i].pos.x, particulas[i].pos.y);
			glEnd();
			//ofCircle(particulas[i].pos.x, particulas[i].pos.y,5);
			//printf("%i,%i\n",particulas[i].pos.x, particulas[i].pos.y);
		}


	glDisable(GL_BLEND);									
	//glDisable(GL_TEXTURE_2D);
	glDisable( GL_POINT_SMOOTH );

}


void AVGSistPart::dibujaEspeciales()
{
	
	float size;
	float x, y, z;
	float a;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gltexture[0]);
	glEnable( GL_POINT_SMOOTH );
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	for (int i=0 ; (i < MAXPART) && (i < iLimiteParticulas) ; i++)
		if ( particulas[i].viva && (particulas[i].iEspecial > 0) )
		{
			size = particulas[i].size;
			//printf("especial %i", size);
			x = particulas[i].pos.x;
			y = particulas[i].pos.y;
			z = particulas[i].pos.z;
			a = particulas[i].a;// + 0.4f;
			//if (a > 1.0f) a = 1.0f;
			glColor4f(particulas[i].r, particulas[i].g, particulas[i].b, a);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f); glVertex3f(x-size, y+size,z);
				glTexCoord2f(0.0f,1.0f); glVertex3f(x-size,y-size,z);
				glTexCoord2f(1.0f,1.0f); glVertex3f(x+ size,y-size,z);
				glTexCoord2f(1.0f,0.0f); glVertex3f(x+ size, y+size,z);
			glEnd();
		}
	glDisable(GL_BLEND);		
	glDisable(GL_TEXTURE_2D);
	glDisable( GL_POINT_SMOOTH );

}

void AVGSistPart::dibujaVBO()
{

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gltexture[0]);

	glEnable( GL_POINT_SMOOTH );
	glPointSize(fTamañoPunto);
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//Vertices
	if (bDrawQuads)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[2]);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(partQuads), partQuads);
	}
	else
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[0]);
		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(partPos), partPos);
	}
	glVertexPointer(3, GL_FLOAT, 0, 0);
	
	//Color
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboP[1]);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(partCol), partCol);
	if (bDrawQuads)
		glColorPointer(4, GL_FLOAT, 0, 0);
	else
		glColorPointer(4, GL_FLOAT,(GLsizei) (sizeof(float)*4*4), 0);

	//Dibuja
	if (bDrawQuads)
		glDrawArrays(GL_QUADS, 0, MAXPART);
	else	
		glDrawArrays(GL_POINTS, 0, MAXPART);
		
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
		
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDisable(GL_BLEND);									
	glDisable( GL_POINT_SMOOTH );
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();

}


int	AVGSistPart::añadeParticula (ofVec3f pos, ofVec3f vel)
{
	int iTmp = iParticulaActual;

	particulas[iTmp].setInitialCondition( pos, vel);
	particulas[iTmp].iNumParticula = iTmp; //Le paso a la particula su número (posicion dentro del array)
	particulas[iTmp].posIni = pos;

	if (partPerlin)
	{
		particulas[iTmp].bPerlin = true;
		particulas[iTmp].perlinSeed = ofRandom(1,5000);
	}
	else
		particulas[iTmp].bPerlin = false;

	//updateArray(iTmp);

	iParticulaActual++;
	
	//Limite variable para jugar con el máximo de particulas, que sea < MAXPART
	if ( (iParticulaActual >= MAXPART) || (iParticulaActual >= iLimiteParticulas))
		iParticulaActual = 0;
	
	return(iTmp);

}

void	AVGSistPart::eliminaParticula (int iNumParticula)
{
	particulas[iNumParticula].viva = false;
}




// load a 256x256 RGB .RAW file as a texture
GLuint AVGSistPart::LoadTexture(ofImage image)
{
	unsigned char* texturedata;
	
	texturedata = image.getPixels();
	
    GLuint texture;
	bool wrap = true;
	
    // allocate a texture name
    glGenTextures( 1, &texture );
	
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );
	
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
					wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
					wrap ? GL_REPEAT : GL_CLAMP );
	
    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image.width, image.height,
					  GL_RGB, GL_UNSIGNED_BYTE, texturedata );
	
    return texture;
}

void AVGSistPart::CargaTextura(string strArchivo, int iTextura)
{
	
	//Carga la textura para las particulas
	texture.loadImage(strArchivo);
	texture.setImageType(OF_IMAGE_COLOR);
	gltexture[iTextura] = LoadTexture(texture);

}

//Carga una imagen para utilzarla como mosaico para las particulas
// si width y height == 0, deja la foto en tamaño original
void AVGSistPart::cargaFotoMosaico(string strArchivo, ofVec2f pos, int width, int height)
{
	mosaico_params.fotoMosaico.loadImage(strArchivo);
	
	if (width != 0 && height !=0)
		mosaico_params.fotoMosaico.resize(width, height);
	
	mosaico_params.pos = pos;
	mosaico_params.width = mosaico_params.fotoMosaico.width;
	mosaico_params.height = mosaico_params.fotoMosaico.height;

}

//void AVGSistPart::setPartRangoColor(float r1, float r2, float g1, float g2, float b1, float b2)
//{
//	partR1 = r1;
//	partR2 = r2;
//
//	partG1 = g1;
//	partG2 = g2;
//
//	partB1 = b1;
//	partB2 = b2;
//}
//
//
//void AVGSistPart::setPartRangoVida(float ini, float fin)
//{
//	partVida1 = ini;
//	partVida2 = fin;
//}
//
//
//void AVGSistPart::setPartRangoAlpha( float ini1, float ini2, float fin1, float fin2)
//{
//	partAlphaIni1 = ini1;
//	partAlphaIni2 = ini2;
//
//	partAlphaFin1 = fin1;
//	partAlphaFin2 = fin2;
//}
//
//
//void AVGSistPart::setPartRangoSize(float s1, float s2)
//{
//	partSize1 = s1;
//	partSize2 = s2;
//}

/*
 These functions are for adding quads and triangles to an ofMesh -- either
 vertices, or texture coordinates.
 */
//--------------------------------------------------------------
void AVGSistPart::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
}

//--------------------------------------------------------------
void AVGSistPart::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

//--------------------------------------------------------------
void AVGSistPart::addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c) {
	mesh.addTexCoord(a);
	mesh.addTexCoord(b);
	mesh.addTexCoord(c);
}

//--------------------------------------------------------------
void AVGSistPart::addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d) {
	addTexCoords(mesh, a, b, c);
	addTexCoords(mesh, a, c, d);
}


