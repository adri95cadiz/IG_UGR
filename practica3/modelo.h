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
		void visualizar_todo();
		void setVertices(vector<_vertex3f> vert);		
		void setCaras(vector<_vertex3i> car);
		void generar_por_revolucion(int n_div); 	// n_div: número de divisiones verticales del objeto 			
		void generar_cuerpo_revolucion(int n_div, float ang_ini, float ang_fin);	
		void generar_contorno_cerrado(int n_div);	

 };

 _vertex3f rotar(_vertex3f punto, float giro );

 #endif
