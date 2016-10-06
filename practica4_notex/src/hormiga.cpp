/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 *
 * hormiga.cpp
 *
 ******************************************************************************/

 #include "hormiga.h"

 GLfloat SimetriaZ[16] = {-1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

 /******************************************************************************
 *
 * CabezaHormiga
 *
 ******************************************************************************/

 CabezaHormiga::CabezaHormiga()
 {

 	step1 = step2 = 0;
 	up1 = up2 = true;

 	craneo_hormiga = new Modelo_Ply((char*)"modelos_ply/hormiga/cabeza");
 	craneo_hormiga->generar_normales();
 	antena_hormiga = new Modelo_Ply((char*)"modelos_ply/hormiga/antena");
 	antena_hormiga->generar_normales();
 	colmillo_hormiga = new Modelo_Ply((char*)"modelos_ply/hormiga/colmillo");
 	colmillo_hormiga->generar_normales();

 }

 void CabezaHormiga::visualizar(unsigned modoVis)
 {

 	glPushMatrix();  		
	 	glRotatef(-90,1,0,0);
	 	glColor3f(0.4, 0.4, 0.4);
	 	craneo_hormiga->visualizar(modoVis);
 	glPopMatrix();
	

 	glPushMatrix(); 	

		glRotatef(-90,1,0,0);			
 		glTranslatef(-0.05,-0.72,0.2);

 		glPushMatrix(); 
	 		glRotatef(step1,0,0,1);	
	 		glRotatef(step1,1,0,0);	
	 		glColor3f(0.3, 0.3, 0.3);
		 	antena_hormiga->visualizar(modoVis);
	 	glPopMatrix();

	 	glTranslatef(0.11,0,0);		

	 	glPushMatrix(); 
		 	glMultMatrixf(SimetriaZ);	
	 		glRotatef(step1,0,0,1);	
		 	glRotatef(step1,1,0,0);			 	
	 		glColor3f(0.3, 0.3, 0.3);
		 	antena_hormiga->visualizar(modoVis);
	 	glPopMatrix(); 

 	glPopMatrix();

 	glPushMatrix(); 		

	 	glRotatef(-90,1,0,0);
	 	glTranslatef(0.12,-0.77,0.08);

	 	glPushMatrix();
		 	glRotatef(step2,0,0,1);	
		 	colmillo_hormiga->visualizar(modoVis);
	 	glPopMatrix();

	 	glTranslatef(-0.225,0,0);

	 	glPushMatrix();
		 	glMultMatrixf(SimetriaZ);
		 	glRotatef(step2,0,0,1);	
		 	colmillo_hormiga->visualizar(modoVis);
	 	glPopMatrix();

 	glPopMatrix();

 }

 void CabezaHormiga::animar(float speed_antenas)
 {

 	if (step1 > 10 || step1 < -10)
 		up1 = !up1;

 	if(up1)
 		step1 = step1+0.015*speed_antenas;
 	else
 		step1 = step1-0.015*speed_antenas;


 	if (step2 > 5 || step2 < -5)
 		up2 = !up2;

 	if(up2)
 		step2 = step2+0.01*speed_antenas;
 	else
 		step2 = step2-0.01*speed_antenas;


 }

 /******************************************************************************
 *
 * CuerpoHormiga
 *
 ******************************************************************************/

 CuerpoHormiga::CuerpoHormiga()
 {

 	step1 = step2 = step3 = 0;
 	up1 = up2 = up3 = true;

 	cabeza_hormiga = new CabezaHormiga();
 	torso_hormiga = new Modelo_Ply((char*)"modelos_ply/hormiga/torso");
 	torso_hormiga->generar_normales();
 	cola_hormiga = new Modelo_Ply((char*)"modelos_ply/hormiga/cola");
 	cola_hormiga->generar_normales();

 }

 void CuerpoHormiga::visualizar(unsigned modoVis)
 {		


 	glPushMatrix();

		glRotatef(-step3,1,0,0);
		glRotatef(-step3,0,1,0);

	 	glPushMatrix();
		 	glTranslatef(0,0,0.93);
		 	glRotatef(step1,0,1,0);
			cabeza_hormiga->visualizar(modoVis);	
		glPopMatrix();

		glPushMatrix();		 	
		 	glRotatef(-90,1,0,0);		 	
	 		glColor3f(0.35, 0.35, 0.35);
			torso_hormiga->visualizar(modoVis);	
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-0.1,-0.74);		
		 	glScalef(1.1,1.1,1.1);
		 	glRotatef(-step2,1,0,0);
		 	glRotatef(-90,1,0,0);
	 		glColor3f(0.32, 0.32, 0.32);
			cola_hormiga->visualizar(modoVis);	
		glPopMatrix();

	glPopMatrix();

 }

 void CuerpoHormiga::animar(float speed_cuerpo, float speed_cabeza, float speed_antenas)
 {

 	cabeza_hormiga->animar(speed_antenas);

 	if (step1 > 10 || step1 < -10)
 		up1 = !up1;

 	if(up1)
 		step1 = step1+0.015*speed_cabeza;
 	else
 		step1 = step1-0.015*speed_cabeza;


 	if (step2 > 7 || step2 < -7)
 		up2 = !up2;

 	if(up2)
 		step2 = step2+0.01*speed_cabeza;
 	else
 		step2 = step2-0.01*speed_cabeza;

 	if (step3 > 1.5 || step3 < -1.5)
 		up3 = !up3;

 	if(up3)
 		step3 = step3+0.003*speed_cuerpo;
 	else
 		step3 = step3-0.003*speed_cuerpo;

 }

 /******************************************************************************
 *
 * PatasHormiga
 *
 ******************************************************************************/

 PatasHormiga::PatasHormiga()
 {

 	step = 1;
 	up = true;

	pata_hormiga = new Modelo_Ply((char*)"modelos_ply/hormiga/pata");
	pata_hormiga->generar_normales();
 }

 void PatasHormiga::visualizar(unsigned modoVis)
 {

 	glPushMatrix();

	 	glPushMatrix();
		 	glRotatef(step,0,0,1);
		 	glRotatef(-90,1,0,0);
		 	pata_hormiga->visualizar(modoVis);
	 	glPopMatrix();

	 	glPushMatrix();
	 		glTranslatef(0,0,-0.02);		
		 	glRotatef(135,0,1,0);
		 	glRotatef(step,0,0,1); 	
		 	glRotatef(-90,1,0,0);
		 	pata_hormiga->visualizar(modoVis);
	 	glPopMatrix();

	 	glPushMatrix();
	 		glTranslatef(0,0,0.02);
		 	glRotatef(225,0,1,0); 	
		 	glRotatef(step,0,0,1); 	
		 	glRotatef(-90,1,0,0);
		 	pata_hormiga->visualizar(modoVis);
	 	glPopMatrix();

 	glPopMatrix();

 }

 void PatasHormiga::animar(float speed_patas)
 {

 	if (step > 10 || step < 0)
 		up = !up;

 	if(up)
 		step = step+0.01*speed_patas;
 	else
 		step = step-0.01*speed_patas;

 }

 /******************************************************************************
 *
 * Hormiga
 *
 ******************************************************************************/

 Hormiga::Hormiga()
 {
 	x = y = 0;
 	step1 = 0;
 	step2 = 20;
 	up1 = up2 = true;

 	cuerpo_hormiga = new CuerpoHormiga();
 	patas_hormiga = new PatasHormiga();
 }

 void Hormiga::visualizar(unsigned modoVis, bool muestra)
 {

 	glPushMatrix();

 		glTranslatef(0,0.7,0);

 		glPushMatrix();
 			glRotatef(step1,0,1,0);
 			if(muestra)
	 			glColor3f(0, 0, 0.8);
	 		else
	 			glColor3f(0.35, 0.35, 0.35);
 			patas_hormiga->visualizar(modoVis);
 		glPopMatrix();

 		glPushMatrix();
 			glRotatef(step2,0,1,0);
	 		glMultMatrixf(SimetriaZ);
	 		glColor3f(0.8, 0, 0);
	 		if(muestra)
	 			glColor3f(0.8, 0, 0);
	 		else
	 			glColor3f(0.35, 0.35, 0.35);
	 		patas_hormiga->visualizar(modoVis);
 		glPopMatrix();	 	

	 	glPushMatrix();
	 		cuerpo_hormiga->visualizar(modoVis);
 		glPopMatrix();

 	glPopMatrix();
 }

 void Hormiga::animar(float speed_patas, float speed_cuerpo, float speed_cabeza, float speed_antenas)
 {

 	cuerpo_hormiga->animar(speed_cuerpo, speed_cabeza, speed_antenas);
 	patas_hormiga->animar(speed_patas);

 	if (step1 > 20 || step1 < -20)
 		up1 = !up1;

 	if(up1)
 		step1 = step1+0.04*speed_patas;
 	else
 		step1 = step1-0.04*speed_patas;

	if (step2 > 20 || step2 < -20)
	 	up2 = !up2;

	if(up2)
	 	step2 = step2+0.04*speed_patas;
	else
	 	step2 = step2-0.04*speed_patas;


 }


