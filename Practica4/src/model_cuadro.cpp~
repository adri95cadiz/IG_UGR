#ifndef _cuadroCPP_
#define	_cuadroCPP_
#include "model_cuadro.h"

void cuadro::aplicarTextura(){
  if(imagen != NULL){

  }

}

void cuadro::initialize(int xx, int yy){
  alto = yy;
  ancho = xx;
  int version = 0;
  int x = xx+1;
  int y = yy+1;
  if(xx < 3) x = 4;
  if(yy < 3) y = 4;
  if(version == 0){
    //v1
    _vertices.resize(x*y);
    _caras.resize(xx*yy*2);
    for(int i = 0,k=0,t=0; i < x; i++){
      for(int j= 0; j < y; j++,k++){
        _vertices[k].x = i;
        _vertices[k].y = j;
        _vertices[k].z = 0.0;

        if(j != y-1 && i != x-1){
          _caras[t].x=k;
          _caras[t].y=k+1;
          _caras[t].z=k+y;
          t++;
          _caras[t].x=k+1;
          _caras[t].y=k+1+y;
          _caras[t].z=k+y;
          t++;

        }
      }
    }
  }
  else {
    //versión rateando puntos
    int tamanio = x*4+y*4-16;
    _vertices.resize(tamanio);
    tamanio = xx*yy*2-((xx-2)*(yy-2)*2);
    _caras.resize(tamanio);

    //indice vertices
    int k = 0;
    //indice caras
    int t = 0;
    //pilar 1
    for(int w = 0; w < 2; w++)
      for(int i = 0; i < y; i++,k++){
        _vertices[k].x = w;//cambiar si queremos centrar
        _vertices[k].y = i;//cambiar si queremos centrar
        _vertices[k].z = 0.0;
        if(w != 1 ){
          if(i != y-1){
            _caras[t].x=k;
            _caras[t].y=k+1;
            _caras[t].z=k+y;
            t++;
          }
          if(i > 0){
            _caras[t].x=k;
            _caras[t].y=k+y;
            _caras[t].z=k+y-1;
            t++;
          }
        }	
        else{
          if(i==0){
            _caras[t].x=k;
            _caras[t].y=k+1;
            _caras[t].z=k+y;
            t++;
            _caras[t].x=k+1;
            _caras[t].y=k+y;
            _caras[t].z=k+y+1;
            t++;

          }
          else if(i == y-2){
            _caras[t].x=k;
            _caras[t].y=k+1;
            _caras[t].z=k+4;
            t++;
            _caras[t].x=k+1;
            _caras[t].y=k+5;
            _caras[t].z=k+4;
            t++;

          }
        }

      }
    for(int i = 1; i < x-1;i++){
      for(int j = 0; j < 4; j++){
        if(i > 1 && i < (x-2)){
          _vertices[k].x = i;	
          _vertices[k].z = 0.0;
          if(j < 2) _vertices[k].y = j;
          else _vertices[k].y = y +j-4;

          if(j%2 == 0){
            _caras[t].x=k;
            _caras[t].y=k+1;
            if(i != x-3 || j == 0) _caras[t].z=k+4;
            else _caras[t].z=k+y;
            t++;

            _caras[t].x=k+1;
            if(i != x-3 || j == 0){
              _caras[t].y=k+4;
              _caras[t].z=k+5;
            }
            else{
              _caras[t].y=k+y;
              _caras[t].z=k+y+1;
            }
            t++;
          }


          k++;
          //	if(i < x-1 && j%2 != 0){
          //	    _caras[t].x=k;
          //            _caras[t].y=k+4;
          //            _caras[t].z=k+3;
          //		t++;
          //	}

        }

      }
    }

    //pilar 2 (casi igual que el 1)
    for(int w = x-2; w < x; w++)
      for(int i = 0; i < y; i++,k++){
        _vertices[k].x = w;
        _vertices[k].y = i;
        _vertices[k].z = 0.0;

        if(w != x-1 ){
          if(i != y-1){
            _caras[t].x=k;
            _caras[t].y=k+1;
            _caras[t].z=k+y;
            t++;
          }
          if(i > 0){
            _caras[t].x=k;
            _caras[t].y=k+y;
            _caras[t].z=k+y-1;
            t++;
          }
        }	
      }
  }

  //calcular coordenadas de textura
  //  calcularCoordenadasTextura(x,y);
  colocar_textura(x,y);



  generarNormales();
  setColor(1.0,0.2,0.7,1);
};

void cuadro::colocar_textura(int lados, int vperfil){
  lados = lados-2;
  vperfil = vperfil-2;
  vector<float> distancias;
  distancias.resize(vperfil);
  _texturas.resize(0);
  float x,y,z,xtext, ytext;
  distancias[0]=0.0;
  //jugamos con qe tienen la misma separacion, 1
  for(int i = 1; i < vperfil; i++){
    x = _vertices[i].x-_vertices[i-1].x;
    y = _vertices[i].y-_vertices[i-1].y;
    z = _vertices[i].z-_vertices[i-1].z;
    distancias[i] = distancias[i-1] + sqrt(x*x+y*y+z*z);
  } 
  for(int i = 0; i < lados; i++){
    for(int j = vperfil-1; j >-1; j--){
      xtext = ((float)i)/(lados-1);
      ytext =distancias[j]/distancias[vperfil-1];
      _texturas.push_back(_vertex2f(xtext,ytext));
    }
  }
}


void cuadro::dibujar(Model::DrawMode mode){
  if(mode == Model::SOLID || mode == Model::CHESS || mode == Model::FLAT || mode == Model::SMOOTH || mode == Model::ALL)
    dsolido();
  else
    draw(mode);

};

void cuadro::dsolido(){
  dbordes();
  dtextura();
};
void cuadro::dbordes(){
  glEnable(GL_COLOR_MATERIAL);
  glDisable(GL_TEXTURE_2D);

  int indice =alto*2+2;
  glBegin(GL_TRIANGLES);   
  for (int i=4;i<_caras.size();i++){
      if( i < 8 || i > 11){
      if(i % 2 == 0)
        glColor3f(0,0,0);
      else
        glColor3f(1,1,1);
      //glNormal3f(_normales_vertices[posv1].x, _normales_vertices[posv1].y, _normales_vertices[posv1].z);
      glVertex3fv((GLfloat *) &(_vertices[_caras[i].x]));
      glVertex3fv((GLfloat *) &(_vertices[_caras[i].y]));
      glVertex3fv((GLfloat *) &(_vertices[_caras[i].z]));
      }    
  }
  glEnd();

};
void cuadro::dtextura(){

  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glEnable(GL_TEXTURE_2D);
  glDisable(GL_COLOR_MATERIAL);

  glColor3f(_color.x,_color.y,_color.z);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);   


  bool hay_normales=_normales_vertices.size();
  int indice = 0;
  int indiceT=0;
  int pintada = 2;
  int auxi = 0;


    for(int i = indice; auxi < ancho-2; auxi++, i=i+5){

      dibujarCaras(i,i+pintada,hay_normales,indiceT);
      indiceT++;
    }

  glEnd();
  glDisable(GL_TEXTURE_2D);

};

void cuadro::dibujarCaras(int principio, int final, bool hay_normales, int & indiceT){
  for (int i=final-1;i>principio-1;i--){

    int posv1=i;//6
    int posv2=posv1+1;//7
    int posv3=posv2+alto;//11
    int posv4=posv3+1;//12
    ///////
    //Pintamos una cara del cuadrado
    ///////
    glTexCoord2f(_texturas[indiceT+1].x, _texturas[indiceT+1].y); 
    if (hay_normales)
      glNormal3f(_normales_vertices[posv1].x, _normales_vertices[posv1].y, _normales_vertices[posv1].z);
    //pintamos v1_      
    glVertex3f(_vertices[posv1].x, _vertices[posv1].y, _vertices[posv1].z);

    glTexCoord2f(_texturas[indiceT].x, _texturas[indiceT].y); 
    if (hay_normales)
      glNormal3f(_normales_vertices[posv2].x, _normales_vertices[posv2].y, _normales_vertices[posv2].z);
    //pintamos v2_
    glVertex3f(_vertices[posv2].x, _vertices[posv2].y, _vertices[posv2].z);

    glTexCoord2f(_texturas[indiceT+alto].x, _texturas[indiceT+alto].y);
    if (hay_normales)
      glNormal3f(_normales_vertices[posv3].x, _normales_vertices[posv3].y, _normales_vertices[posv3].z);
    //pintamos v3            
    glVertex3f(_vertices[posv3].x, _vertices[posv3].y, _vertices[posv3].z);
    ///////
    //Pintamos la otra cara del cuadrado
    ///////

    glTexCoord2f(_texturas[indiceT+alto].x, _texturas[indiceT+alto].y);
    if (hay_normales)
      glNormal3f(_normales_vertices[posv3].x, _normales_vertices[posv3].y, _normales_vertices[posv3].z);
    //pintamos v3            
    glVertex3f(_vertices[posv3].x, _vertices[posv3].y, _vertices[posv3].z);

    glTexCoord2f(_texturas[indiceT].x, _texturas[indiceT].y); 
    if (hay_normales)
      glNormal3f(_normales_vertices[posv2].x, _normales_vertices[posv2].y, _normales_vertices[posv2].z);
    //pintamos v2_      
    glVertex3f(_vertices[posv2].x, _vertices[posv2].y, _vertices[posv2].z);

    glTexCoord2f(_texturas[indiceT+alto-1].x, _texturas[indiceT+alto-1].y); 
    if (hay_normales)
      glNormal3f(_normales_vertices[posv4].x, _normales_vertices[posv4].y, _normales_vertices[posv4].z);
    //pintamos v4_
    glVertex3f(_vertices[posv4].x, _vertices[posv4].y, _vertices[posv4].z);
    indiceT++;
  }
}



#endif	










