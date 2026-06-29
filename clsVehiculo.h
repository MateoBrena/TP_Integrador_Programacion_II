#ifndef CLSVEHICULO_H_INCLUDED
#define CLSVEHICULO_H_INCLUDED


#include "clsFecha.h"

class Vehiculo {
    private:
        int id;
        char patente[10];
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
        Vehiculo(int d=0, const char *p="AAA123", int iM=1, const char *m="Un modelo", int a=1900, const char *c="Negro",
        int k=0, float pr=0.00, const char *co="Nafta", Fecha fI=Fecha());
        void hacerMayusculas(char *p);
        bool validarPatente(const char *p);
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
        std::string getPrecioFormato();
        const char *getCombustible();
        Fecha getFechaIngreso();
        bool getEstado();
        void Cargar(int d, const char *p, int iM);
        void Mostrar();
        ~Vehiculo();
};

#endif // CLSVEHICULO_H_INCLUDED
