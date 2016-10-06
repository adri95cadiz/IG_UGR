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
 #include <iostream>
 #include <assert.h>
 #include <fstream>
 #include "jpg_imagen.hpp"

 class Modelo 
 {

	protected:

		vector<_vertex3f> vertices;
		vector<_vertex3i> caras;

		_vertex4f _color;  	// Informacion del color

		// Texturas
    	GLuint ident_textura;	   // 'nombre' o identif. de textura para OpenGL
		jpg::Imagen *imagen;       // objeto con los bytes de la imagen de textura

		vector<_vertex2f> texturas; // aqui hay que meter el sI y sj
		vector<_vertex3f> normales_caras;
		vector<_vertex3f> normales_vertices;


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
		void visualizar_plano();
		void visualizar_gouraud();
		void visualizar_todo();		
		void generar_normales();
		void generar_normales_caras();
		void generar_normales_vertices();
		void setVertices(vector<_vertex3f> vert);		
		void setCaras(vector<_vertex3i> car);
		void generar_por_revolucion(int n_div); 	// n_div: número de divisiones verticales del objeto 			
		void generar_cuerpo_revolucion(int n_div, float ang_ini, float ang_fin);	
		void generar_contorno_cerrado(int n_div);
		void calcular_coord_textura(int N, int M);	
		void loadImage(const string & nombreArchivoJPG);
		void setColor(float r, float g, float b, float alpha);


 };

 _vertex3f rotar(_vertex3f punto, float giro );
 double distancia(_vertex3f a, _vertex3f b);

 
 #endif
