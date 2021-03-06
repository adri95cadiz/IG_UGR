/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * ---------------------------------------------
 *
 *  2015 - Adrián Portillo Sánchez
 *
 *  Codigo del Model_Revolution
 *
 ******************************************************************************/

#include <model_revolution.h>
#include <math.h>

Model_Revolution::Model_Revolution(vector<_vertex3f> perfil, int steps)
{

    setColor(0,1,0,1);

    // Bandera de si queremos pintar o no las normales
    varDrawNormales = false;
    generarPorPerfil(perfil, steps);
    generarNormales();
}

_vertex3f rotar_afin(_vertex3f punto, _vertex3f centro, float giro )
 {
    return centro + _vertex3f((punto.x-centro.x)*cos((M_PI/180)*giro)-punto.y*sin((M_PI/180*giro)), (punto.x-centro.x)*sin((M_PI/180*giro))+punto.y*cos((M_PI/180*giro)), punto.z);     
 }

Model_Revolution::Model_Revolution(float radio, unsigned int anillos, unsigned int sectores)
{  
        vector<_vertex3f> vertices_esfera;

        // Bandera de si queremos pintar o no las normales
        varDrawNormales = false;
        float giro = 180/(anillos);
        int i;

        vertices_esfera.push_back(_vertex3f(0, -radio, 0)); //Inicio del giro.

        //Vertices del primer giro.     
        for(i = 0; i<anillos; i++)
            vertices_esfera.push_back(rotar_afin(vertices_esfera[i], _vertex3f(0, 0, 0 ) , -giro));

        generarPerfilCerrado(vertices_esfera, sectores);
        generarNormales();
}

void Model_Revolution::process_key(unsigned char Tecla)
{
    // Al pulsar la tecla activamos / desactivamos el pintado de las normales
    if (Tecla == 'l')
        varDrawNormales = !varDrawNormales;
}


void Model_Revolution::draw(DrawMode mode)
{
    // Lo primero, movemos el modelo al centro establecido mediante setCenter()
    glPushMatrix();
    glTranslatef(x, y, z);

    // Llamamos al método la clase base
    Model::draw(mode);

    // En caso de que hayamos activado la tecla de mostrar las normales
    // las pintamos
    if (varDrawNormales)
        drawNormales();

    glPopMatrix();

}


void Model_Revolution::drawNormales() const
{

    float t = 0.2;

    glPointSize(2);
    glColor3f(0, 0, 1);


    glBegin(GL_LINES);

        for (int i= 0; i < _vertices.size(); i++)
        {
            _vertex3f _1 = _vertices[i];
            _vertex3f _2;

            _2.x = _1.x + t * _normales_vertices[i].x;
            _2.y = _1.y + t * _normales_vertices[i].y;
            _2.z = _1.z + t * _normales_vertices[i].z;

            glVertex3f(_1.x, _1.y, _1.z);
            glVertex3f(_2.x, _2.y, _2.z);
        }

    glEnd();

}

void Model_Revolution::generarPorPerfil(vector<_vertex3f> perfil, int steps)
{
    double angle;
    vector<_vertex3i> caras;
    vector<_vertex3f> vertices(perfil);

    angle = (2.0*M_PI) / steps;

    // Generamos la parte principal

    for (int step = 0; step < steps; step++)
    {
        vector<_vertex3f> siguientePerfil(perfil.size());
        // Generamos los puntos rodaso
        for (unsigned int k = 0; k < perfil.size(); k++)
            siguientePerfil[k] = rotateY(perfil[k], angle);

        // Añadimos los vertices al final del vector
        vertices.insert(vertices.end(), siguientePerfil.begin(), siguientePerfil.end() );

        // Generamos las caras
        unsigned int inicioPerfil, finPerfil;
        inicioPerfil = step * perfil.size();
        finPerfil = inicioPerfil + perfil.size();

        for (unsigned int i = inicioPerfil+1, k = finPerfil+1; i < finPerfil; i++, k++)
        {
            caras.push_back(_vertex3i(i-1, k-1, k));
            caras.push_back(_vertex3i(i-1, k,   i));
        }

        perfil = siguientePerfil;

    }
    
    //Añadimos un perfil más para las texturas  
    vector<_vertex3f> siguientePerfil(perfil.size());
    for (unsigned int k = 0; k < perfil.size(); k++)
            siguientePerfil[k] = rotateY(perfil[k], angle);

        // Añadimos los vertices al final del vector
        vertices.insert(vertices.end(), siguientePerfil.begin(), siguientePerfil.end() );

    // Generamos las tapas

    // Generamos la tapa de abajo
    if (vertices.front().x )
    {
        // Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
        _vertex3f puntoCentral(0.0, vertices.front().y, 0.0);
        vertices.push_back(puntoCentral);

        for (int step = 0; step < steps; step++)
        {
            int perfilactual = step * perfil.size();
            int siguientePerfil = perfilactual + perfil.size();
            caras.push_back(_vertex3i(vertices.size()-1, siguientePerfil, perfilactual));

        }

    }

    // Generamos la tapa de arriba
    if (vertices[perfil.size() - 1].x )
    {

        // Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
        _vertex3f puntoCentral(0.0, vertices[perfil.size() - 1].y, 0.0);
        vertices.push_back(puntoCentral);

        for (int step = 0; step < steps; step++)
        {
            int perfilactual = (step+1) * perfil.size() -1;
            int siguientePerfil = perfilactual + perfil.size();
            caras.push_back(_vertex3i(vertices.size()-1, perfilactual,siguientePerfil)); // Hay que ponerlos al revés que en la otra tapa para que calcule bien las normales

        }

    }

    setVertices(vertices);
    setFaces(caras);

    // Calcular coordenadas de textura
    calcular_coord_textura(steps, perfil.size());

}

void Model_Revolution::generarPerfilCerrado(vector<_vertex3f> perfil, int steps)
{
    double angle;
    vector<_vertex3i> caras;
    vector<_vertex3f> vertices(perfil);

    angle = (2.0*M_PI) / steps;

    // Generamos la parte principal

    for (int step = 0; step < steps; step++)
    {
        vector<_vertex3f> siguientePerfil(perfil.size());
        // Generamos los puntos rodaso
        for (unsigned int k = 0; k < perfil.size(); k++)
            siguientePerfil[k] = rotateY(perfil[k], angle);

        // Añadimos los vertices al final del vector
        vertices.insert(vertices.end(), siguientePerfil.begin(), siguientePerfil.end() );

        // Generamos las caras
        unsigned int inicioPerfil, finPerfil;
        inicioPerfil = step * perfil.size();
        finPerfil = inicioPerfil + perfil.size();

        for (unsigned int i = inicioPerfil+1, k = finPerfil+1; i < finPerfil; i++, k++)
        {
            caras.push_back(_vertex3i(i-1, k-1, k));
            caras.push_back(_vertex3i(i-1, k,   i));
        }

        perfil = siguientePerfil;

    }
    
    //Añadimos un perfil más para las texturas  
    vector<_vertex3f> siguientePerfil(perfil.size());
    for (unsigned int k = 0; k < perfil.size(); k++)
            siguientePerfil[k] = rotateY(perfil[k], angle);

        // Añadimos los vertices al final del vector
        vertices.insert(vertices.end(), siguientePerfil.begin(), siguientePerfil.end() );

    setVertices(vertices);
    setFaces(caras);

    // Calcular coordenadas de textura
    calcular_coord_textura(steps, perfil.size());

}
//***************************************************************************************
// Funcion para generar y almacenar los coord. de textura (malla generada por revolucion)
//***************************************************************************************

// Donde N es el numero de rotaciones
void Model_Revolution::calcular_coord_textura(int N, int M)
{

    int n_vertices = _vertices.size();

    double d[M];    //vector de distancias
    d[0] = 0;

    for(unsigned int k=1; k<M; k++)
        d[k] = d[k-1] + distancia(_vertices[k-1], _vertices[k]);

    for(unsigned int i=0; i<N; i++)
    {
        for(unsigned int j=0; j<M; j++)
        {

            float si = (float)i/(N-1);

            float tj = d[j]/d[M-1];

            _texturas.push_back(_vertex2f(si, tj));

        }
    }
}

double Model_Revolution::distancia(_vertex3f a, _vertex3f b)
{
    double x = pow((b.x-a.x), 2);
    double y = pow((b.y-a.y), 2);
    double z = pow((b.z-a.z), 2);

    return sqrt((double)(x+y+z));
}



float Model_Revolution::degreesToRadians(float degreeValue)
{
    return degreeValue * M_PI / 180.0;
}

_vertex3f Model_Revolution::rotateX(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = p.x;
    point.y = cos(alpha) * p.y - sin(alpha) * p.z;
    point.z = sin(alpha) * p.y + cos(alpha) * p.z;

    return point;
}

_vertex3f Model_Revolution::rotateY(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = cos(alpha) * p.x + sin(alpha) * p.z;
    point.y = p.y;
    point.z = -sin(alpha) * p.x + cos(alpha) * p.z;

    return point;
}

_vertex3f Model_Revolution::rotateZ(_vertex3f p, float alpha)
{
    _vertex3f point;

    point.x = cos(alpha) * p.x - sin(alpha) * p.y;
    point.y = sin(alpha) * p.x + cos(alpha) * p.y;
    point.z = p.z;

    return point;
}
