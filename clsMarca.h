#ifndef CLSMARCA_H_INCLUDED
#define CLSMARCA_H_INCLUDED

class Marca {
    private:
        int id;
        char nombre[20];
        char pais[20];
        bool estado;
    public:
        Marca(int d=0, const char *n="Una Marca", const char *p="Un pais");
        void setId(int i);
        void setNombre(const char *n);
        void setPais(const char *p);
        void setEstado(bool e);
        int getId();
        const char *getNombre();
        const char *getPais();
        bool getEstado();
        void Cargar(int d, const char *n);
        void Mostrar();
        ~Marca();
};


#endif // CLSMARCA_H_INCLUDED
