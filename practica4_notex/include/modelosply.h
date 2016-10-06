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


 #ifndef _MODEL_PLY_H_
 #define _MODEL_PLY_H_
 
 #include <GL/gl.h>
 #include <stdlib.h>
 #include <vector>
 #include "modelo.h"
 #include "file_ply_stl.hpp"

 class Modelo_Ply : public Modelo
 {

 protected:

 public:
	Modelo_Ply();
	Modelo_Ply(char * file);

 };

 #endif