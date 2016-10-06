/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * ---------------------------------------------
 *
 *  Cabeceras del codigo del modelo, funciona tanto en linux como en mac
 *
 ******************************************************************************/
#ifndef _MODEL_REVOLUTION_
#define _MODEL_REVOLUTION_

#include <model.h>

class Model_Revolution : public Model
{
private:


	float degreesToRadians(float degreeValue);
	_vertex3f rotateX(_vertex3f p, float alpha);
	_vertex3f rotateY(_vertex3f p, float alpha);
	_vertex3f rotateZ(_vertex3f p, float alpha);

	bool varDrawNormales;
	void drawNormales() const;


	void generarPorPerfil(vector<_vertex3f> perfil, int steps);
	void generarPerfilCerrado(vector<_vertex3f> perfil, int steps);

	void calcular_coord_textura(int N, int M);
	double distancia(_vertex3f a, _vertex3f b);

public:

	Model_Revolution(vector<_vertex3f> pefil, int steps);
	Model_Revolution(float radio, unsigned int anillos, unsigned int sectores);

	void draw(DrawMode mode = SOLID);

	void process_key(unsigned char Tecla);

};

#endif

