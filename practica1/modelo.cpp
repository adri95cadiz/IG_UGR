/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * modelo.cpp
 *
 ******************************************************************************/

 #include "modelo.h"
 #include <math.h>

 Modelo::Modelo(){}

 void Modelo::visualizar(unsigned modoVis ){

	switch(modoVis)
	{
	 	case 0: //Puntos.
			visualizar_puntos();
	 		break;
	 	case 1: //Lineas.
			visualizar_lineas();
	 		break;
	 	case 2: //Solido.
	 		visualizar_solido(false);
	 		break;
	 	case 3: //Ajedrez.
	 		visualizar_solido(true);
	 		break;
	}	
 }

 void Modelo::visualizar_puntos()
 { 
		
    	glColor3f(0, 0, 0 );	
	glPointSize(2);

	glBegin(GL_POINTS );	
	for(int i = 0; i<vertices.size(); i++ )
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
 }
	
 void Modelo::visualizar_lineas()
 {
	glColor3f(0, 0, 1 );

	int Vertex_1,Vertex_2,Vertex_3;    

 	glBegin(GL_LINE_STRIP );

 	for(int i = 0; i<caras.size(); i++ ){
	 
	 	 Vertex_1 = caras[i].x;
		 Vertex_2 = caras[i].y;
		 Vertex_3 = caras[i].z;

		 glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);
		 glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);
		 glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z);

	 } 	

 	glEnd(); 	

 }

 void Modelo::visualizar_solido(bool ajedrez)
 {
	glColor3f(0, 1, 0 );

	int Vertex_1,Vertex_2,Vertex_3;    

 	glBegin(GL_TRIANGLES );

 	for(int i = 0; i<caras.size(); i++ ){

 		//Modo Ajedrez
 		if(ajedrez){
 			if(i%2 == 0 )
 				glColor3f(0, 0, 1 ); //Azul.
 			else
 				glColor3f(0, 0, 0 ); //Negro.
 		}
	 
	 	 Vertex_1 = caras[i].x;
		 Vertex_2 = caras[i].y;
		 Vertex_3 = caras[i].z;

		 glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);
		 glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);
		 glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z);

	 } 	

 	glEnd(); 	

 }

Tetraedro::Tetraedro(){}

 Tetraedro::Tetraedro(float size ){

 	//Vertices
 	vertices.push_back(_vertex3f(0, (size*(sqrt(6)/3))/2, 0 )); //Punta del tetraedro.
 	//Vertices de la base.
 	vertices.push_back(_vertex3f(-size/2, -(size*(sqrt(6)/3))/2, -size/3 ));
 	vertices.push_back(_vertex3f(size/2, -(size*(sqrt(6)/3))/2, -size/3 ));
 	vertices.push_back(_vertex3f(0, -(size*(sqrt(6)/3))/2, (2*size)/3 ));

 	//Caras
 	caras.push_back(_vertex3i(1, 2, 0 ));	
	caras.push_back(_vertex3i(3, 1, 0 ));
	caras.push_back(_vertex3i(2, 3, 0 ));
	caras.push_back(_vertex3i(1, 2, 3 )); //Base del tetraedro

 }

 Hexaedro::Hexaedro(){}

 Hexaedro::Hexaedro(float size ){

 	//Vertices inferiores.
 	vertices.push_back(_vertex3f(size/2, size/2, size/2)); 
 	vertices.push_back(_vertex3f(-size/2, size/2, size/2));
 	vertices.push_back(_vertex3f(-size/2, size/2, -size/2));
 	vertices.push_back(_vertex3f(size/2, size/2, -size/2));
 	 //Vertices superiores.
 	vertices.push_back(_vertex3f(size/2, -size/2, size/2));
 	vertices.push_back(_vertex3f(-size/2, -size/2, size/2));
 	vertices.push_back(_vertex3f(-size/2, -size/2, -size/2));
 	vertices.push_back(_vertex3f(size/2, -size/2, -size/2));

 	//Cara (0,1,4,5).
 	caras.push_back(_vertex3i(0, 4, 5 )); 
 	caras.push_back(_vertex3i(1, 0, 5 ));
 	//Cara (1,2,6,5).
 	caras.push_back(_vertex3i(1, 5, 6 )); 
 	caras.push_back(_vertex3i(2, 1, 6 ));
 	//Cara (2,3,7,6).
 	caras.push_back(_vertex3i(2, 6, 7 )); 
	caras.push_back(_vertex3i(3, 2, 7 ));
	//Cara (3,0,4,7).
	caras.push_back(_vertex3i(3, 7, 4 ));
	caras.push_back(_vertex3i(0, 3, 4 ));
	//Cara (0,1,2,3) (Inferior).
	caras.push_back(_vertex3i(0, 3, 1 ));
	caras.push_back(_vertex3i(3, 2, 1 ));
	//Cara (4,5,6,7) (Superior).
	caras.push_back(_vertex3i(5, 4, 7 )); 
	caras.push_back(_vertex3i(6, 5, 7 ));
 }

 _vertex3f rotar(_vertex3f punto, float giro ){
 	return _vertex3f(punto.x*cos((M_PI/180)*giro)-punto.z*sin((M_PI/180*giro)), punto.y, punto.x*sin((M_PI/180*giro))+punto.z*cos((M_PI/180*giro))); 	
 }

 Cornetto::Cornetto(){}

 Cornetto::Cornetto(float height, float rad, int n_caras){

 	int i, n_div = (n_caras / 2);
 	float giro = 360/(n_div);

 	//Vertices.
 	vertices.push_back(_vertex3f(0, height/2, 0)); //Punta del cono.
 	vertices.push_back(_vertex3f(0, -height/2, 0 )); //Centro de la base del cono.
 	
 	//Vertices de la circunferencia.
 	vertices.push_back(_vertex3f(rad, -height/2, 0 )); //Inicio del giro.
 	for(int i = 2; i<n_div+1; i++) 
 	{	
 		vertices.push_back(rotar(vertices[i], giro));
 	}

 	//Caras del cono.
 	for(i = 2; i<n_div+1; i++) 	
		caras.push_back(_vertex3i(i, 0, i+1 ));
 	
 	caras.push_back(_vertex3i(i, 1, 2 ));

 	//Caras de la base.
 	for(i = 2; i<n_div+1; i++)
		caras.push_back(_vertex3i(i+1, i, 1 ));
 	
 	caras.push_back(_vertex3i(2, i, 0 ));

 }

 Cilindro::Cilindro(){}

 Cilindro::Cilindro(float height, float rad, int n_caras){

 	int i, n_div = (n_caras / 3);
 	float giro = 360/(n_div);

 	//Vertices
 	vertices.push_back(_vertex3f(0, -height/2, 0 )); //Centro de la base inferior del cilindro.
 	vertices.push_back(_vertex3f(0, height/2, 0)); //Centro de la base superior del cilindro.
 	vertices.push_back(_vertex3f(rad, -height/2, 0 )); //Inicio del giro inferior.
 	vertices.push_back(_vertex3f(rad, height/2, 0)); //Inicio del giro superior.

 	//Vertices de las circunferencias (se van alternando inferior y superior por el orden en el que se han introducido en el vector).
 	for(i = 2; i<(n_div*2)+3; i++)  	
 		vertices.push_back(rotar(vertices[i], giro));
 	
 	//Caras de la superficie del cilindro.
 	for(i = 3; i<(n_div*2)+3; i+=2){
		caras.push_back(_vertex3i(i, i+1, i+2));		
		caras.push_back(_vertex3i(i+2, i+1, i+3));
 	}


	//Caras de la base inferior del cilindro.
 	for(i = 2; i<(n_div*2)+1; i+=2)
		caras.push_back(_vertex3i(i, 0, i+2));

	//Caras de la base superior del cilindro.
	for(i = 3; i<(n_div*2)+2; i+=2)
		caras.push_back(_vertex3i(i+2, i, 1));

 }

 _vertex3f rotar_afin(_vertex3f punto, _vertex3f centro, float giro ){
 	return centro + _vertex3f((punto.x-centro.x)*cos((M_PI/180)*giro)-punto.y*sin((M_PI/180*giro)), (punto.x-centro.x)*sin((M_PI/180*giro))+punto.y*cos((M_PI/180*giro)), punto.z); 	
 }

 
 Donut::Donut(){}

 Donut::Donut(float rad, float thick, int n_caras){

 	int i, n_div = (int) sqrt(n_caras);
 	float giro = 360/(n_div);

 	vertices.push_back(_vertex3f(rad, 0, 0 )); //Centro del giro.
 	vertices.push_back(_vertex3f(rad-thick, 0, 0)); //Inicio del giro.

 	//Vertices del primer giro. 	
 	for(i = 1; i<n_div; i++)
 		vertices.push_back(rotar_afin(vertices[i], vertices[0], giro));
 	
 	//Giramos esos vertices por todo el toroide para generar los vertices en su totalidad.
 	for(i = 1; i<n_div*(n_div)+1; i++){
 		vertices.push_back(rotar(vertices[i], giro));
 	}


 	//Caras del recorrido del toroide.
 	for(i = 1; i<n_div*(n_div); i++)
 	{
	 	if(i%n_div == 0)
	 	{ 			 
	 		caras.push_back(_vertex3i(i, i-n_div+1, i+n_div));	
	 		caras.push_back(_vertex3i(i+n_div, i+1, i-n_div+1));	
 		}
 		else
 		{
	 		caras.push_back(_vertex3i(i, i+n_div, i+1));
	 		caras.push_back(_vertex3i(i+n_div, i+n_div+1, i+1));
	 	}
 	}  

 	//Últimas caras.
 	caras.push_back(_vertex3i(i-n_div+1, n_div, i )); 
 	caras.push_back(_vertex3i(1, n_div, i-n_div+1 )); 	

 }
 

