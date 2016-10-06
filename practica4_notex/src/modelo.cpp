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

Modelo::Modelo()
{
	imagen = NULL;
	_color = _vertex4f(0.0,0.0,0.0,1.0);
}

void Modelo::setColor(float r, float g, float b, float alpha)
{
	_color = _vertex4f(r, g, b, alpha);
}

void Modelo::loadImage(const string & nombreArchivoJPG)
{
    imagen = new jpg::Imagen(nombreArchivoJPG);
    //ident_textura = loadTexture(imagen);

    // usar con:
    // int tamx = imagen->tamX(); // num. columnas (unsigned)
    // int tamy = imagen->tamY(); // num. filas (unsigned)
    // unsigned char * texels = imagen->leerPixels(); // puntero texels (unsigned char *)

}

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
	 	case 4: //Iluminado plano.
	 		visualizar_plano();
	 		break;
	 	case 5: //Iluminado Gouraud.
	 		visualizar_gouraud();
	 		break;
		case 6: //Todo
			visualizar_todo();
			break;
	}	
}

void Modelo::visualizar_puntos()
{ 
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
	int Vertex_1,Vertex_2,Vertex_3;    

 	glBegin(GL_LINE_STRIP );

 	for(int i = 0; i<caras.size(); i++ )
 	{

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
	int Vertex_1,Vertex_2,Vertex_3;    

 	glBegin(GL_TRIANGLES );

 	for(int i = 0; i<caras.size(); i++ )
 	{

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

void Modelo::visualizar_plano()
{
	glShadeModel(GL_FLAT);
    if (imagen != NULL)
    {
        // Carga la imagen
        glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        glEnable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
    }
    else
    {
        glEnable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }


    glBegin(GL_TRIANGLES);

        for (int i = 0; i < caras.size(); i++)
        {
            int Vertex_1,Vertex_2,Vertex_3;

            Vertex_1 = caras[i].x;
            Vertex_2 = caras[i].y;
            Vertex_3 = caras[i].z;

            if (normales_caras.size() > 0)
                glNormal3f(normales_caras[i].x, normales_caras[i].y, normales_caras[i].z);

            if (texturas.size() > 0)
                glTexCoord2f(texturas[Vertex_1].x, texturas[Vertex_1].y);

            glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);

            if (texturas.size() > 0)
                glTexCoord2f(texturas[Vertex_2].x, texturas[Vertex_2].y);

            glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);

            if (texturas.size() > 0)
                glTexCoord2f(texturas[Vertex_3].x, texturas[Vertex_3].y);

            glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z);
        }

    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void Modelo::visualizar_gouraud()
{
	glShadeModel(GL_SMOOTH);
    if (imagen != NULL)
    {
        // Carga la imagen
        glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        glEnable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
    }
    else
    {
        glEnable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }


    glBegin(GL_TRIANGLES);

        for (int i= 0; i < caras.size(); i++)
        {
            int Vertex_1,Vertex_2,Vertex_3;

            Vertex_1 = caras[i].x;
            Vertex_2 = caras[i].y;
            Vertex_3 = caras[i].z;

            if (texturas.size() > 0)
                glTexCoord2f(texturas[Vertex_1].x, texturas[Vertex_1].y);

            if (normales_vertices.size() > 0)
                glNormal3f(normales_vertices[Vertex_1].x, normales_vertices[Vertex_1].y, normales_vertices[Vertex_1].z );

            glVertex3f(vertices[Vertex_1].x, vertices[Vertex_1].y, vertices[Vertex_1].z);

            if (texturas.size() > 0)
                glTexCoord2f(texturas[Vertex_2].x, texturas[Vertex_2].y);

            if (normales_vertices.size() > 0)
                glNormal3f(normales_vertices[Vertex_2].x, normales_vertices[Vertex_2].y, normales_vertices[Vertex_2].z );

            glVertex3f(vertices[Vertex_2].x, vertices[Vertex_2].y, vertices[Vertex_2].z);

            if (texturas.size() > 0)
                glTexCoord2f(texturas[Vertex_3].x, texturas[Vertex_3].y);

            if (normales_vertices.size() > 0)
                glNormal3f(normales_vertices[Vertex_3].x, normales_vertices[Vertex_3].y, normales_vertices[Vertex_3].z );

            glVertex3f(vertices[Vertex_3].x, vertices[Vertex_3].y, vertices[Vertex_3].z );
        }

    glEnd();

    glDisable(GL_TEXTURE_2D);

 }

 void Modelo::visualizar_todo()
 {
	glColor3f(1, 0, 0 ); //Rojo.
	visualizar(0);	
	glColor3f(0, 1, 0 ); //Verde.
	visualizar(1);
	glColor3f(0, 0, 1 ); //Azul.
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

    calcular_coord_textura(n_div, perfil.size());

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

    calcular_coord_textura(n_div, perfil.size());

 }

 double distancia(_vertex3f a, _vertex3f b)
 {
    double x = pow((b.x-a.x), 2);
    double y = pow((b.y-a.y), 2);
    double z = pow((b.z-a.z), 2);

    return sqrt((double)(x+y+z));
 }

 void Modelo::calcular_coord_textura(int N, int M)
 {

    int n_vertices = vertices.size();

    double d[M];    //vector de distancias
    d[0] = 0;

    for(unsigned int k=1; k<M; k++)
        d[k] = d[k-1] + distancia(vertices[k-1], vertices[k]);

    for(unsigned int i=0; i<N; i++)
    {
        for(unsigned int j=0; j<M; j++)
        {

            float si = (float)i/(N-1);

            float tj = d[j]/d[M-1];

            texturas.push_back(_vertex2f(si, tj));

        }
    }
 }

void Modelo::generar_normales()
{
    generar_normales_caras();
    generar_normales_vertices();

}


void Modelo::generar_normales_caras()
{
    for(int i = 0; i < caras.size(); i++)
    {

        _vertex3f A, B, C;
        A = vertices[caras[i].x];
        B = vertices[caras[i].y];
        C = vertices[caras[i].z];

        _vertex3f ab, bc, normal;

        ab.x = B.x - A.x;
        ab.y = B.y - A.y;
        ab.z = B.z - A.z;

        bc.x = C.x - B.x;
        bc.y = C.y - B.y;
        bc.z = C.z - B.z;

        // Calculamos el producto vectorial (https://es.wikipedia.org/wiki/Producto_vectorial)
        normal.x = ab.y * bc.z - ab.z * bc.y;
        normal.y = ab.z * bc.x - ab.x * bc.z;
        normal.z = ab.x * bc.y - ab.y * bc.x;

        float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/modulo;
        normal.y=normal.y/modulo;
        normal.z=normal.z/modulo;

        normales_caras.push_back(normal);

    }

}

void Modelo::generar_normales_vertices()
{

    // Recorremos los vertices
    for(int i = 0; i < vertices.size(); i++)
    {

        _vertex3f verticeactual = vertices[i];
        _vertex3f normal(0,0,0);

        // Recorremos las caras
        for(int h = 0; h < caras.size(); h++)
        {
            // Comprobamos si el vertice esta en otra cara (por la posicion)
            if (caras[h].x == i || caras[h].y == i || caras[h].z == i)
            {
            
                normal = _vertex3f(normal.x + normales_caras[h].x,
                                   normal.y + normales_caras[h].y,
                                   normal.z + normales_caras[h].z);
            }

        }

        float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/modulo;
        normal.y=normal.y/modulo;
        normal.z=normal.z/modulo;

        normales_vertices.push_back(normal);
    }

}

 



 

