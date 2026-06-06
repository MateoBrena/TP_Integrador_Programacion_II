#ifndef CLSCLIENTE_H_INCLUDED
#define CLSCLIENTE_H_INCLUDED

#include "clsPersona.h"

class Cliente : public Persona {
    private:
        int nroCliente;
        char cuit[15];
        char telefono[12];
    public:
        Cliente(int n=0, const char *c="20-00000000-0", const char *t="12345678");
        bool validarCuitFormato(const char *c);
        bool validarCuit(const char *c, const char *d);
        void setNroCliente(int n);
        void setCuit(const char *c);
        void setTelefono(const char *t);
        int getNroCliente();
        const char * getCuit();
        const char * getTelefono();
        void Cargar(const char *d, int n, const char *c, Fecha fN);
        void Mostrar();
        ~Cliente();
};

#endif // CLSCLIENTE_H_INCLUDED
