#ifndef CLSPERSONA_H_INCLUDED
#define CLSPERSONA_H_INCLUDED

#include "clsFecha.h"
#include "clsDomicilio.h"

class Persona{
    protected:
        char nombre[50];
        char apellido[50];
        int dni;
        char mail[30];
        Fecha fechaNacimiento;
        Domicilio domicilio;
        bool estado;
    public:
        Persona(const char *n="Fulano", const char *a="Perez", int d=0, const char *m="mail@ejemplo.com", Fecha fN=Fecha(), Domicilio dom=Domicilio());
        void setNombre(const char *n);
        void setApellido(const char *a);
        void setDni(int);
        void setMail(const char *m);
        void setFechaNacimiento(Fecha fechaNac);
        void setDomicilio(Domicilio);
        void setEstado(bool e);
        const char *getNombre();
        const char *getApellido();
        int getDni();
        const char *getMail();
        Fecha getFechaNacimiento();
        Domicilio getDomicilio();
        bool getEstado();
        void Cargar();
        void Mostrar();
        ~Persona();
};

#endif // CLSPERSONA_H_INCLUDED
