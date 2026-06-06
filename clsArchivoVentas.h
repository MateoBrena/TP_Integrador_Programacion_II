#ifndef CLSARCHIVOVENTAS_H_INCLUDED
#define CLSARCHIVOVENTAS_H_INCLUDED

#include "clsVenta.h"

class ArchivoVentas {
    private:
        char nombre[30];
    public:
        ArchivoVentas(const char *n = "Ventas.dat");
        Venta leerRegistro(int pos);
        bool grabarRegistro(Venta obj);
        bool modificarRegistro(Venta obj, int pos);
        int contarRegistros();
        int contarRegistrosActivos(int ca);
        int buscarRegistro(int d);
        int buscarRegistroxCliente(int d);
        int buscarRegistroxVendedor(int d);
        int buscarRegistroxVehiculo(int d);
        int buscarRegistroxMarca(int d);
        void listarRegistros();
        void altaVenta();
        void listadoFiltrado(int *l, const int TAM);
        void buscarPorId();
        void buscarPorFecha();
        void buscarPorCliente();
        void buscarPorVendedor();
        void buscarPorVehiculo();
        void buscarPorMarca();
        void buscarPorMonto();
        void modificarFechaVenta();
        void modificarNroCliente();
        void modificarNroVendedor();
        void modificarNroVehiculo();
//        void modificarMonto();
        void bajaVenta();
        ~ArchivoVentas();
};

#endif // CLSARCHIVOVENTAS_H_INCLUDED
