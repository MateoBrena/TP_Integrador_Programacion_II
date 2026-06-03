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
        int buscarRegistroActivo(int d);
        void listarRegistros();
        void altaVenta();
        void buscarPorId();
        void modificarFechaVenta();
        void modificarCuitCliente();
        void modificarNroVendedor();
        void modificarPatenteVehiculo();
        void modificarMarcaVehiculo();
        void modificarMonto();
        void bajaVenta();
        ~ArchivoVentas();
};

#endif // CLSARCHIVOVENTAS_H_INCLUDED
