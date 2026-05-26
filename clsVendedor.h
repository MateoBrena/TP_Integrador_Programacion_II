#ifndef CLSVENDEDOR_H_INCLUDED
#define CLSVENDEDOR_H_INCLUDED

#include "clsPersona.h"

class Vendedor : public Persona {
    private:
        int categoria;
        Fecha fechaContratacion;
    public:
        Vendedor();
        void setCategoria(int c);
        void setFechaContratacion(Fecha f);
        int getCategoria();
        Fecha getFechaContratacion();
        void Cargar();
        void Mostrar();
        ~Vendedor();
};


#endif // CLSVENDEDOR_H_INCLUDED
