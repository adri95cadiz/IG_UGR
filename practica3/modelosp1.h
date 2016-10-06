 /******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * modelosp1.h
 *
 ******************************************************************************/

 #ifndef _MODELOS_P1_H_
 #define _MODELOS_P1_H_

 #include <GL/gl.h>
 #include <stdlib.h>
 #include <vector>
 #include "vertex.h"
 #include "modelo.h"

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