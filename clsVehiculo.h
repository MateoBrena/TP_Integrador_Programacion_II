#ifndef CLSVEHICULO_H_INCLUDED
#define CLSVEHICULO_H_INCLUDED

#include "clsFecha.h"

class Vehiculo {
    private:
        int id;
        char patente[8];
        int idMarca;
        char modelo[20];
        int anio;
        char color[20];
        int kilometros;
        float precio;
        char combustible[10];
        Fecha fechaIngreso;
        bool estado;
    public:
        Vehiculo();
        void setId(int i);
        void setPatente(const char *p);
        void setIdMarca(int iM);
        void setModelo(const char *m);
        void setAnio(int a);
        void setColor(const char *c);
        void setKilometros(int k);
        void setPrecio(float p);
        void setCombustible(const char *co);
        void setFechaIngreso(Fecha fI);
        void setEstado(bool e);
        int getId();
        const char *getPatente();
        int getIdMarca();
        const char *getModelo();
        int getAnio();
        const char *getColor();
        int getKilometros();
        float getPrecio();
        const char *getCombustible();
        Fecha getFechaIngreso();
        bool getEstado();
        void Cargar();
        void Mostrar();
        ~Vehiculo();

};

#endif // CLSVEHICULO_H_INCLUDED
