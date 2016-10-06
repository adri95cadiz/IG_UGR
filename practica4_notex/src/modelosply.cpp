 /******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * modelosply.cpp
 *
 ******************************************************************************/

 #include "modelosply.h"

 Modelo_Ply::Modelo_Ply(){

 }

 Modelo_Ply::Modelo_Ply(char* file)
 { 

	vector<double> vec_vertices;
    vector<unsigned long> vec_caras;

    // Obtenemos los vértices del fichero .ply
    _file_ply::read(file, vec_vertices, vec_caras);

    for (int i = 0; i < vec_vertices.size(); i+=3)
    {
        _vertex3f vert;
        vert.x = vec_vertices[i];
        vert.y = vec_vertices[i+1];
        vert.z = vec_vertices[i+2];

        vertices.push_back(_vertex3f(vert.x, vert.y, vert.z ));

    }

    for (int i = 0; i < vec_caras.size(); i+=3)
    {

        _vertex3i cara;
        cara._0 = vec_caras[i];
        cara._1 = vec_caras[i+1];
        cara._2 = vec_caras[i+2];

        caras.push_back(_vertex3i(cara._0, cara._1, cara._2 ));

    }

    this->generar_normales();

    //setVertices(vertices);
    //setFaces(caras);

 }