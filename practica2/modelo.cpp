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
		case 4: //Todo
			visualizar_todo();
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
	glColor3f(0, 1, 0 ); //Verde.

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

 void Modelo::visualizar_todo()
 {
	visualizar(0);
	visualizar(1);
	visualizar(2);
 }

 void Modelo::setVertices(vector<_vertex3f> vert)
 {
	vertices = vert;
 }

 void Modelo::setCaras(vector<_vertex3i> car)
 {
	caras = car;
 }


 _vertex3f rotar(_vertex3f punto, float giro )
 {
 	return _vertex3f(punto.x*cos((M_PI/180)*giro)-punto.z*sin((M_PI/180*giro)), punto.y, punto.x*sin((M_PI/180*giro))+punto.z*cos((M_PI/180*giro))); 	
 }

 void Modelo::generar_cuerpo_revolucion(int n_div, float ang_ini, float ang_fin)
 {	
 	vector<_vertex3f> perfil = vertices;
 	float giro = (ang_fin-ang_ini)/n_div;

	if(ang_ini > 0)
	{
 		vector<_vertex3f> primerPerfil(perfil.size());
		for( unsigned int i = 0; i < perfil.size(); i++)
		{
			primerPerfil[i] = rotar(perfil[i], ang_ini);
		}
		perfil = primerPerfil;	
		setVertices(perfil);
	}


 	//Generamos los vértices junto con el cuerpo.
 	for(int i = 0; i<n_div ; i++) 
 	{
 		vector<_vertex3f> siguientePerfil(perfil.size());

 		//Generamos los vértices del siguiente perfil rotando los del anterior.
 		for (unsigned int j = 0; j < perfil.size(); j++)
           		siguientePerfil[j] = rotar(perfil[j], giro);

		vertices.insert(vertices.end(), siguientePerfil.begin(), siguientePerfil.end() );

		unsigned int inicioPerfil, finPerfil;
		inicioPerfil = i * perfil.size();
		finPerfil = inicioPerfil + perfil.size();

		//Generamos las caras del perfil actual con respecto al siguiente.
		for (unsigned int j = inicioPerfil+1, k = finPerfil+1; j < finPerfil; j++, k++)
		{
		    caras.push_back(_vertex3i(j-1, k-1, k));
		    caras.push_back(_vertex3i(j-1, k,   j));
		}

		//Actualizamos el perfil con el siguiente para la siguiente iteración del bucle.
		perfil = siguientePerfil;
    }
}

 void Modelo::generar_por_revolucion(int n_div)
 {
 	caras.clear();
 	vector<_vertex3f> perfil = vertices;

 	//Llamamos a la función de generar cuerpo, que también generará los vértices.
 	generar_cuerpo_revolucion(n_div, 0, 360);

 	//Generamos tapa superior (si el perfil no tiene punto central superior).
    if (vertices.front().x)
    {
    	vertices.push_back(_vertex3f(0.0, vertices.front().y, 0.0));

        for (int i = 0; i < n_div; i++)
        {
            int perfilactual = i * perfil.size();
            int siguientePerfil = perfilactual + perfil.size();
            caras.push_back(_vertex3i(vertices.size()-1, siguientePerfil, perfilactual));
        }

    }

    //Generamos tapa inferior (si el perfil no tiene punto central inferior).
    if (vertices[perfil.size() - 1].x)
    {    	
        vertices.push_back(_vertex3f(0.0, vertices[perfil.size() - 1].y, 0.0));

        for (int i = 0; i < n_div; i++)
        {
            int perfilactual = (i+1) * perfil.size() -1;
            int siguientePerfil = perfilactual + perfil.size();
            caras.push_back(_vertex3i(vertices.size()-1, perfilactual,siguientePerfil)); 
        }

    }


 }

 void Modelo::generar_contorno_cerrado(int n_div)
 {
 	caras.clear();
 	vector<_vertex3f> perfil = vertices;

 	//Llamamos a la función de generar cuerpo, que también generará los vértices.
 	generar_cuerpo_revolucion(n_div, 0, 360);

    //Generamos cierre del perfil (si el perfil no tiene ambos puntos centrales).
    if (vertices.front().x || vertices[perfil.size() - 1].x)
    {
	    for (int i = 1; i < n_div; i++)
	    {
	        int perfilactual = i * perfil.size();            
	        int siguientePerfil = perfilactual + perfil.size();

	        if(siguientePerfil < vertices.size()) {
	            caras.push_back(_vertex3i(siguientePerfil-1, perfilactual-1, perfilactual));
	            caras.push_back(_vertex3i(siguientePerfil-1, perfilactual, siguientePerfil)); 
	        }

	    }	

    	caras.push_back(_vertex3i(0, vertices.size()-perfil.size()-1, perfil.size()-1));
    	caras.push_back(_vertex3i(perfil.size()-1, 0, perfil.size()));      		  
    }  

 }


 

