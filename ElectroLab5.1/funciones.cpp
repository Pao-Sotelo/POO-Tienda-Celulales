#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include "funciones.h"
#include "Vendedor.h"
#include "rlutil.h"
#include "celular.h"
#include "SOutil.h"
#include "detalleVenta.h"
#include "ventas.h"
#include "conio.h"
#include "menu.h"
#include <windows.h>
using namespace std;


void cargarCadena(char *pal, int tam){
  int i;
  fflush(stdin);
      for(i=0;i<tam;i++){
          pal[i]= cin.get();
          if(pal[i]=='\n') break;
	  }
  pal[i]='\0';
  fflush(stdin);
}

int verificar_usuario(int leg, char clave []){
    vendedor v;
    int i=0;
    while (v.leerDeDisco(i++)){
        if (v.getLegajo()== leg && v.getEstado()==false){
            MessageBox(NULL, "ESTE USUARIO FUE DADO DE BAJA", "ERROR", MB_OK|MB_ICONERROR);
            return 0;
        }
        if( v.getLegajo()== leg && strcmp(v.getcontrasena(), clave)==0 && v.getCargo()== 2){
        return 2;
        }
        else {
            if( v.getLegajo()== leg && strcmp(v.getcontrasena(), clave)==0 ){
        return 1;
            }
        }
    }
    MessageBox(NULL, "USUARIO O CLAVE INCORRECTA", "ERROR", MB_OK|MB_ICONERROR);
    return 0;
}

bool cadenaVacia(char *pal, int tam, int x, int y){
    if ((pal[0]=='\0')|| (pal[0]==' ')){
        gotoxy(x, y+1);
        cout<<"REINGRESE POR FAVOR: ";
        return false;
    }
    return true;
}



bool verif_Cant(int cant, char* cod){
bool vC=true;
celular obj;
int i=0;
while (obj.leerDeDisco(i++)){
    if(( obj.getstock()< cant)&& (strcmp(obj.getcodigo(), cod)==0)){
        MessageBox(NULL, "STOCK INSUFICIENTE", "EQUIPO", MB_OK|MB_ICONERROR);
        vC=false;
        return vC;
    }}
return vC;
}



int WINAPI WinMain(HINSTANCE hInstanciaActual,HINSTANCE hInstanciaPrevia, LPSTR lpCmdLinea, int nCmdshow){

MessageBox(NULL, "Hola", "Mensaje", MB_OKCANCEL|MB_ICONQUESTION);
return 0;
}


void dibujarCuadro(int x1,int y1,int x2,int y2){
	int i;

    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "\304"; //linea horizontal superior
		gotoxy(i,y2); cout << "\304"; //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout <<"\263"; //linea vertical izquierda
		gotoxy(x2,i); cout <<"\263"; //linea vertical derecha
	}

    gotoxy(x1,y1); cout<< "\332";
    gotoxy(x1,y2); cout<< "\300";
    gotoxy(x2,y1); cout<< "\277";
    gotoxy(x2,y2); cout<< "\331";
}
