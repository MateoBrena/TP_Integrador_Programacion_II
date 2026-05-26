#ifndef CLSDOMICILIO_H_INCLUDED
#define CLSDOMICILIO_H_INCLUDED

class Domicilio{
    private:
        char calle[50];
        int altura;
        char localidad[50];
        char provincia[50];
        int codigoPostal;
    public:
        Domicilio(const char *c = "Calle Falsa", int a = 123, const char *l = "Una localidad", const char *p = "Buenos Aires", int cp=1234);
        void setCalle(const char *c);
        void setLocalidad(const char *l);
        void setProvincia(const char *p);
        void setAltura(int a);
        void setCodigoPostal(int cp);
        const char *getCalle();
        const char *getLocalidad();
        const char *getProvincia();
        int getAltura();
        int getCodigoPostal();
        void cargar();
        void mostrar();
        ~Domicilio();

};

#endif // CLSDOMICILIO_H_INCLUDED
