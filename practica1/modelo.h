/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * modelo.h
 *
 ******************************************************************************/

 #ifndef _MODELO_H_
 #define _MODELO_H_

 #include <GL/gl.h>
 #include <stdlib.h>
 #include <vector>
 #include "vertex.h"

 class Modelo 
 {

	protected:

		vector<_vertex3f> vertices;
		vector<_vertex3i> caras;

	public:

		Modelo();

		/** modoVis:
		0 = PUNTOS
		1 = LINEAS
		2 = SOLIDO
		3 = AJEDREZ */

		void visualizar(unsigned modoVis );
		void visualizar_puntos();
		void visualizar_lineas();	
		void visualizar_solido(bool ajedrez);

 };

 class Tetraedro : public Modelo 
 {
	public:
		Tetraedro();
	 	Tetraedro(float size); //size: Tamaño del lado
 };

 class Hexaedro : public Modelo 
 {
	public:
	 	Hexaedro();
	 	Hexaedro(float size); //size: Tamaño del lado
 };

 class Cornetto : public Modelo 
 {
	public:
	 	Cornetto();
	 	Cornetto(float height, float rad, int caras); //height: altura, rad: radio. caras: Numero de caras (Para un correcto funcionamiento que sea divisible entre 2).
 };
 
 class Cilindro : public Modelo 
 {
	public:
	 	Cilindro();
	 	Cilindro(float height, float rad, int caras); //height: altura, rad: radio. caras: Numero de caras (Para un correcto funcionamiento que sea divisible entre 3).
 };

 
 class Donut : public Modelo 
 {
 	public:
	 	Donut();
	 	Donut(float rad, float thick, int caras); //rad: Tamaño del radio, thick: radio del grosor del toro. caras: Numero de caras (Para un correcto funcionamiento que sea un cuadrado perfecto).
 };
 

 #endif
