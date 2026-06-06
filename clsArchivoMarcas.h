#ifndef CLSARCHIVOMARCAS_H_INCLUDED
#define CLSARCHIVOMARCAS_H_INCLUDED

#include "clsMarca.h"

class ArchivoMarcas {
    private:
        char nombre[30];
    public:
        ArchivoMarcas(const char *n = "Marcas.dat");
        Marca leerRegistro(int);
        bool grabarRegistro(Marca);
        bool modificarRegistro(Marca, int);
        int contarRegistros();
        int contarRegistrosActivos(int ca);
        int buscarRegistro(int);
        int buscarRegistroxNombre(const char *n);
        void listarRegistros();
        void altaMarca();
        void listadoFiltrado(int *l, const int TAM);
        void buscarPorId();
        void buscarPorNombre();
        void buscarPorPais();
        void modificarNombre();
        void modificarPais();
        void bajaMarca();
        ~ArchivoMarcas();
};

#endif // CLSARCHIVOMARCAS_H_INCLUDED
