#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
#include "funciones.h"
#include "Vendedor.h"
#include "rlutil.h"
#include "celular.h"
#include "SOutil.h"
#include "detalleVenta.h"
#include "ventas.h"
#include "conio.h"
#include "menu.h"
#include "Backup.h"
#include <windows.h>


void MENU(){
    vendedor v;
    int legajo,verificar=0;
    char contra [25];
    do{
        int verificar=0;
        system("cls");
        rlutil::setColor(2);
        dibujarCuadro(2,1,119,29);
        rlutil::setColor(4);
        dibujarCuadro(37,9,79,11);
        dibujarCuadro(37,12,79,23);
        rlutil::setColor(2);
        gotoxy (53,10);cout << "BIENVENIDO" << endl;
        gotoxy (50,14);cout << "INGRESE SU LEGAJO" << endl;
        gotoxy (95,30);cout << "PRESIONE 0 PARA SALIR";
        rlutil::setColor(2);
        gotoxy (50,16); cout <<">>";
        gotoxy (50,18);cout << "INGRESE SU CLAVE" << endl;
        gotoxy (50,20); cout <<">>";
        gotoxy (57,16);cin >> legajo;
        if (legajo==0) {
            rlutil::cls();
            exit(-1);
        }
        gotoxy (57,20);cargarCadena(contra, 25);
        verificar=verificar_usuario(legajo,contra);
        system("cls");
        switch(verificar){
            case 1:
                menuV(legajo);
            break;
            case 2:
                menuS(legajo);
            break;
            case 0:
            break;
            default:
                MessageBox(NULL, "ERROR DE INGRESO", "ERROR", MB_OK|MB_ICONERROR);
        }
    }while(verificar==0);
}

//-----------------------------MENÚ SUPERVISOR---------------------------------------

void menuS (int legajo2){
    int opcion;
    do{
        system("cls");
        rlutil::setColor(2);
        dibujarCuadro(2,1,119,29);
        dibujarCuadro(37,9,79,11);
        mostrarUsuario(legajo2);
        gotoxy (53,10);cout << "MENU SUPERVISOR" << endl;
        gotoxy (50,14);cout << "1- REPORTE DE VENTAS" << endl;
        gotoxy (50,16);cout << "2- PRODUCTOS" << endl;
        gotoxy (50,18);cout << "3- USUARIOS" << endl;
        gotoxy (50,20);cout << "4- BACKUP" << endl;
        gotoxy (50,22);cout << "5- CAMBIAR MI CLAVE" << endl;
        gotoxy (110,30);cout << "0- SALIR";
        gotoxy (50,24); cout <<">>";
        gotoxy (57,24);cin >> opcion;
        switch(opcion){
            case 1:
                menu_buscar_venta(legajo2);
            break;
            case 2:
                menu_s_productos(legajo2);
            break;
            case 3:
                menu_s_usuario(legajo2);
            break;
            case 4:
                menuBackup(legajo2);
            break;
            case 5:cambiar_clave(legajo2);
                break;
            case 0:
            break;
            default:
                MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
            }
    }while(opcion!=0);
}

void menu_buscar_venta(int leg){
    int opcion;
    do{
    system("cls");
    rlutil::setColor(2);
    dibujarCuadro(2,1,119,29);
    dibujarCuadro(37,9,79,11);
    mostrarUsuario(leg);
    gotoxy (55,10);cout << "VENTAS" << endl;
    gotoxy (47,14);cout << "1| BUSCAR POR NUMERO DE VENTA " << endl;
    gotoxy (47,16);cout << "2| BUSCAR POR VENDEDOR" << endl;
    gotoxy (47,18);cout << "3| BUSCAR POR FECHA" << endl;
    gotoxy (47,20);cout <<"4| BUSCAR POR MARCA" << endl;
    gotoxy (47,23);cout <<">>";
    gotoxy (107,30);cout << "0|IR ATRAS";
    gotoxy (50,23);cin >> opcion;
    system ("cls");
    gotoxy (48,15);
    buscar_venta(opcion, leg);}while(opcion!=0);
}

void buscar_venta(int opcion, int leg){
    int numero_buscado,legajo;
    mostrarUsuario(leg);
    gotoxy (107,30);cout << "0|IR ATRAS";
        switch (opcion){
            case 1:
                dibujarCuadro(2,1,119,29);
                gotoxy(35,10);
                cout << "INGRESE EL NUMERO DE VENTA: ";
                cin >> numero_buscado;
                if (numero_buscado==0){MessageBox(NULL, "BUSQUEDA CANCELADA", "CANCEL", MB_OK|MB_ICONEXCLAMATION); return;}
                buscar_detalle(numero_buscado);
                break;
            case 2:
                dibujarCuadro(2,1,119,29);
                gotoxy(35,10);
                cout << "INGRESE EL LEGAJO DEL VENDEDOR: ";
                cin >> legajo;
                if (legajo==0){MessageBox(NULL, "BUSQUEDA CANCELADA", "CANCEL", MB_OK|MB_ICONEXCLAMATION); return;}
                buscar_detalle_legajo(legajo);
                getch();
                break;
            case 3:
                dibujarCuadro(2,1,119,29);
                detalle_fecha_DMA();
                break;
            case 4:
                dibujarCuadro(2,1,119,29);
                gotoxy(35,10);
                cout << "INGRESA LA MARCA DEL PRODUCTO: ";
                char marca [15];
                cin.ignore();
                cin.getline(marca,15);
                if(cadenacero(marca)==false){MessageBox(NULL, "BUSQUEDA CANCELADA", "CANCEL", MB_OK|MB_ICONEXCLAMATION); return;}
                buscar_detalle(marca);
                break;
              case 0:
                    break;
            default: MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
        }
}

void menu_s_productos(int legajo2){
    int opcion;
        do{
            system("cls");
            dibujarCuadro(2,1,119,29);
            dibujarCuadro(37,9,83,11);
            mostrarUsuario(legajo2);
            gotoxy (55,10);cout << "PRODUCTOS" << endl;
            gotoxy (50,14);cout << "1| BUSCAR PRODUCTO" << endl;
            gotoxy (50,16);cout << "2| LISTAR TODOS LOS PRODUCTOS" << endl;
            gotoxy (50,18);cout << "3| MODIFICAR STOCK/PRECIO" << endl;
            gotoxy (50,20);cout << "4| ALTA DE PRODUCTO" << endl;
            gotoxy (50,22);cout << "5| BAJA DE PRODUCTO" << endl;
            gotoxy (107,30);cout << "0|IR ATRAS";
            gotoxy (50,24); cout <<">>";
            gotoxy (57,24);cin >> opcion;
            switch(opcion){
                case 1:
                    menu_busqueda(legajo2);
                    break;
                case 2:
                    mostrar_equipos();
                    break;
                case 3:
                    menu_modCelular(legajo2);
                    break;
                case 4:
                    alta_producto();
                    break;
                case 5:
                    baja_Celular(legajo2);
                    break;
                case 0:
                    break;
                default: MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
            }
        }while (opcion!=0);
}

void menu_busqueda(int leg){
   int opcion;
   float precio_buscado;
   char codigo_buscado [15];
        do{
            system("cls");
            dibujarCuadro(2,1,119,29);
            dibujarCuadro(37,9,79,11);
            rlutil::setColor(2);
            mostrarUsuario(leg);
            gotoxy (55,10);cout << "PRODUCTOS" << endl;
            gotoxy (50,14);cout << "1| BUSCAR POR CODIGO " << endl;
            gotoxy (50,16);cout << "2| BUSCAR POR MARCA" << endl;
            gotoxy (50,18);cout << "3| BUSCAR POR PRECIO" << endl;
            gotoxy (50,21); cout <<">>";
            gotoxy (107,30);cout << "0|IR ATRAS";
            gotoxy (57,21);cin >> opcion;
            system ("cls");
            gotoxy (50,16);
                switch(opcion){
                    case 1:
                        dibujarCuadro(2,1,119,29);
                        gotoxy (107,30);cout << "0|IR ATRAS";
                        gotoxy (40,15);cout << "INGRESE EL CODIGO DEL PRODUCTO: ";
                        gotoxy (76,15);cargarCadena(codigo_buscado,15);
                         if(cadenacero(codigo_buscado)==false){MessageBox(NULL, "BUSQUEDA CANCELADA", "CANCEL", MB_OK|MB_ICONEXCLAMATION); return;}
                        buscar_equipo(codigo_buscado);
                        break;
                    case 2:
                        dibujarCuadro(2,1,119,29);
                        gotoxy (107,30);cout << "0|IR ATRAS";
                        gotoxy (40,15);cout << "INGRESE LA MARCA DEL PRODUCTO: ";
                        gotoxy (76,15);cargarCadena(codigo_buscado,15);
                        if(cadenacero(codigo_buscado)==false){MessageBox(NULL, "BUSQUEDA CANCELADA", "CANCEL", MB_OK|MB_ICONEXCLAMATION); return;}
                        buscar_equipo_marca(codigo_buscado);
                        break;
                    case 3:
                       dibujarCuadro(2,1,119,29);
                       gotoxy (107,30);cout << "0|IR ATRAS";
                       gotoxy (40,15); cout << "INGRESE EL PRECIO DEL PRODUCTO: ";
                       gotoxy (76,15); cin >> precio_buscado;
                       if(precio_buscado==0){MessageBox(NULL, "BUSQUEDA CANCELADA", "CANCEL", MB_OK|MB_ICONEXCLAMATION); return;}
                        buscar_equipo_precio(precio_buscado);
                        break;
                    case 0:
                        break;

                    default: MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
                }
       }while(opcion!=0);
}

void menu_modCelular(int leg){
    int opcion;
    char codigo_buscado[15];
    do{
        system("cls");
        dibujarCuadro(2,1,119,29);
        dibujarCuadro(37,9,79,11);
        rlutil::setColor(2);
        mostrarUsuario(leg);
        gotoxy (53,10);cout << "STOCK/PRECIO" << endl;
        gotoxy (50,14);cout << "1| MODIFICAR STOCK " << endl;
        gotoxy (50,16);cout << "2| MODIFICAR PRECIO" << endl;
        gotoxy (50,21); cout <<">>";
        gotoxy (107,30);cout << "0|IR ATRAS";
        gotoxy (57,21);cin >> opcion;

            switch(opcion){
                case 1:
                    gotoxy (50,23);
                    cout << "INGRESE EL CODIGO: ";
                    cargarCadena(codigo_buscado,15);
                    modificar_stock(codigo_buscado);
                    break;
                case 2:
                    gotoxy (50,23);
                    cout << "INGRESE EL CODIGO: ";
                    cargarCadena(codigo_buscado,15);
                    modificar_Precio(codigo_buscado);
                    break;
                case 0:

                    break;
                default:
                    MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);

                    break;
            }
    }while (opcion!=0);
}

void menu_s_usuario(int leg){
    int opcion;
        do{
            system("cls");
            dibujarCuadro(2,1,119,29);
            dibujarCuadro(37,9,79,11);
            mostrarUsuario(leg);
            gotoxy (55,10);cout << "USUARIOS" << endl;
            gotoxy (50,14);cout << "1| ALTA DE USUARIO" << endl;
            gotoxy (50,16);cout << "2| BAJA DE USUARIO" << endl;
            gotoxy (50,18);cout << "3| VER TODOS LOS USUARIOS" << endl;
            gotoxy (107,30);cout << "0|IR ATRAS";
            gotoxy (50,21); cout <<">>";
            gotoxy (57,21);cin >> opcion;
                switch(opcion){
                    case 1:
                        system("cls");
                        alta_Usuario();
                        break;
                    case 2:
                        baja_Usuario();
                        break;

                    case 3:
                        system("cls");
                        ver_usuarios();
                        break;
                    case 0:
                    break;
                    default:
                       MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
                        break;
                }
        }while (opcion!=0);
}

void menuBackup(int leg){
    int opcion;
    do{
        system("cls");
        dibujarCuadro(2,1,119,29);
        dibujarCuadro(37,9,79,11);
        rlutil::setColor(2);
        mostrarUsuario(leg);
        gotoxy(55,10);
        cout << "BACKUP" << endl;
        gotoxy(52,14);
        cout << "1| REALIZAR BACKUP" << endl;
        gotoxy(52,16);
        cout << "2| RESTAURAR BACKUP" << endl;
        gotoxy (52,18); cout <<">>";
        gotoxy (107,30);cout << "0|IR ATRAS";
        gotoxy (57,18); cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                backupVyDV(leg);
            break;
            case 2:
                restauracionVyDV(leg);
            break;
            case 0:
            break;
            default:
                MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
            break;
        }
    }while(opcion!=0);
}

//-----------------------------MENÚ VENDEDOR---------------------------------------
void menuV(int legajo2){
    int opcion;
    do{

        system("cls");
        dibujarCuadro(2,1,119,29);
        dibujarCuadro(37,9,79,11);
        rlutil::setColor(2);
        mostrarUsuario(legajo2);
        gotoxy (55,10);cout << "MENU VENDEDOR" << endl;
        gotoxy (50,14);cout << "1- NUEVA VENTA" << endl;
        gotoxy (50,16);cout << "2- PRODUCTOS" << endl;
        gotoxy (50,18);cout << "3- CAMBIAR MI CLAVE" << endl;
        gotoxy (107,30);cout << "0|IR ATRAS";
        gotoxy (50,20); cout <<">>";
        gotoxy (57,20);cin >> opcion;
            switch(opcion){
                case 1:
                    realizar_venta(legajo2);
                    break;
                case 2:
                    menu_v_productos(legajo2);
                    break;

                case 3:cambiar_clave(legajo2);
                    break;
                case 0:

                    break;
                default:
                    MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
            }
    }while(opcion!=0);
}



void menu_v_productos(int legajo2){
    int opcion;
    char codigo_buscado[15];
    do{

        system("cls");
        dibujarCuadro(2,1,119,29);
        dibujarCuadro(37,9,83,11);
        rlutil::setColor(2);
        mostrarUsuario(legajo2);
        gotoxy (55,10);cout << "MENU VENDEDOR" << endl;
        gotoxy (50,14);cout << "1| BUSCAR PRODUCTO" << endl;
        gotoxy (50,16);cout << "2| LISTAR TODOS LOS PRODUCTOS" << endl;
        gotoxy (50,18);cout << "3| MODIFICAR STOCK" << endl;
        gotoxy (50,20);cout << "4| ALTA DE PRODUCTO" << endl;
        gotoxy (50,22);cout << "5| BAJA DE PRODUCTO" << endl;
        gotoxy (50,24); cout <<">>";
        gotoxy (107,30);cout << "0|IR ATRAS";
        gotoxy (57,24);cin >> opcion;

            switch(opcion){
                case 1:
                    menu_busqueda(legajo2);
                    break;
                case 2:
                    mostrar_equipos();
                    break;
                case 3:
                     gotoxy (50,27); cout <<"INGRESE EL CODIGO DEL PRODUCTO >>";
                    cargarCadena(codigo_buscado,15);
                    modificar_stock(codigo_buscado);
                    break;
                case 4:
                     alta_producto();
                    break;
                case 5:
                    baja_Celular(legajo2);
                    break;
                case 0:
                break;

               default:MessageBox(NULL, "ERROR DE INGRESO, VUELVA A INTENTARLO", "ERROR", MB_OK|MB_ICONERROR);
            }
    }while(opcion!=0);
}
