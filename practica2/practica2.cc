//**************************************************************************
// Práctica 2
//
// Domingo Martin Perandres 2013-2016
//
// GPL
// 2015 - Adrián Portillo Sánchez
//
// practica2.cc
//
//**************************************************************************

#include <stdlib.h>
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "modelo.h"
#include "modelosp1.h"
#include "modelosply.h"
#include "evaluacionp2.h"

//ModoVis
unsigned modo = 0;
unsigned numModel = 0;
unsigned numPract = 2;

//Modelo utilizado
Hexaedro *hexaedro=NULL;
Tetraedro *tetraedro=NULL;
Cornetto *cornetto=NULL;
Cilindro *cilindro=NULL;
Donut *donut=NULL;
Modelo_Ply *modelo_ply=NULL;
Modelo_Ply *modelo_rev=NULL;
Modelo_Ply *modelo_cont=NULL;
Modelo_Ply *beethoven=NULL;
Modelo_Ply *dodge=NULL;
Modelo_Ply *ant=NULL;
vector<Modelo> eval; 

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1800,UI_window_height=950;

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
				case 5: //Fin_ciclo
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
				case 5: //modelo generado por revolución con contorno cerrado
					modelo_cont->visualizar(modo );
					break;
				case 6:	//Fin_ciclo				
					numModel = 0;
					glutPostRedisplay();
					break;
			}
			break;

		case 99: //Práctica 2 evaluación.
			if(numModel == 5)
				numModel = 0;
			eval[numModel].visualizar(modo );
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

switch(toupper(Tecla1)){

	case 'Q':
		exit(0);
		break;

	case '1': 
		numPract = 1;
		break;

	case '2':
		numPract = 2;
		break;
	
	case 'E':
		numPract = 99;
		break;

	case 'M':
		modo++;
		if(modo == 5)
			modo = 0;
		cout << "Cambiado a modo " << modo;
		break;

	case 'N':
		numModel++;
		cout << "Cambiado a modelo " << numModel;		
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
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=0.5;
Window_height=0.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
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

	hexaedro = new Hexaedro(1);
	tetraedro = new Tetraedro(1);
	cornetto = new Cornetto(1, 0.5, 80);
	cilindro = new Cilindro(1, 0.5, 120);
	donut = new Donut(0.5, 1, 400);
	beethoven = new Modelo_Ply((char*)"modelos_ply/beethoven");
	dodge = new Modelo_Ply ((char*)"modelos_ply/big_dodge");
	ant = new Modelo_Ply((char*)"modelos_ply/ant");

	if(argc == 2)
		modelo_ply = new Modelo_Ply(argv[1]);
	else
		modelo_ply = new Modelo_Ply((char*)"modelos_ply/apple");

	modelo_rev = new Modelo_Ply((char*)"modelos_ply/perfil");
	modelo_rev->generar_por_revolucion(15);


	modelo_cont = new Modelo_Ply((char*)"modelos_ply/perfil_cerrado");
	modelo_cont->generar_contorno_cerrado(15);
	
	eval = crear_figuras_evaluacion();
	
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
glutCreateWindow("Práctica 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}

