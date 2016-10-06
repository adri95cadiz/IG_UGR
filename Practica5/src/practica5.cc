/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2015 - Adrián Portillo Sánchez
 * ---------------------------------------------
 *
 *  Práctica 4 - Iluminación y texturas
 *
 *  Permitimos la carga de ficheros PLY así como la creación fija de un cubo y
 *  una pirámide, se permite el cambio de modo de visualización con las teclas
 *  1 = Puntos | 2 = Alambre | 3 = Solido | 4 = Ajedrez
 *
 *
 ******************************************************************************/

#include <stdlib.h> // pulls in declaration of malloc, free
#include "stdio.h"
#include <iostream>
#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include <ctype.h>

#include <model_cube.h>
#include <model_pyramid.h>
#include <model_ply.h>
#include <model_revolution.h>
#include <model_cuadro.h>
#include <values.h>
#include <camara.h>


// Atributos
int modo = 5, modelView = 1, numMaterial = 0;  // Aqui almacenaremos el modo de visualización y la figura a  ver.

Model * model [9];

bool animar_luz = false, luz = false, luz1 = false, luz2 = false;
float pos_tierra = 0.0, pos_luna = 0.0;
float mx = 0, my = 0, mz = 0;
GLfloat light_position[4] = {15.0, 0.0, 15.0, 1.0};
int camaraActiva=0, n_obser=2;
Camara *camaras;


// Model * model2 = new Model(); // Aqui guardamos la figura cargada


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

bool pulsado_derecho=false, pulsado_izquierda=false;

_vertex2f angles;

int valor=4, gl=-1, ObjetoSel=0;
unsigned zoom=5;

bool model_color_orig[9] = {true};

int yant=0, xant=0;

GLfloat Window_width,Window_height,Front_plane,Back_plane;
// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1400,UI_window_height=1000;


#define MAXNAMES 256

typedef struct
{
  int nnms;             // Número de identificadores del objeto
  int nms[MAXNAMES];    // Vector con las identificadores
  float zmin;
  float zmax;
} OBJ;

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

void projection(){
	if(camaras[camaraActiva].cenital){
		//cout<<"cenitaaaaal!!"<<endl;
		float zoom=camaras[camaraActiva].Observer_distance*0.1;
		glOrtho(zoom * -Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width , zoom * Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width, zoom * -Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height, zoom * Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height,Front_plane,Back_plane);
	}
	else{
		glFrustum(-Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width , Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width, -Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height, Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height,Front_plane,Back_plane);

	}

}
void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	projection();
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camaras[camaraActiva].setObservador();
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
	Model::DrawMode mode;
	// Pintamos el objeto seleccionado dependiendo del modo
	switch (modo)
	{
		case 1: //Puntos
			mode = Model::POINTS;
			break;
		case 2: //Aristas
			mode = Model::LINES;
			break;
		case 3: //Solido
			mode = Model::SOLID;
			break;
		case 4: //Ajedrez
			mode = Model::CHESS;
			break;
		case 5: //Suavizado Plano
			mode = Model::FLAT;
			break;
		case 6: //Suavizado Gouraud
			mode = Model::SMOOTH;
			break;
		case 7: //TODO
			mode = Model::ALL;
			break;
		default:
			modo = 1;
	}

	glPushMatrix();
		glLoadName(0);
		model[0]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(1);
		model[1]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(2);
		model[2]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(3);
		model[3]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(4);
		model[4]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(5);
		model[5]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(6);
		model[6]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(7);
		model[7]->draw(mode);
	glPopMatrix();

	glPushMatrix();
		glLoadName(8);
		model[8]->draw(mode);
	glPopMatrix();

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

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
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

	switch (Tecla1)
	{
		case 'q':
			exit(0);	

		// Z activa o desactiva la luz.
		case 'z':
			luz = !luz;
			if(luz)
				glEnable(GL_LIGHTING);
			else
				glDisable(GL_LIGHTING);
			break;	

		// X activa o desactiva la luz 1.
		case 'x':
			luz1 = !luz1;
			if(luz1)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);
			break;

		// C activa o desactiva la luz 2.
		case 'c':
			luz2 = !luz2;
			if(luz2)
				glEnable(GL_LIGHT1);
			else
				glDisable(GL_LIGHT1);
			break;

		// V activa o desactiva la animación de la luz.
		case 'v':
			animar_luz = !animar_luz;
			break;

		//Cambia el modo de visualización.
		case 'n': 
			camaraActiva++;
			if(camaraActiva == n_obser)
				camaraActiva = 0;

			change_observer();

			break;

		//Cambia el modo de visualización.
		case 'm': 
			modo++;
			break;

		// Mueve el objeto hacia atrás.
		/*case 'w':
			mz -= 0.1;			
			break;

		// Mueve el objeto hacia delante.
		case 's':
			mz += 0.1;			
			break;

		// Mueve el objeto hacia delante.
		case 'a':
			mx -= 0.1;			
			break;

		case 'd':
			mx += 0.1;
			break;

		// Mueve el objeto hacia arriba.
		case 'e':
			my += 0.1; 
			break;

		// Mueve el objeto hacia abajo.
		case 'r':
			my -= 0.1;			
			break;

		// Vuelve a colocar el objeto en el centro.
		case 'f':
			mx = my = mz = 0;			
			break;*/

		case 'a':camaras[camaraActiva].Observer_angle_y--;break;
		case 'd':camaras[camaraActiva].Observer_angle_y++;break;
		case 'w':camaras[camaraActiva].Observer_angle_x--;break;
		case 's':camaras[camaraActiva].Observer_angle_x++;break;

		case GLUT_KEY_PAGE_UP:
			camaras[camaraActiva].Observer_distance=zoom*Front_plane+ Front_plane*2;
			camaras[camaraActiva].Observer_angle_x=0;
			camaras[camaraActiva].Observer_angle_y=0;
		break;
		case GLUT_KEY_PAGE_DOWN:
			camaras[camaraActiva].Observer_distance=zoom*Front_plane - Front_plane*2;
			camaras[camaraActiva].Observer_angle_x=0;
			camaras[camaraActiva].Observer_angle_y=0;
		break;


	}

	change_projection();
	// Repintamos
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

	switch (Tecla1)	{
		case GLUT_KEY_LEFT:camaras[camaraActiva].Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:camaras[camaraActiva].Observer_angle_y++;break;
		case GLUT_KEY_UP:camaras[camaraActiva].Observer_angle_x--;break;
		case GLUT_KEY_DOWN:camaras[camaraActiva].Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:camaras[camaraActiva].Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:camaras[camaraActiva].Observer_distance/=1.2;break;
	}
	change_projection();
	gl=-1;
	glutPostRedisplay();
}

void change_spotlight()
{

    GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	light_position[0] = light_position[0]*cos((M_PI/180))-light_position[2]*sin((M_PI/180));
	light_position[2] = light_position[0]*sin((M_PI/180))+light_position[2]*cos((M_PI/180));

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
// Activa la iluminación (light 0)
//***************************************************************************
void EnableLighting(void) {


	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 20.0, 10.0, 30.0, 1.0 };
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	float shininess = 20;

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
/*
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);



	GLfloat emision[] = {0.3, 0.3, 0.3, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
*/
	glEnable(GL_SMOOTH);     // enable smooth shading
	glEnable(GL_LIGHTING);   // enable lighting
	glEnable(GL_LIGHT0);     // enable light 0
	glEnable(GL_DEPTH_TEST);   //Activa el buffer de profundidad.
	glShadeModel(GL_SMOOTH);


	//change_spotlight();
}


void animacion(void)
{
	if(animar_luz)
	{
		pos_tierra += 1;
		pos_luna += 1;
		change_spotlight();
		glutPostRedisplay();
	}
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************
void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Window_width=1;
	Window_height=1;
	Front_plane=1;
	Back_plane=1000;
	
	// se inicia la posicion del observador, en el eje z
	camaras[camaraActiva].Observer_distance=zoom*Front_plane;
	camaras[camaraActiva].Observer_angle_x=0;
	camaras[camaraActiva].Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);

	// Activamos la iluminacion
  	EnableLighting();

	change_projection();
	glViewport(0,0,UI_window_width,UI_window_height);

}

/*void seleccionarFigura(int i){
  cout << "Se ha seleccionado el beethoven " << i<<endl;
  for(i=0; i<9; i++){
  	model[i]->setColor(0,0,1,1);
  }
  switch(i){
  case 0: 
    model[0]->setColor(1,0,0,1); 
    break;
  case 1: 
    model[1]->setColor(1,0,0,1);  
    break;
  case 2: 
    model[2]->setColor(1,0,0,1);  
    break;
  case 3: 
    model[3]->setColor(1,0,0,1);  
    break;
  case 4: 
    model[4]->setColor(1,0,0,1);  
    break;
  case 5: 
    model[5]->setColor(1,0,0,1);  
    break;
  case 6: 
    model[6]->setColor(1,0,0,1);  
    break;
  case 7: 
    model[7]->setColor(1,0,0,1);  
    break;
  case 8: 
    model[8]->setColor(1,0,0,1);  
    break;
  default: 
    cerr << "ERROR EN LA SELECCION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl; 
    break;
  }

}*/

void procesar_hits(GLint hits, GLuint *names)
{
	//...
	// mostrar contenido de la pila
	cout << "Hits: " << hits << endl;

	for (int i = 0; i < hits; i++)
	{
		cout << "Numero: " << names[i * 4] << endl;

		cout << "Min Z: " << names[i * 4 + 1] << endl;
		cout << "Max Z: " << names[i * 4 + 2] << endl;
		cout << "Nombre en la pila: " << names[i * 4 + 3] << endl;
	}

	cout << endl;

	if (hits > 0)
	{

	//seleccionarFigura(names[3]);

		for(unsigned i = 0; i < 9; i++)
		{		
			if (names[i+3] == i)
			{
				if (model_color_orig[i])
				{
					model[i]->setColor(1,0,0,1);
					model_color_orig[i] = false;
				}
				else
				{
					model[i]->setColor(0,0,1,1);
					model_color_orig[i] = true;
				}

			}
		//glColor3f(0,0,1);
		
		}

	}

	// switch (names[0+3])
	// {
	// 	case 1:
	// 	{
	// 		cout << "hola" << endl;
	// 		glColor3f(0,0,1);
	// 		break;
	// 	}
	// }
	//....
	// procesar el cambio de color
	//...

}

int pick( int x, int y){

	cout << "PICK x=" << x << ",y=" << y << endl;

	GLuint selectBuf[100]={0};
	GLint viewport[4], hits=0;

	// Declarar buffer de selección
	glSelectBuffer(100, selectBuf);

	// Obtener los parámetros del viewport
	glGetIntegerv (GL_VIEWPORT, viewport);

	// Pasar OpenGL a modo selección
	glRenderMode (GL_SELECT);
	glInitNames();
	glPushName(0);

	// Fijar la transformación de proyección para la selección
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix(x,(viewport[3] - y),5.0, 5.0, viewport);
	float ratio =  UI_window_width * 1.0 / UI_window_height;
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

	// Dibujar la escena
	draw_scene();

	// Pasar OpenGL a modo render
	hits = glRenderMode (GL_RENDER);

	// Restablecer la transformación de proyección
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, UI_window_width, UI_window_height);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Procesar el contenido del buffer de selección
	procesar_hits(hits, selectBuf);

	// Dibujar la escena para actualizar cambios
	draw_scene();
}

void moveMouse(int x, int y)
{
	if(pulsado_derecho){
		camaras[camaraActiva].Observer_angle_y=x+xant;
		camaras[camaraActiva].Observer_angle_x=y+yant;
		yant= y;
		xant=x;
	}
	glutPostRedisplay();
}

void mouseClick( int button, int state, int x, int y )
{
	if(button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_DOWN){
			pick(x,y);
			pulsado_derecho=true;
		}
	}
	else
	{
		if(button == GLUT_LEFT_BUTTON){
			if(state == GLUT_DOWN){
				pulsado_derecho=false;
				pick(x,y);
			}
		}
		else
		{
			if(button == 3)
				camaras[camaraActiva].Observer_distance/=1.2;
			else if(button==4)
				camaras[camaraActiva].Observer_distance*=1.2;
			pulsado_derecho=false;
		}
	}
	glutPostRedisplay();
}



//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//
//***************************************************************************

int main(int argc, char **argv)
{

	camaras=new Camara[n_obser];
	camaras[1].cenital=true;

	for(unsigned i = 0; i<9; i++)
	{
		model[i] = new Model_Ply("data/beethoven.ply");
	}
	model[0]->trasladar(_vertex3f(-10, 0, -10));
	model[1]->trasladar(_vertex3f(-10, 0, 0));
	model[2]->trasladar(_vertex3f(-10, 0, 10));
	model[3]->trasladar(_vertex3f(0, 0, -10));
	model[4]->trasladar(_vertex3f(0, 0, 0));
	model[5]->trasladar(_vertex3f(0, 0, 10));
	model[6]->trasladar(_vertex3f(10, 0, -10));
	model[7]->trasladar(_vertex3f(10, 0, 0));
	model[8]->trasladar(_vertex3f(10, 0, 10));

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
	glutCreateWindow("Informatica Grafica");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(changeSize);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);
	// asignación de la función llamada "animacion" al evento correspondiente
	glutIdleFunc(animacion);

	//Funciones de ratón
	glutMouseFunc(mouseClick);
	glutMotionFunc(moveMouse);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
