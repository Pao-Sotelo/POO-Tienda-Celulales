#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED
#include "celular.h"
#include "Vendedor.h"
class Venta{
private:
  int NumeroTicket;
  Fecha fechaVenta;
  int TipoPago; // 1 efectivo, 2 Debito, 3 Credito
  int Legajo;
  float preciototal;
public:
    venta();
    void setNumeroTicket(int);
    void setLegajo(int);
    void settipopago(int);
    void setpreciototal(float);
    void setFecha(Fecha);
    int getlegajo();
    int gettipopago();
    int getNumeroTicket();
    float getpreciototal();
    Fecha getFecha();
    void cargar(int,float);
    void mostrar();
    bool buscar_detalle(int);
    bool guardarEnDisco(int = -1);
    bool leerDeDisco(int);
};


#endif // VENTAS_H_INCLUDED
