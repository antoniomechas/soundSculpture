#ifndef PART_H
#define PART_H

#include "ofMain.h"
#define OF_ADDON_USING_OFXVECTORMATH
//#include "ofAddons.h"

#define TIPO_PARTICULA_MOSAICO 4

class part
{
    public:
        ofVec3f vel;
        ofVec3f frc;   // frc is also know as acceleration (newton says "f=ma")
		
		ofTrueTypeFont myFont;
		
        part();
		virtual ~part(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		void addRepulsionForce(part *p, float radius, float scale);
		void addAttractionForce(part *p, float radius, float scale);
		
		void addDampingForce();
        
		void setDamping(float fDamping);
		void setGravity(float fGravity);
		void setScreenLimits(float width, float height);

		void setColorRange(float r1, float r2, float g1, float g2, float b1, float b2);
		void setColorRange(ofColor ini, ofColor fin);
		void setInitialCondition(ofVec3f p, ofVec3f v);
        void update();
        void draw();

		void		setAlpha(float alphaIni, float alphaFin);
		void		setEndSize(float SizeIni, float SizeFin);
		void		setColor(float r, float g, float b);
		float		getR();
		float		getG();
		float		getB();
		float		getA();
		void		setPos(float x, float y);
		ofVec2f		getPos();

		void bounceOffWalls();
	
		void	ancla(float x, float y, float fuerza, float escala);
		void	updateArray();	//Actualiza el array de particulas

		bool	viva;
		int		temperatura;
		int		tipo;					//Tipo de particula
		float	size;
		float	size2;
		bool	bUseSize;
		float	r1, r2, g1, g2, b1, b2; //Rango de colores para ofRandom(r1,r2)
		int		clicksMuerte;			//Cuando llegue a estos clicks de vida, se muere la particula
		int		ivHoriz1, ivHoriz2;		//desplazamiento horizontal
		int		iTextura;				//Qué textura está utilizando la partícula
		int		iNumParticula;			//Que posicion tiene la particula en el array

		float*	_partPos;
		float*	_partCol;
		float*	_partQuads;
		float*	_partTex;
		float	r,g,b,a;
        ofVec3f pos;

		int		iEspecial;				// si es diferente de 0, significa que la particula esta en un estado especial, para dibujar un destello, etc.
		float	fPorcentajeEspecial;	// Para determinar el porcentaje de particulas que se vuelven especiales
		float	perlinSeed;
		bool	bPerlin;
		ofVec2f posIni;
		ofVec2f posFin;					// Establece la posición final a donde tiene que llegar la partícula
		float	multVelocidad;
		int		perlinRadio;

protected:

		float	a1,a2;			//Alpha
		float	s1,s2;			//Size
		int		clicksVida;		//Cuantos clicks de vida tiene la particula
		float	incAlpha;		//Incremento de alpha en cada click
		float	incSize;		//Incremento de size en cada click
		int		anclaX,anclaY;
		float	anclaF;
		float	damping;
		float	gravity;
		float	screenW;
		float	screenH;

private:
};

#endif // PART_H
