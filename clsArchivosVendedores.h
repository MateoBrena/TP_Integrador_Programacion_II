#ifndef CLSARCHIVOSVENDEDORES_H_INCLUDED
#define CLSARCHIVOSVENDEDORES_H_INCLUDED

#include "clsVendedor.h"

class ArchivoVendedores {
    private:
        char nombre[30];
    public:
        ArchivoVendedores(const char *n = "Vendedores.dat");
        Vendedor leerRegistro(int);
        bool grabarRegistro(Vendedor);
        bool modificarRegistro(Vendedor, int);
        int contarRegistros();
        int buscarRegistro(int);
        void listarRegistros();
        void altaVendedor();
        void buscarPorDni();
        void modificarNombre();
        void modificarApellido();
        void modificarFechaNacimiento();
        void modificarMail();
        void modifcarCategoria();
        void modificarDomicilio();
        void modificarFechaContratacion();
        void bajaVendedor();
};





#endif // CLSARCHIVOSVENDEDORES_H_INCLUDED
