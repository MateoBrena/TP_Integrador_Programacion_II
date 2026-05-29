#ifndef CLSCLIENTE_H_INCLUDED
#define CLSCLIENTE_H_INCLUDED

#include "clsPersona.h"

class Cliente : public Persona {
    private:
        int nroCliente;
        char cuit[12];
        char telefono[12];
    public:
        Cliente(int n=0, const char *c="11111111111", const char *t="12345678");
        void setNroCliente(int n);
        void setCuit(const char *c);
        void setTelefono(const char *t);
        int getNroCliente();
        const char * getCuit();
        const char * getTelefono();
        void Cargar(int d, int n);
        void cuitFormato(const char *c);
        void Mostrar();
        ~Cliente();
};

#endif // CLSCLIENTE_H_INCLUDED
