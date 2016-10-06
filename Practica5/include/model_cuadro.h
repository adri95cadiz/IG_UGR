#ifndef _cuadroH_
#define	_cuadroH_
#include "model.h"

class cuadro : public Model{
private:
  int ancho, alto;
public:
  //xx e yy serán el número de cuadradados horizontales y verticales que marcarán el cuadro
  //x e y el número de vértices que representarán el cuadro
  //nos quedamos con la versión 0
  void initialize(int x, int y);
  void aplicarTextura();
  void dsolido();
  void dtextura();
  void dbordes();
  void dibujarCaras(int principio, int final,bool hay_normales,int  &indiceT);
  void colocar_textura(int x, int y);
  void dibujar(Model::DrawMode mode);
};

#endif	

