#ifndef HORA_H_INCLUDED
#define HORA_H_INCLUDED

class Fecha{
    private:
    int dia, mes, anio;
    public:
        Fecha();
        int getDia();
        int getMes();
        int getAnio();
        void setDia(int);
        void setMes(int);
        void setAnio(int);
        void mostrar();
        bool cargar();
};



#endif // HORA_H_INCLUDED
