#ifndef CLSVENTA_H_INCLUDED
#define CLSVENTA_H_INCLUDED

#include "clsFecha.h"

class Venta {
    private:
        int nroVenta;
        Fecha fechaVenta;
        int cuitCliente;
        int nroVendedor;
        int idVehiculo;
        float monto;
        bool estado;
    public:
        Venta();
        void setNroVenta(int nV);
        void setFechaVenta(Fecha fV);
        void setCuitCliente(int cC);
        void setNroVendedor(int nV);
        void setidVehiculo(int iV);
        void setMonto(float m);
        void setEstado(bool e);
        int getNroVenta();
        Fecha getFechaVenta();
        int getCuitCliente();
        int getNroVendedor();
        int getIdVehiculo();
        float getMonto();
        bool getEstado();
        void Cargar();
        void Mostrar();
        ~Venta();
};

#endif // CLSVENTA_H_INCLUDED
