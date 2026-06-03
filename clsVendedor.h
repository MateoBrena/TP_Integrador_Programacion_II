#ifndef CLSVENDEDOR_H_INCLUDED
#define CLSVENDEDOR_H_INCLUDED

#include "clsPersona.h"

class Vendedor : public Persona {
    private:
        int nroVendedor;
        int categoria;
        Fecha fechaContratacion;
    public:
        Vendedor(int n=0, int c=1, Fecha f=Fecha());
        void setNroVendedor(int n);
        void setCategoria(int c);
        void setFechaContratacion(Fecha f);
        int getNroVendedor();
        int getCategoria();
        Fecha getFechaContratacion();
        void Cargar(int d, int n, int cat, Fecha fN, Fecha fC);
        void Mostrar();
        ~Vendedor();
};


#endif // CLSVENDEDOR_H_INCLUDED
