#ifndef CLSCLIENTE_H_INCLUDED
#define CLSCLIENTE_H_INCLUDED

#include "clsPersona.h"

class Cliente : public Persona {
    private:
        int cuit[12];
        int telefono[12];
    public:
        Cliente();
        void setCuit(const int *);
        void setTelefono(const int *);
        const int * getCuit();
        const int * getTelefono();
        void Cargar();
        void Mostrar();
        ~Cliente();
};

#endif // CLSCLIENTE_H_INCLUDED
