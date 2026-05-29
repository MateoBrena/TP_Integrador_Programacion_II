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
        int buscarRegistro(int idCat);
        void listarRegistros();
        void altaCategoria();
        void buscarPorId();
        void modificarDescripcion();
        void modificarComision();
        void bajaCategoria();
};

#endif // CLSARCHIVOSCATEGORIAS_H_INCLUDED


