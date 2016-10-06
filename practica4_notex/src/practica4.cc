//**************************************************************************
// Práctica 4
//
// Domingo Martin Perandres 2013-2016
//
// GPL
// 2015 - Adrián Portillo Sánchez
//
// practica4.cc
//
//**************************************************************************

#include <stdlib.h>
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include "modelo.h"
#include "modelosp1.h"
#include "modelosply.h"
#include "hormiga.h"

//ModoVis
unsigned modo = 4;
unsigned numModel = 0;
unsigned numPract = 4;
float mx = 0, my = 0, mz = 0;
float speed_patas = 1, speed_cuerpo = 1, speed_cabeza = 1, speed_antenas = 1, speed_luz = 0.1;
bool animar = false, muestra = false, animar_luz = false, luz = true, luz1 = true, luz2 = true;
GLfloat light_position[4] = {15.0, 0.0, 15.0, 1.0};


//Modelo utilizado
Hexaedro *hexaedro = NULL;
Tetraedro *tetraedro = NULL;
Cornetto *cornetto = NULL;
Cilindro *cilindro = NULL;
Donut *donut = NULL;
Esfera *esfera = NULL;
Plano *plano = NULL;
Modelo_Ply *modelo_ply = NULL;
Modelo_Ply *modelo_rev = NULL;
Modelo_Ply *beethoven = NULL;
Modelo_Ply *dodge = NULL;
Modelo_Ply *ant = NULL;
Hormiga *hormiga = NULL;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1920,UI_window_height=1080;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);

}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(mx,my,mz);
	//Pintamos el objeto que hayamos seleccionado dependiendo del modo.
	switch(numPract){		
		case 1: //Práctica 1
			switch(numModel){
				case 0: //Tetraedro
					tetraedro->visualizar(modo );
					break;

				case 1: //Cubo
					hexaedro->visualizar(modo );
					break;

				case 2: //Cono
					cornetto->visualizar(modo );
					break;

				case 3: //Cilindro
					cilindro->visualizar(modo );
					break;

				case 4: //Toroide
					donut->visualizar(modo );
					break;
				case 5: //Esfera
					esfera->visualizar(modo );
					break;
				case 6: //Plano
					plano->visualizar(modo );
					break;
				default: //Fin_ciclo
					numModel = 0;
					glutPostRedisplay();
					break;
			}	
			break;

		case 2: //Práctica 2.
			switch(numModel){
				case 0: //modelo cargado					
					modelo_ply->visualizar(modo );
					break;
				case 1: //dodge
					dodge->visualizar(modo );
					break;
				case 2: //hormiga
					ant->visualizar(modo );
					break;
				case 3: //beethoven
					beethoven->visualizar(modo );
					break;
				case 4: //modelo generado por revolución
					modelo_rev->visualizar(modo );
					break;
				default:	//Fin_ciclo				
					numModel = 0;
					glutPostRedisplay();
					break;
			}
			break;

		case 3: //Práctica 3: Hormiga animada.			
			hormiga->visualizar(modo, muestra );
			break;

		case 4: //Práctica 4: Iluminación y texturas.
			switch(numModel){
				case 0: //Beethoven.
					beethoven->visualizar(modo );
					break;
				case 1: //Planeta tierra.
					esfera->visualizar(modo );
					break;
				case 2: //Plano.
					plano->visualizar(modo );
					break;
				default:	//Fin_ciclo				
					numModel = 0;
					glutPostRedisplay();
					break;
			}
			break;
		
	}

}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

	clear_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();

}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}

void change_spotlight()
{

    GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	light_position[0] = light_position[0]*cos((M_PI/180)*speed_luz)-light_position[2]*sin((M_PI/180)*speed_luz);
	light_position[2] = light_position[0]*sin((M_PI/180)*speed_luz)+light_position[2]*cos((M_PI/180)*speed_luz);

	GLfloat spotlight_direction[3] = {-light_position[0], -light_position[1], -light_position[2] };

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spotlight_direction);

}



//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

	switch(toupper(Tecla1))
	{

		// Q sale.
		case 'Q':
			exit(0);
			break;

		// Práctica 1.
		case '1': 			
			mx = my = mz = 0;	
			numPract = 1;
			break;

		// Práctica 2.
		case '2':			
			mx = my = mz = 0;	
			numPract = 2;
			break;
		
		// Práctica 3.
		case '3':			
			mx = my = mz = 0;	
			numPract = 3;
			break;

		// Práctica 4.
		case '4':	
			mx = my = mz = 0;	
			numPract = 4;
			break;

		// Z activa la animación de la hormiga en la práctica 3.
		case 'Z':
			if(numPract == 3)
			{
				animar = !animar;
			} 
			break;

		// L activa o desactiva la luz.
		case 'L':
			luz = !luz;
			if(luz)
				glEnable(GL_LIGHTING);
			else
				glDisable(GL_LIGHTING);
			break;	

		// X activa o desactiva la luz 1.
		case 'X':
			luz1 = !luz1;
			if(luz1)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);
			break;

		// C activa o desactiva la luz 2.
		case 'C':
			luz2 = !luz2;
			if(luz2)
				glEnable(GL_LIGHT1);
			else
				glDisable(GL_LIGHT1);
			break;

		// V activa o desactiva la animación de la luz.
		case 'V':
			animar_luz = !animar_luz;
			break;

		// B/b Acelera/Decelera la velocidad de animación de la luz. 
		case 'B':
			if(Tecla1 == 'b')
				speed_luz -= 0.1;
			else
				speed_luz += 0.1;
			break;

		// Prácticas 1, 2, 4: N cambia el modelo a dibujar.
		case 'N':
			numModel++;
			cout << "Cambiado a modelo " << numModel;				
			break;

		// M cambia el modo de visualización de los objetos.
		case 'M':		 
			modo++;
			if(modo == 6)
				modo = 0;
			cout << "Cambiado a modo " << modo;
			break;

		// Mueve el objeto hacia atrás.
		case 'W':
			mz -= 0.1;			
			break;

		// Mueve el objeto hacia delante.
		case 'S':
			mz += 0.1;			
			break;

		// Mueve el objeto hacia delante.
		case 'A':
			mx -= 0.1;			
			break;

		case 'D':
			mx += 0.1;
			break;

		// Mueve el objeto hacia arriba.
		case 'E':
			my += 0.1; 
			break;

		// Mueve el objeto hacia abajo.
		case 'R':
			my -= 0.1;			
			break;

		// Vuelve a colocar el objeto en el centro.
		case 'F':
			mx = my = mz = 0;			
			break;

	}

	glutPostRedisplay();

}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

	switch (Tecla1){

		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;

	}

	glutPostRedisplay();

}

//***************************************************************************
// Funcion llamada siempre que no se produce ningún evento
//
// Generará los cambios en los parámetros animación en la práctica de
// jerarquía
//***************************************************************************

void animacion(void)
{
	if(animar_luz)
	{
		change_spotlight();
		glutPostRedisplay();
	}

	if(animar)
	{		
		hormiga->animar(speed_patas, speed_cuerpo, speed_cabeza, speed_antenas);
		
		glutPostRedisplay();
	}

}

//***************************************************************************
// Función que activa la iluminación
//***************************************************************************

void EnableLighting(void) {


	GLfloat light_ambient[] = { .5, .5, .5, 1.0 };
	GLfloat light_diffuse[] = { .9, .9, .9, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 20.0, 10.0, 30.0, 0.0 };
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	float shininess = 20;

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	GLfloat emision[] = {0.3, 0.3, 0.3, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);

	glEnable(GL_SMOOTH);     // enable smooth shading
	glEnable(GL_LIGHTING);   // enable lighting
	glEnable(GL_LIGHT0);     // enable light 0
	glEnable(GL_DEPTH_TEST);   //Activa el buffer de profundidad.
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	change_spotlight();


}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

	// se inicalizan la ventana y los planos de corte
	Window_width=1.6;
	Window_height=0.9;
	Front_plane=1;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(0,0,0,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	// Habilitamos la iluminación
	EnableLighting();
	//
	change_projection();
	//
	glViewport(0,0,UI_window_width,UI_window_height);

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

	//Inicialización de figuras.
	hexaedro = new Hexaedro(1);
	//hexaedro->loadImage("texturas/dia_8192.jpg");
	tetraedro = new Tetraedro(1);
	//tetraedro->loadImage("texturas/dia_8192.jpg");
	cornetto = new Cornetto(1, 0.5, 80);
	//cornetto->loadImage("texturas/dia_8192.jpg");
	cilindro = new Cilindro(1, 0.5, 120);
	//cilindro->loadImage("texturas/dia_8192.jpg");
	donut = new Donut(0.5, 0.5, 400);
	//donut->loadImage("texturas/dia_8192.jpg");
	esfera = new Esfera(0.5, 20, 40);
	//esfera->loadImage("texturas/estrellas_8192.jpg");
	plano = new Plano(1,1);
	//plano->loadImage("texturas/dia_8192.jpg");
	beethoven = new Modelo_Ply((char*)"modelos_ply/beethoven");
	dodge = new Modelo_Ply ((char*)"modelos_ply/big_dodge");
	ant = new Modelo_Ply((char*)"modelos_ply/ant");	
	hormiga = new Hormiga();	

	modelo_rev = new Modelo_Ply((char*)"modelos_ply/perfil");
	modelo_rev->generar_por_revolucion(15);
	modelo_rev->generar_normales();

	if(argc == 2)
		modelo_ply = new Modelo_Ply(argv[1]);
	else
		modelo_ply = new Modelo_Ply((char*)"modelos_ply/apple");

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Práctica 4");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);
	// asignación de la función llamada "animacion" al evento correspondiente
	glutIdleFunc(animacion);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;

}

