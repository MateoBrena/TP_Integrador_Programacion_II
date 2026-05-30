#ifndef CLSMENUMARCA_H_INCLUDED
#define CLSMENUMARCA_H_INCLUDED

class menuMarca {
    private:

    public:
        menuMarca();
        void mostrarCabeceraTabla(int posX, int posY);
        void tablaMarcas(int posX, int posY);
        void subMenuModificarMarca();
        void iniciar();
        ~menuMarca();
};

#endif // CLSMENUMARCA_H_INCLUDED
