#ifndef CLSPERSONA_H_INCLUDED
#define CLSPERSONA_H_INCLUDED

#include "clsFecha.h"
#include "clsDomicilio.h"

class Persona{
    protected:
        int dni;
        char nombre[20];
        char apellido[20];
        char mail[30];
        Fecha fechaNacimiento;
        Domicilio domicilio;
        bool estado;
    public:
        Persona(int d=0, const char *n="Fulano", const char *a="Perez", const char *m="mail@ejemplo.com", Fecha fN=Fecha(), Domicilio dom=Domicilio());
        void setDni(int);
        void setNombre(const char *n);
        void setApellido(const char *a);
        void setMail(const char *m);
        void setFechaNacimiento(Fecha fechaNac);
        void setDomicilio(Domicilio);
        void setEstado(bool e);
        int getDni();
        const char *getNombre();
        const char *getApellido();
        const char *getMail();
        Fecha getFechaNacimiento();
        Domicilio getDomicilio();
        bool getEstado();
        void Cargar(int d);
        void Mostrar();
        ~Persona();
};

#endif // CLSPERSONA_H_INCLUDED
