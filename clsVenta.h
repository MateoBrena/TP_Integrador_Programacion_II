#ifndef CLSVENTA_H_INCLUDED
#define CLSVENTA_H_INCLUDED

#include "clsFecha.h"

class Venta {
    private:
        int nroVenta;
        Fecha fechaVenta;
        int nroCliente;
        int nroVendedor;
        int nroVehiculo;
        int idMarcaVehiculo;
        float monto;
        bool estado;
    public:
        Venta(int n=0, Fecha f=Fecha(), int nC=0, int nV=0, int nVeh=0, int iM=0, float m=0.00);
        void setNroVenta(int nV);
        void setFechaVenta(Fecha fV);
        void setNroCliente(int nC);
        void setNroVendedor(int nV);
        void setNroVehiculo(int nVeh);
        void setIdMarcaVehiculo(int d);
        void setMonto(float m);
        void setEstado(bool e);
        int getNroVenta();
        Fecha getFechaVenta();
        int getNroCliente();
        int getNroVendedor();
        int getNroVehiculo();
        int getIdMarcaVehiculo();
        float getMonto();
        std::string getMontoFormato();
        bool getEstado();
        void Cargar(int n, Fecha f, int nC, int nV, int nVeh, int iM, float m);
        void Mostrar();
        ~Venta();
};

#endif // CLSVENTA_H_INCLUDED
