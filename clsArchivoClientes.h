#ifndef CLSARCHIVOCLIENTES_H_INCLUDED
#define CLSARCHIVOCLIENTES_H_INCLUDED

#include "clsCliente.h"

class ArchivoClientes {
    private:
        char nombre[30];
    public:
        ArchivoClientes(const char *n = "Clientes.dat");
        Cliente leerRegistro(int);
        bool grabarRegistro(Cliente);
        bool modificarRegistro(Cliente, int);
        int contarRegistros();
        int contarRegistrosActivos(int ca);
        int buscarRegistro(int);
        int buscarRegistroxDNI(const char *d);
        int buscarRegistroxCUIT(const char *c);
        int buscarRegistroxMail(const char *m);
        int buscarRegistroxTelefono(const char *t);
        void listarRegistros();
        void altaCliente();
        void listadoFiltrado(int *l, const int TAM);
        void buscarPorId();
        void buscarPorDni();
        void buscarPorNombre();
        void buscarPorApellido();
        void buscarPorMail();
        void buscarPorFechaNac();
        void buscarPorCuit();
        void buscarPorTelefono();
        void modificarNombre();
        void modificarApellido();
        void modificarFechaNacimiento();
        void modificarMail();
        void modificarDomicilio();
        void modificarCuit();
        void modificarTelefono();
        void bajaCliente();
        ~ArchivoClientes();
};

#endif // CLSARCHIVOCLIENTES_H_INCLUDED
