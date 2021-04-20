#ifndef DETALLEVENTA_H_INCLUDED
#define DETALLEVENTA_H_INCLUDED

class DetalleVenta{
private:
    int NroVenta;
    float Precio;
    char Codigo [15];
    int Cantidad;
public:
    detalleVenta();
    int getNroVenta();
    float getPrecio();
    char* getcodigo();
    int getCantidad();
    void setNroVenta(int);
    void setPrecio(float);
    void setcodigo(char*);
    void setCantidad(int);
    float cargar();
    void mostrar();
    void mostrar(int,int,int);
    bool guardarEnDisco(int=-1);
    bool leerDeDisco(int);
};

#endif // DETALLEVENTA_H_INCLUDED
