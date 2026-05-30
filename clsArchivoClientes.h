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
        void listarRegistros();
        void altaCliente();
        void buscarPorDni();
        void modificarNombre();
        void modificarApellido();
        void modificarFechaNacimiento();
        void modificarMail();
        void modificarDomicilio();
        void modificarTelefono();
        void bajaCliente();
        ~ArchivoClientes();
};

#endif // CLSARCHIVOCLIENTES_H_INCLUDED
