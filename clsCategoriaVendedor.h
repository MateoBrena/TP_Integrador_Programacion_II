#ifndef CLSCATEGORIAVENDEDOR_H_INCLUDED
#define CLSCATEGORIAVENDEDOR_H_INCLUDED


class CategoriaVendedor {
    private:
        int idCategoria;
        char descripcion[30];
        float porcentajeComision;
        bool estado;
    public:
        CategoriaVendedor(int d=0, const char *desc="Junior", float pC=0.01);
        void setIdCategoria(int id);
        void setDescripcion(const char *d);
        void setComision(float c);
        void setEstado(bool e);
        int getIdCategoria();
        const char *getDescripcion();
        float getPorcentajeComision();
        bool getEstado();
        void Cargar(int id, const char *d, float p);
        void Mostrar();
        ~CategoriaVendedor();
};


#endif // CLSCATEGORIAVENDEDOR_H_INCLUDED
