/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * Cabeceras del codigo del modelo, funciona tanto en linux como en mac
 *
 ******************************************************************************/
#ifndef _MODEL_
#define _MODEL_

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdlib.h> // pulls in declaration of malloc, free
#include <vector>
#include <math.h> // Librerias matemáticas

#include "jpg_imagen.hpp" // Librerias para texturas

#include <vertex.h>

using namespace std;

class Model
{

protected:

	vector<_vertex3f> _vertices;
	vector<_vertex3i> _caras;

	void setVertices(vector<_vertex3f> vertex);
    void setFaces(vector<_vertex3i> faces);

   	_vertex4f _color;  	// Informacion del color

	// Texturas
    GLuint ident_textura ;// 'nombre' o identif. de textura para OpenGL
	jpg::Imagen * imagen;       // objeto con los bytes de la imagen de textura



	vector<_vertex2f> _texturas; // aqui hay que meter el sI y sj
	vector<_vertex3f> _normales_vertices;
	vector<_vertex3f> _normales_caras;

public:

	Model()
	{
		x = 0;
		y = 0;
		z = 0;
		imagen = NULL;
		_color = _vertex4f(1.0,1.0,1.0,1.0);
	}

	void loadImage(const string & nombreArchivoJPG);

	void setColor(float r, float g, float b, float alpha)
	{
		_color = _vertex4f(r, g, b, alpha);
	}

	// Posicion central del objeto
	float x, y, z;
	void setCenter(float pX, float pY, float pZ)
	{
		x = pX;
		y = pY;
		z = pZ;
	};	

    void setNormalesCaras(vector<_vertex3f> normals);
    void setNormalesVertices(vector<_vertex3f> normals);

	void generarNormales();
	void generarNormalesCaras();
	void generarNormalesVertices();



	// Obtiene los vertices, se usa porque en determinados casos nos
	// pasamos los vertices de un modelo a otro (cargamos un ply y lo pasamos a uno de revolucion)
	vector<_vertex3f> getVertices(){ return _vertices; };

	enum DrawMode {
		POINTS, LINES, SOLID, CHESS, FLAT, SMOOTH, ALL
	};

	// Esta funcion pinta el modelo, como es virtual, es sobrecargable
	virtual void draw(DrawMode mode = SOLID);

	void draw_puntos();
	void draw_lineas();	
	void draw_solido(bool ajedrez);
	void draw_plano();
	void draw_gouraud();
	void draw_todo();	

	// Esta funcion procesa una letra en el modelo, sirve para extender el procesado
	// de teclas, de ahí que sea virtual
	virtual void process_key(unsigned char Tecla) {};

};

#endif
