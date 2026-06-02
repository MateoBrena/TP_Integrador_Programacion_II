#ifndef CLSVENTA_H_INCLUDED
#define CLSVENTA_H_INCLUDED

#include "clsFecha.h"

class Venta {
    private:
        int nroVenta;
        Fecha fechaVenta;
        char cuitCliente[12];
        int nroVendedor;
        char patenteVehiculo[10];
        float monto;
        bool estado;
    public:
        Venta(int n=0, Fecha f=Fecha(), const char *cc="201111111100", int nV=0, const char *v="AAA123", float m=0.00);
        void setNroVenta(int nV);
        void setFechaVenta(Fecha fV);
        void setCuitCliente(const char *cC);
        void setNroVendedor(int nV);
        void setPatenteVehiculo(const char *pV);
        void setMonto(float m);
        void setEstado(bool e);
        int getNroVenta();
        Fecha getFechaVenta();
        const char * getCuitCliente();
        int getNroVendedor();
        const char * getPatenteVehiculo();
        float getMonto();
        bool getEstado();
        void Cargar(int n, Fecha f, const char *cC, int nV, const char *pV, float m);
        void Mostrar();
        ~Venta();
};

#endif // CLSVENTA_H_INCLUDED
