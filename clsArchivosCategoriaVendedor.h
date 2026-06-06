#ifndef CLSARCHIVOSCATEGORIAVENDEDOR_H_INCLUDED
#define CLSARCHIVOSCATEGORIAVENDEDOR_H_INCLUDED

#include "clsCategoriaVendedor.h"

class ArchivoCategorias {
    private:
        char nombre[30];
    public:
        ArchivoCategorias(const char *n = "Categorias.dat");
        CategoriaVendedor leerRegistro(int pos);
        bool grabarRegistro(CategoriaVendedor obj);
        bool modificarRegistro(CategoriaVendedor obj, int pos);
        int contarRegistros();
        int contarRegistrosActivos(int ca);
        int buscarRegistro(int d);
        int buscarRegistroxNombre(const char *n);
        int buscarRegistroxComision(float c);
        void listarRegistros();
        void altaCategoria();
        void listadoFiltrado(int *l, const int TAM);
        void buscarPorId();
        void buscarPorNombre();
        void buscarPorComision();
        void modificarDescripcion();
        void modificarComision();
        void bajaCategoria();
        ~ArchivoCategorias();
};

#endif // CLSARCHIVOSCATEGORIAS_H_INCLUDED


