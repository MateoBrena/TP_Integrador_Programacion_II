#ifndef CLSFECHA_H_INCLUDED
#define CLSFECHA_H_INCLUDED

#include <iostream>
#include <cstring>

class Fecha{
    private:
        int dia, mes, anio;
        bool esBisiesto(int a);
        bool esValida(int d, int m, int a);
    public:
        Fecha(int d=1, int m=1, int a=1900);
        int getDia();
        int getMes();
        int getAnio();
        bool setDia(int d);
        bool setMes(int m);
        bool setAnio(int a);
        void setHoy();
        void cargarFecha();
        void mostrarFecha();
        std::string mostrarFechaFormato();
        bool operator<(Fecha);
        bool operator<=(Fecha);
        bool operator>(Fecha);
        bool operator>=(Fecha);
        bool operator==(Fecha);
        ~Fecha();
};

#endif // CLSFECHA_H_INCLUDED
