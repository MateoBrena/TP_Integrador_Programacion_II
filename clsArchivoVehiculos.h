#ifndef CLSARCHIVOVEHICULOS_H_INCLUDED
#define CLSARCHIVOVEHICULOS_H_INCLUDED

#include "clsVehiculo.h"

class ArchivoVehiculos {
    private:
        char nombre[30];
    public:
        ArchivoVehiculos(const char *n = "Vehiculos.dat");
        Vehiculo leerRegistro(int pos);
        bool grabarRegistro(Vehiculo obj);
        bool modificarRegistro(Vehiculo obj, int pos);
        int contarRegistros();
        int buscarRegistro(int d);
        int buscarRegistroInactivo(int d);
        int buscarRegistroPorPatente(const char *p);
        void listarRegistros();
        void listadoFiltrado(int *l, const int TAM);
        void altaVehiculo();
        void buscarPorId();
        void buscarPorPatente();
        void buscarPorMarca();
        void buscarPorModelo();
        void buscarPorAnio();
        void buscarPorColor();
        void buscarPorKilometros();
        void buscarPorPrecio();
        void buscarPorCombustible();
        void buscarPorFechaIngreso();
        void modificarPatente();
        void modificarMarca();
        void modificarModelo();
        void modificarAnio();
        void modificarColor();
        void modificarKilometros();
        void modificarPrecio();
        void modificarCombustible();
        void modificarFechaIngreso();
        void bajaVehiculo();
        ~ArchivoVehiculos();
};








#endif // CLSARCHIVOVEHICULOS_H_INCLUDED
