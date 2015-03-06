#ifndef SISTPART_H
#define SISTPART_H

#include "Part.h"
#include "ofxGui.h"

#define NUM_TEX 10
#define MAXPART 50000

class AVGSistPart
{
    public:

		AVGSistPart(){};
		virtual ~AVGSistPart(){};

		part particulas[MAXPART];
		
		void	setup();
		void	resetForce();
		void	actualiza();
		void	inicializa();
		void	dibuja();
		int		añadeParticula (ofVec3f pos, ofVec3f vel);
		void	eliminaParticula (int iNumParticula);
		void	CargaTextura(string strArchivo, int iTextura = 0);
		void	cargaFotoMosaico(string strArchivo, ofVec2f pos, int width, int height);

		//void	setPartRangoColor(float r1, float r2, float g1, float g2, 
		//												float b1, float b2);			//  rango de color para las partículas
		//void	setPartRangoVida(float ini, float fin);									//  vida de las particulas
		//void	setPartRangoAlpha( float ini1, float ini2, float fin1, float fin2);		//  alpha inicial y final de las particulas
		//void	setPartRangoSize(float s1, float s2);									//  Tamaño inicial estará entre s1 y s2
		void	resetMosaico();															//  Pone el estado del mosaico a idle

		//void	setPartTamañoPunto(float t);											//  Especifica el tamaño del punto cuando se dibujan particulas como puntos


		//bool	LoadTexture(char *TexName, GLuint TexHandle);

		//Si no es 0, este número suplanta a MAXPARTICULAS
		int		iLimiteParticulas;
		bool	bUseVBO;
		bool	bDrawQuads;
		float	fTamañoPunto;
		float	fPorcentajeEspecial;

		//Para dibujar por arrays
		float	partPos[MAXPART][3];			//Array de posiciones
		float	partCol[MAXPART][16];			//Array de colores. Al LORO: son 4 * 4 puntos cada quad, en caso de puntos, el stride será 4 ?
		float	partTex[MAXPART][8];			//Array de texturas
		float	partQuads[MAXPART][12];			//Array de quads
		GLuint	vboP[4];
		
		//int						partLimiteParticulas;
		//bool					partColorAuto;
		//float					partR1, partG1, partB1;									//  Rango de colores para las partículas
		//float					partR2, partG2, partB2;									//  Rango de colores para las partículas
		//float					partAlphaIni1, partAlphaIni2;
		//float					partAlphaFin1, partAlphaFin2;
		//float					partVida1, partVida2;
		//float					partSize1, partSize2;
		//int						partTipo;
		//float					partFuerza, partEscala;
		//float					partMultiplicador;
		//float					partPorcentajeBrillo;
		//int						partPerlinRadioMin, partPerlinRadioMax;
		//int						partMosaicoVelIni, partMosaicoVelFin;
		bool					partPerlin;

		//Particulas
		ofxIntSlider		partTipo;
		ofxToggle			partColorAuto;
		ofxFloatSlider		partColorAutoDelay;
		ofxColorSlider		partColorIni;
		ofxColorSlider		partColorFin;
		ofxIntSlider		partVidaIni;
		ofxIntSlider		partVidaFin;
		ofxIntSlider		partSizeIni;
		ofxIntSlider		partSizeFin;
		ofxFloatSlider		partAlphaIni1;
		ofxFloatSlider		partAlphaFin1;
		ofxFloatSlider		partAlphaIni2;
		ofxFloatSlider		partAlphaFin2;
		ofxFloatSlider		partPorcentajeEspecial;
		//ofxIntSlider		partMosaicoVelIni;
		//ofxIntSlider		partMosaicoVelFin;
		ofxFloatSlider		partVelZ1;
		ofxFloatSlider		partVelZ2;
		ofxFloatSlider		partDamping;
		ofxFloatSlider		partGravedad;
		ofxToggle			partUseSound;
		ofxToggle			partUseSoundGlobal;
		ofxFloatSlider		partSoundMult;
		ofxFloatSlider		partSoundMax;

		//Particulas 2
		ofxIntSlider		part2Tipo;
		ofxToggle			part2ColorAuto;
		ofxFloatSlider		part2ColorAutoDelay;
		ofxIntSlider		part2Step;
		ofxColorSlider		part2ColorIni;
		ofxColorSlider		part2ColorFin;
		ofxIntSlider		part2VidaIni;
		ofxIntSlider		part2VidaFin;
		ofxIntSlider		part2SizeIni;
		ofxIntSlider		part2SizeFin;
		ofxFloatSlider		part2AlphaIni1;
		ofxFloatSlider		part2AlphaFin1;
		ofxFloatSlider		part2AlphaIni2;
		ofxFloatSlider		part2AlphaFin2;
		ofxFloatSlider		part2VelZ1;
		ofxFloatSlider		part2VelZ2;
		ofxFloatSlider		part2Damping;
		ofxFloatSlider		part2Gravedad;
		ofxFloatSlider		part2PorcentajeEspecial;
		ofxFloatSlider		part2MultiplicadorVel;
		ofxToggle			part2UseSound;
		ofxToggle			part2UseSoundGlobal;
		ofxFloatSlider		part2SoundMult;
		ofxFloatSlider		part2SoundMax;

		enum MODO
		{
			MODO_NORMAL,
			MODO_MOSAICO
		};
		MODO					modo;

protected:

		void	dibujaVBO();					//  Dibuja las particulas utilizando VBO
		void	dibujaEspeciales();				//	Dibuja las particulas especiales
		void	dibujaParticulas();

		// helper functions
		void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c);
		void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
		void addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c);
		void addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d);

		//Para las texturas
		//ofImage				texture;
		//GLuint	gltexture[NUM_TEX];
		//GLuint	LoadTexture(ofImage image);
		
		vector<ofTexture>		textures;

		int					iParticulaActual;

};


#endif // SISTPART_H