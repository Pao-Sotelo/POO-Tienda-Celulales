#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iomanip>
using namespace std;
#include "detalleVenta.h"
#include "funciones.h"
#include "rlutil.h"
#include "menu.h"
#include "ventas.h"
#include <windows.h>

float DetalleVenta::cargar(){
    char seguir,codigo1[15];
    bool vC=true,vv=true;
    float retorno_precio=0;
    gotoxy(10,8);cout << "CODIGO DE PRODUCTO: ";
    cargarCadena(codigo1,15);
    if(cadenacero(codigo1)==false)return -2;
    strcpy(Codigo,codigo1);
    vv=buscar_equipo_baja(Codigo);
    if (vv==false){
        system("cls");
        return 0;
    }
    Precio=buscar_equipo2(Codigo);
    gotoxy(10,10);cout << "CANTIDAD: ";
    do{
        cin >> Cantidad;
        if(Cantidad==0)return -2;
    }while (Cantidad<=0);
    vC=verif_Cant(Cantidad, Codigo);
    if (vC == false){
        return retorno_precio;
    }
    return retorno_precio=Precio*Cantidad;
}

bool DetalleVenta::guardarEnDisco(int posicion){
bool grabo;
    FILE *p;
    if (posicion == -1){
        p = fopen("Detalle.dat", "ab");
        if (p == NULL)return false;
    }
    else{
        p = fopen("Detalle.dat", "rb+");
        if (p == NULL)return false;
        fseek(p, posicion * sizeof(DetalleVenta), 0);
    }
    grabo = fwrite(this, sizeof(DetalleVenta), 1, p);
    fclose(p);
    return grabo;
}

void DetalleVenta::mostrar(){
   cout << setw(25)<<"* CODIGO DE EQUIPO ";
   cout << setw(20)<<"PRECIO UNITARIO ";
   cout << setw(15)<<"CANTIDAD "<<endl;
   cout<<setw(21)<< Codigo ;
   cout<<setw(12)<<"$ "<< Precio;
   cout<<setw(17)<< Cantidad << endl;
}

void DetalleVenta::mostrar(int x, int y,int pos){
    gotoxy(x,y*pos+1);cout << "CODIGO DE EQUIPO: " << Codigo << endl;
    gotoxy(x,y*pos+2);cout << "PRECIO UNITARIO: $ "<< Precio << endl;
    gotoxy(x,y*pos+3);cout << "CANTIDAD: "<< Cantidad << endl;
}


bool DetalleVenta::leerDeDisco(int posicion){
    bool leyo;
    FILE *p;
    p = fopen("Detalle.dat", "rb");
    if (p == NULL)return false;
    fseek(p, posicion * sizeof(DetalleVenta), 0);
    leyo = fread(this, sizeof(DetalleVenta), 1, p);
    fclose(p);
    return leyo;
}

//---------- GET ---------------------
int DetalleVenta::getNroVenta(){
    return NroVenta;
}

char* DetalleVenta::getcodigo(){
    return Codigo;
}

int DetalleVenta::getCantidad(){
    return Cantidad;
}

//---------- SET ---------------------
void DetalleVenta::setNroVenta(int numero){
    NroVenta=numero;
}
