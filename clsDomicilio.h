#ifndef CLSDOMICILIO_H_INCLUDED
#define CLSDOMICILIO_H_INCLUDED

#include <iostream>
#include <cstring>

class Domicilio{
    private:
        char calle[30];
        int altura;
        char localidad[30];
        char provincia[30];
        char codigoPostal[10];
    public:
        Domicilio(const char *c = "Calle Falsa", int a = 123, const char *l = "Una localidad", const char *p = "Buenos Aires", const char *cp="B1234ABC");
        void setCalle(const char *c);
        void setLocalidad(const char *l);
        void setProvincia(const char *p);
        void setAltura(int a);
        void setCodigoPostal(const char *cp);
        const char *getCalle();
        const char *getLocalidad();
        const char *getProvincia();
        int getAltura();
        const char *getCodigoPostal();
        void Cargar();
        void Mostrar();
        std::string MostrarFormato();
        ~Domicilio();

};

#endif // CLSDOMICILIO_H_INCLUDED
