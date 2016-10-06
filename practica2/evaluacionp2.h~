#ifndef _EV_P2_H
#define _EV_P2_H

#include "modelo.h"

vector<Modelo> crear_figuras_evaluacion()
{
	vector<Modelo> figura;
	Modelo fig;
	vector<_vertex3f> vertices;

	//figura0
	vertices.push_back(_vertex3f(0.5, 0.5, 0));
	vertices.push_back(_vertex3f(0.5, -0.5, 0));
	fig.setVertices(vertices);
	fig.generar_cuerpo_revolucion(15, 45, 120);
	figura.push_back(fig);

	//figura1
	vertices.clear();
	vertices.push_back(_vertex3f(1, 0.5, 0));
	vertices.push_back(_vertex3f(0.5, -0.5, 0));
	vertices.push_back(_vertex3f(0, -0.5, 0));
	fig.setVertices(vertices);
	fig.generar_cuerpo_revolucion(15, 45, 120);
	figura.push_back(fig);

	//figura2
	vertices.clear();
	vertices.push_back(_vertex3f(0, 0.5, 0));
	vertices.push_back(_vertex3f(0.5, 0.5, 0));
	vertices.push_back(_vertex3f(1, -0.5, 0));
	fig.setVertices(vertices);
	fig.generar_cuerpo_revolucion(15, 45, 120);
	figura.push_back(fig);

	//figura3
	vertices.clear();
	vertices.push_back(_vertex3f(0, 0.5, 0));
	vertices.push_back(_vertex3f(0.5, 0.5, 0));
	vertices.push_back(_vertex3f(0.5, -0.5, 0));
	vertices.push_back(_vertex3f(0, -0.5, 0));
	fig.setVertices(vertices);
	fig.generar_cuerpo_revolucion(15, 45, 120);
	figura.push_back(fig);

	//figura4
	vertices.clear();
	vertices.push_back(_vertex3f(0, 0.5, 0));
	vertices.push_back(_vertex3f(0.5, -0.5, 0));
	vertices.push_back(_vertex3f(0, -0.5, 0));
	fig.setVertices(vertices);
	fig.generar_cuerpo_revolucion(15, 45, 120);
	figura.push_back(fig);

	return figura;
}

#endif






	
