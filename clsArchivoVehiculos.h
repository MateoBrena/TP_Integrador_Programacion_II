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
        int buscarRegistro(const char* patente);
        void listarRegistros();
        void altaVehiculo();
        void buscarPorPatente();
        void bajaVehiculo();

        void modificarMarca();
        void modificarModelo();
        void modificarAnio();
        void modificarColor();
        void modificarKilometros();
        void modificarPrecio();
        void modificarCombustible();
        void modificarFechaIngreso();

        ~ArchivoVehiculos();
};








#endif // CLSARCHIVOVEHICULOS_H_INCLUDED
