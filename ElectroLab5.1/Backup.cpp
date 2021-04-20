#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
#include "Backup.h"
#include "ventas.h"
#include "detalleVenta.h"
#include "Vendedor.h"
#include "rlutil.h"
#include "conio.h"
#include "funciones.h"
#include <windows.h>


/// REALIZAR BACKUP
bool backupVyDV(int leg){
    system("cls");
    dibujarCuadro(2,1,119,29);
    dibujarCuadro(37,9,79,11);
    rlutil::setColor(2);
    mostrarUsuario(leg);
    gotoxy(55, 10);
    cout<<"BACKUP"<<endl<<endl;
    gotoxy(50, 14);
    cout << "REALIZANDO BACKUP";
    for (int i=0; i<3;i++){
        cout << ".";
        Sleep(1300);
    }
    backupVentas();
    backupDetalleVentas();
    if((backupVentas()==false)|| (backupDetalleVentas()==false)){
        MessageBox(NULL, "NO SE PUDO REALIZAR EL BACKUP", "ERROR", MB_OK|MB_ICONERROR);
        getch();
        return false;
    }
    else {
        MessageBox(NULL, "BACKUP REALIZADO CON EXITO", "CONFIRMACION", MB_OK|MB_ICONEXCLAMATION);
    }
    return true;
}

bool backupVentas(){
    Venta obj;
    FILE *p=fopen("Ventas.dat", "rb");
    if (p==NULL)return false;
    FILE *pB=fopen("Ventas.bkp", "wb");
    if(pB==NULL) {
        fclose(p);
        return false;
    }
    while(fread(&obj, sizeof (Venta), 1, p)==1){
        fwrite(&obj,sizeof (Venta), 1,pB);
    }
    fclose(p);
    fclose(pB);
    //leerBackupVenta();
    //getch();
    return true;
}

bool leerBackupVenta(){
    Venta obj;
    FILE *p=fopen("Ventas.bkp", "rb");
        if(p==NULL) return false;
        while(fread(&obj,sizeof (Venta),1 ,p)==1){
        obj.mostrar();
        cout<<endl;
    }
    fclose(p);
    return true;
}

bool backupDetalleVentas(){
    DetalleVenta obj;
    FILE *p=fopen("Detalle.dat", "rb");
    if (p==NULL)return false;
    FILE *pB=fopen("Detalle.bkp", "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&obj, sizeof (DetalleVenta), 1, p)==1){
        fwrite(&obj,sizeof (DetalleVenta), 1,pB);
    }
    fclose(p);
    fclose(pB);
    //leerBackupDetalleVentas();
    //getch();
    return true;
}

bool leerBackupDetalleVentas(){
    DetalleVenta obj;
    FILE *p=fopen("Detalle.bkp", "rb");
    if(p==NULL) return false;
    while(fread(&obj,sizeof (DetalleVenta),1 ,p)==1){
        obj.mostrar();
        cout<<endl;
    }
    fclose(p);
    return true;
}

///REALIZAR RESTAURACION

bool restauracionVyDV(int leg){
    system("cls");
    dibujarCuadro(2,1,119,29);
    dibujarCuadro(37,9,79,11);
    rlutil::setColor(2);
    mostrarUsuario(leg);
    gotoxy(50, 10);
    cout<<"RESTAURAR BACKUP"<<endl<<endl;
    gotoxy(50, 14);
    cout << "RESTAURANDO BACKUP";
    for (int i=0; i<3;i++){
        cout << ".";
        Sleep(1300);
    }
    restaurarVentas();
    restaurarDetalleVentas();
    if((restaurarVentas()==false)|| (restaurarDetalleVentas()==false)){
        MessageBox(NULL, "NO SE PUDO RESTAURAR", "ERROR", MB_OK|MB_ICONERROR);
        getch();
        return false;
    }
    else {
        MessageBox(NULL, "RESTAURACION REALIZADA CON EXITO", "CONFIRMACION", MB_OK|MB_ICONEXCLAMATION);
    }
    return true;
}

bool restaurarVentas(){
    Venta obj;
    FILE *p=fopen("Ventas.bkp", "rb");
    if (p==NULL)return false;
    FILE *pR=fopen("Ventas.dat", "wb");
    if(pR==NULL) {
        fclose(p);
        return false;
    }
    while(fread(&obj, sizeof (Venta), 1, p)==1){
        fwrite(&obj,sizeof (Venta), 1,pR);
    }
    fclose(p);
    fclose(pR);
    return true;
}

bool restaurarDetalleVentas(){
    DetalleVenta obj;
    FILE *p=fopen("Detalle.bkp", "rb");
    if (p==NULL)return false;
    FILE *pR=fopen("Detalle.dat", "wb");
    if(pR==NULL) {
        fclose(p);
        return false;
    }
    while(fread(&obj, sizeof (DetalleVenta), 1, p)==1){
        fwrite(&obj,sizeof (DetalleVenta), 1,pR);
    }
    fclose(p);
    fclose(pR);
    return true;
}
