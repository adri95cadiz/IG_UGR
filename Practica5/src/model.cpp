/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 *
 ******************************************************************************/

#include <model.h>


void Model::loadImage(const string & nombreArchivoJPG)
{
    imagen = new jpg::Imagen(nombreArchivoJPG);


    // // usar con:
    // int tamx = imagen->tamX(); // num. columnas (unsigned)
    // int tamy = imagen->tamY(); // num. filas (unsigned)
    // unsigned char * texels = imagen->leerPixels(); // puntero texels (unsigned char *)


}

void Model::setVertices(vector<_vertex3f> vertex)
{
    _vertices = vertex;
}

void Model::setFaces(vector<_vertex3i> faces)
{
    _caras = faces;
}

void Model::draw(DrawMode modoVis ){

	switch(modoVis)
	{
	 	case Model::POINTS: //Puntos.
			draw_puntos();
	 		break;
	 	case Model::LINES: //Lineas.
			draw_lineas();
	 		break;
	 	case Model::SOLID: //Solido.
	 		draw_solido(false);
	 		break;
	 	case Model::CHESS: //Ajedrez.
	 		draw_solido(true);
	 		break;
	 	case Model::FLAT: //Iluminado plano.
	 		draw_plano();
	 		break;
	 	case Model::SMOOTH: //Iluminado Gouraud.
	 		draw_gouraud();
	 		break;
		case Model::ALL: //Todo
			draw_todo();
			break;
	}	
}

void Model::draw_puntos()
{ 
	glPointSize(2);

	glBegin(GL_POINTS );	
	for(int i = 0; i<_vertices.size(); i++ )
	{
		glVertex3f(_vertices[i].x, _vertices[i].y, _vertices[i].z);
	}
	glEnd();
}
	
void Model::draw_lineas()
{
	int Vertex_1,Vertex_2,Vertex_3;    

 	glBegin(GL_LINE_STRIP );

 	for(int i = 0; i<_caras.size(); i++ )
 	{

	 	Vertex_1 = _caras[i].x;
		Vertex_2 = _caras[i].y;
		Vertex_3 = _caras[i].z;

		glVertex3f(_vertices[Vertex_1].x, _vertices[Vertex_1].y, _vertices[Vertex_1].z);
		glVertex3f(_vertices[Vertex_2].x, _vertices[Vertex_2].y, _vertices[Vertex_2].z);
		glVertex3f(_vertices[Vertex_3].x, _vertices[Vertex_3].y, _vertices[Vertex_3].z);

	 } 	

 	glEnd(); 	

}

void Model::draw_solido(bool ajedrez)
{
	int Vertex_1,Vertex_2,Vertex_3;    

 	glBegin(GL_TRIANGLES );

    glColor3f(_color.x,_color.y,_color.z);

 	for(int i = 0; i<_caras.size(); i++ )
 	{

 		//Modo Ajedrez
 		if(ajedrez){
 			if(i%2 == 0 )
 				glColor3f(_color.x,_color.y,_color.z);
 			else
 				glColor3f(0, 0, 0 ); //Negro.
 		}
	 
	 	Vertex_1 = _caras[i].x;
		Vertex_2 = _caras[i].y;
		Vertex_3 = _caras[i].z;

		glVertex3f(_vertices[Vertex_1].x, _vertices[Vertex_1].y, _vertices[Vertex_1].z);
		glVertex3f(_vertices[Vertex_2].x, _vertices[Vertex_2].y, _vertices[Vertex_2].z);
	 	glVertex3f(_vertices[Vertex_3].x, _vertices[Vertex_3].y, _vertices[Vertex_3].z);

	} 	

 	glEnd(); 	

}

void Model::draw_plano()
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

        glColor3f(_color.x,_color.y,_color.z);

        for (int i = 0; i < _caras.size(); i++)
        {
            int Vertex_1,Vertex_2,Vertex_3;

            Vertex_1 = _caras[i].x;
            Vertex_2 = _caras[i].y;
            Vertex_3 = _caras[i].z;

            if (_normales_caras.size() > 0)
                glNormal3f(_normales_caras[i].x, _normales_caras[i].y, _normales_caras[i].z);

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_1].x, _texturas[Vertex_1].y);

            glVertex3f(_vertices[Vertex_1].x, _vertices[Vertex_1].y, _vertices[Vertex_1].z);

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_2].x, _texturas[Vertex_2].y);

            glVertex3f(_vertices[Vertex_2].x, _vertices[Vertex_2].y, _vertices[Vertex_2].z);

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_3].x, _texturas[Vertex_3].y);

            glVertex3f(_vertices[Vertex_3].x, _vertices[Vertex_3].y, _vertices[Vertex_3].z);
        }

    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void Model::draw_gouraud()
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

        glColor3f(_color.x,_color.y,_color.z);

        for (int i= 0; i < _caras.size(); i++)
        {
            int Vertex_1,Vertex_2,Vertex_3;

            Vertex_1 = _caras[i].x;
            Vertex_2 = _caras[i].y;
            Vertex_3 = _caras[i].z;

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_1].x, _texturas[Vertex_1].y);

            if (_normales_vertices.size() > 0)
                glNormal3f(_normales_vertices[Vertex_1].x, _normales_vertices[Vertex_1].y, _normales_vertices[Vertex_1].z );

            glVertex3f(_vertices[Vertex_1].x, _vertices[Vertex_1].y, _vertices[Vertex_1].z);

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_2].x, _texturas[Vertex_2].y);

            if (_normales_vertices.size() > 0)
                glNormal3f(_normales_vertices[Vertex_2].x, _normales_vertices[Vertex_2].y, _normales_vertices[Vertex_2].z );

            glVertex3f(_vertices[Vertex_2].x, _vertices[Vertex_2].y, _vertices[Vertex_2].z);

            if (_texturas.size() > 0)
                glTexCoord2f(_texturas[Vertex_3].x, _texturas[Vertex_3].y);

            if (_normales_vertices.size() > 0)
                glNormal3f(_normales_vertices[Vertex_3].x, _normales_vertices[Vertex_3].y, _normales_vertices[Vertex_3].z );

            glVertex3f(_vertices[Vertex_3].x, _vertices[Vertex_3].y, _vertices[Vertex_3].z );
        }

    glEnd();

    glDisable(GL_TEXTURE_2D);

 }

 void Model::draw_todo()
 {
	glColor3f(1, 0, 0 ); //Rojo.
	draw(Model::POINTS);	
	glColor3f(0, 1, 0 ); //Verde.
	draw(Model::LINES);
	glColor3f(0, 0, 1 ); //Azul.
	draw(Model::SOLID);
 }


GLenum getGLDrawMode(Model::DrawMode mode)
{
    GLenum draw_mode;

    switch (mode)
    {
        case Model::POINTS:
            draw_mode = GL_POINTS;
            break;
        case Model::LINES:
            draw_mode = GL_LINES;
            break;
        default: // SOLID & CHESS
            draw_mode = GL_TRIANGLES;
            break;
    }

    return draw_mode;
}

void Model::setNormalesCaras(vector<_vertex3f> normals)
{
    _normales_caras = normals;
}

void Model::setNormalesVertices(vector<_vertex3f> normals)
{
    _normales_vertices = normals;
}

void Model::trasladar(_vertex3f cen){
  for(int i = 0; i < _vertices.size(); i++){
    _vertices[i].x += cen.x;
    _vertices[i].y += cen.y;
    _vertices[i].z += cen.z;
  }
}

void Model::generarNormales()
{
    generarNormalesCaras();
    generarNormalesVertices();

}


void Model::generarNormalesCaras()
{
    for(int i = 0; i < _caras.size(); i++)
    {

        _vertex3f A, B, C;
        A = _vertices[_caras[i].x];
        B = _vertices[_caras[i].y];
        C = _vertices[_caras[i].z];

        _vertex3f ab, bc, normal;

        ab.x = B.x - A.x;
        ab.y = B.y - A.y;
        ab.z = B.z - A.z;

        bc.x = C.x - B.x;
        bc.y = C.y - B.y;
        bc.z = C.z - B.z;

        normal.x = ab.y * bc.z - ab.z * bc.y;
        normal.y = ab.z * bc.x - ab.x * bc.z;
        normal.z = ab.x * bc.y - ab.y * bc.x;

        float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/modulo;
        normal.y=normal.y/modulo;
        normal.z=normal.z/modulo;

        _normales_caras.push_back(normal);

    }

}

void Model::generarNormalesVertices()
{

    // Recorremos los vertices
    for(int i = 0; i < _vertices.size(); i++)
    {

        _vertex3f verticeactual = _vertices[i];
        _vertex3f normal(0,0,0);

        // Recorremos las caras
        for(int h = 0; h < _caras.size(); h++)
        {
            // Comprobamos si el vertice esta en otra cara (por la posicion)
            if (_caras[h].x == i || _caras[h].y == i || _caras[h].z == i)
            {
            
                normal = _vertex3f(normal.x + _normales_caras[h].x,
                                   normal.y + _normales_caras[h].y,
                                   normal.z + _normales_caras[h].z);
            }

        }

        float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
        normal.x=normal.x/modulo;
        normal.y=normal.y/modulo;
        normal.z=normal.z/modulo;

        _normales_vertices.push_back(normal);
    }

}

 
