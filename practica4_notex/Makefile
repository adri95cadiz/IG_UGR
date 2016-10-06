# fichero Makefile
#
# VARIABLES
BIN 	= bin
SRC 	= src
OBJ 	= obj
LIB 	= lib
INCLUDE = include

# Definición de compiladores
CXX = g++ -Ofast -Wno-write-strings
CC = gcc -Ofast

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
CFLAGS=    -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -Wno-deprecated
CXXFLAGS=  -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -Wno-deprecated

# banderas para el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcion o biblioteca que se desea enlazar.
LDFLAGS=  -ljpeg -lGLU -lGL -lglut -ljpeg

# Nombre del fichero ejecutable
TARGETS = practica4


# TODO (sin empaquetado)
all: clean $(TARGETS)

# COMPILACION

$(TARGETS):
	$(CXX) -o $@ $(SRC)/$@.cc $(CXXFLAGS) $(SRC)/file_ply_stl.cc $(SRC)/modelo.cpp $(SRC)/modelosp1.cpp $(SRC)/hormiga.cpp $(SRC)/modelosply.cpp $(SRC)/jpg_imagen.cpp $(SRC)/jpg_memsrc.cpp $(SRC)/jpg_readwrite.cpp $(LDFLAGS)


# DOCUMENTACION
# Genera la documentacion mediante doxygen en la carpeta doc
.PHONY: doc
doc:
	doxygen doc/doxys/Doxyfile

# EMPAQUETADO
# Genera el archivo .zip de la práctica mediante la linea de comandos
# Omite los archivos propios de MacOSX y coge el nombre del directorio como nombre
.PHONY: package
package: clean
	@echo "Empaquetando..."
	zip $(shell basename "$(CURDIR)")_Adrian_Portillo.zip -9 -r ./*


tgz: clean #REVISAR
	@echo "Empaquetando .tgz..."
	tar -zcvf $(TARGETS).tgz *

# LIMPEZA
# Limpia los archivos compilados, así como los archivos objeto y los paquetes zip
.PHONY: clean
clean:
	@echo "Limpiando..."
	@rm -f $(OBJ)/*\
		./practica4