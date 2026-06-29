#ifndef CLSARCHIVOSVENDEDORES_H_INCLUDED
#define CLSARCHIVOSVENDEDORES_H_INCLUDED

#include "clsVendedor.h"

class ArchivoVendedores {
    private:
        char nombre[30];
    public:
        ArchivoVendedores(const char *n = "Vendedores.dat");
        Vendedor leerRegistro(int pos);
        bool grabarRegistro(Vendedor);
        bool modificarRegistro(Vendedor, int pos);
        int contarRegistros();
        int contarRegistrosActivos(int ca);
        int buscarRegistro(int d);
        int buscarRegistroxDNI(const char *d);
        void listarRegistros();
        void altaVendedor();
        void listadoFiltrado(int *l, const int TAM);
        void buscarPorId();
        void buscarPorDni();
        void buscarPorNombre();
        void buscarPorApellido();
        void buscarPorMail();
        void buscarPorFechaNac();
        void buscarPorFechaCont();
        void buscarPorCat();
        void modificarNombre();
        void modificarApellido();
        void modificarFechaNacimiento();
        void modificarMail();
        void modifcarCategoria();
        void modificarDomicilio();
        void modificarFechaContratacion();
        void bajaVendedor();
        ~ArchivoVendedores();
};





#endif // CLSARCHIVOSVENDEDORES_H_INCLUDED
