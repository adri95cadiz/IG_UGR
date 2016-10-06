/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * hormiga.h
 *
 ******************************************************************************/

 #ifndef _HORMIGA_H_
 #define _HORMIGA_H_

 #include "modelosply.h"

 class CabezaHormiga
 {
 	protected:

 		Modelo_Ply *antena_hormiga=NULL; 
 		Modelo_Ply *colmillo_hormiga=NULL; 
 		Modelo_Ply *craneo_hormiga=NULL; 

 		float step1, step2;
 		bool up1, up2;

 	public:
 		CabezaHormiga();

 		void visualizar(unsigned modoVis);
 		void animar(float speed_antenas);
 };

 class CuerpoHormiga
 {
 	protected: 		
 		CabezaHormiga *cabeza_hormiga = NULL;
 		Modelo_Ply *torso_hormiga=NULL;
 		Modelo_Ply *cola_hormiga=NULL; 

 		float step1, step2, step3;
 		bool up1, up2, up3;

 	public:
 		CuerpoHormiga();

 		void visualizar(unsigned modoVis);
 		void animar(float speed_cuerpo, float speed_cabeza, float speed_antenas);
 }; 

 class PatasHormiga
 {
 	protected:
 		Modelo_Ply *pata_hormiga = NULL; 

 		float step;
 		bool up;

 	public:
 		PatasHormiga();

 		void visualizar(unsigned modoVis);
 		void animar(float speed_patas);
 };

 class Hormiga
 {
 	protected:
 		CuerpoHormiga *cuerpo_hormiga = NULL;
 		PatasHormiga *patas_hormiga = NULL; 

 		float step1, step2, x, y;
 		bool up1, up2;		

 	public:
 		Hormiga();

 		void visualizar(unsigned modoVis, bool muestra);
 		void animar(float speed_patas, float speed_cuerpo, float speed_cabeza, float speed_antenas);
 		void mover(float mx, float my);

 };

 #endif