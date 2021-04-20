#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iomanip>
using namespace std;
#include "Vendedor.h"
#include "celular.h"
#include "rlutil.h"
#include "funciones.h"
#include "conio.h"
#include "menu.h"
#include <windows.h>

using namespace std;

bool celular::cargar(){
    system ("cls");
    bool cV=true;
    bool bR=true;
   /// cin.ignore();

    dibujarCuadro(30,5,85,7);
    dibujarCuadro(30,5,85,100);
    rlutil::setColor(4);
    dibujarCuadro(106,29,117,31);
    rlutil::setColor(2);
    gotoxy (107,30);cout << "0|CANCELAR";
    gotoxy(50,6);
    cout << "NUEVO REGISTRO"<<endl;
    gotoxy (35,10);cout << "INGRESE LA MARCA DEL EQUIPO: ";
    cin.ignore();
        do{
            cin.getline(marca,20);
            if (cadenacero(marca)==false) return false;
            cV=cadenaVacia(marca, 20, 35, 10);

        }while(cV==false);
    gotoxy (35,12);cout << "INGRESE EL MODELO DEL EQUIPO: ";

       do{
            cin.getline(modelo,20);
             if (cadenacero(modelo)==false) return false;
            cV=cadenaVacia(modelo, 20, 35, 12);
            bR=buscarRepetido(modelo, 20, 35,12);
        } while ((cV==false)||(bR==false));
    gotoxy (35,14);cout << "INGRESE EL PRECIO: ";
    cin >> precio;
    if (precio==0)return false;
        while (precio<=0){
            gotoxy(35,15);
            cout<<"REINGRESE: "<<"\t";
            cin>>precio;
            if (precio==0)return false;
        }
    gotoxy (35,16);cout << "INGRESE EL CODIGO DEL PRODUCTO: ";
    cin.ignore();
     do{

            cin.getline(codigo,20);
            if (cadenacero(codigo)==false) return false;
            cV=cadenaVacia(codigo, 20, 35, 16);
            bR=buscarRepetido(codigo, 20, 35, 16);
        }   while ((cV==false)|| (bR==false));
    gotoxy (35,18);cout << "INGRESE STOCK: ";
    cin>> stock;
    if (stock==0)return false;
        while (stock<=0){
            gotoxy(35,19);
            cout<<"REINGRESE: "<<"\t";
            cin>>stock;
             if (stock==0)return false;
        }
    Estado=true;
}

void celular::mostrar(){
   if (Estado==true){
        cout << endl;
        left;
        cout <<setw(18)<< "CODIGO: "<< codigo;
        cout <<setw(28)<< "MARCA:  "<< marca<< endl;
        cout <<setw(50)<< "MODELO: "<< modelo<< endl;
        cout <<setw(52)<< "PRECIO: $ "<< precio<< endl;
        cout <<setw(50)<< "STOCK:  "<<stock<< endl;

    }
    else {
        cout << "EL EQUIPO FUE DADO DE BAJA"<< endl;
   }
}

//---------------SET------------------------
void celular::setcodigo(char* cod){
    strcpy(codigo, cod);
}

void celular::setstock(int st){
  stock=st;
}

void celular::setprecio (float pr){
    precio=pr;
}

void celular::setEstado(bool e){
    Estado=e;
}

//---------------GET-------------------------
char* celular::getcodigo (){
    return codigo;
}

int celular::getstock(){
 return stock;
}

float celular::getprecio (){
return precio;
}

char* celular::getmarca(){
  return marca;
}

char* celular::getmodelo(){
  return modelo;
}

int celular::getEstado(){
    return Estado;
}

//--------------------------------------------------------------------

bool celular::guardarEnDisco(int posicion){
    bool grabo;
    FILE *p;
        if (posicion == -1){
            p = fopen("celulares.dat", "ab");
            if (p == NULL)return false;
        }
    else{
        p = fopen("celulares.dat", "rb+");
        if (p == NULL)return false;
        fseek(p, posicion * sizeof(celular), 0);
    }
    grabo = fwrite(this, sizeof(celular), 1, p);
    fclose(p);
    return grabo;
}

bool celular::leerDeDisco(int posicion){
    bool leyo;
    FILE *p;
    p = fopen("celulares.dat", "rb");
        if (p == NULL)return false;
    fseek(p, posicion * sizeof(celular), 0);
    leyo = fread(this, sizeof(celular), 1, p);
    fclose(p);
    return leyo;
}

void alta_producto(){
    celular obj;
    bool cancel;
    int conf;
    cancel=obj.cargar();
    if (cancel){
    conf=MessageBox(NULL, "DESEA GUARDAR EL EQUIPO?", "EQUIPO", MB_OKCANCEL|MB_ICONQUESTION);
    if (conf==1){
        obj.guardarEnDisco();
        MessageBox(NULL, "EQUIPO GUARDADO", "CONFIRMACION", MB_OK|MB_ICONINFORMATION);
    }
    else {
       MessageBox(NULL, "ERROR AL GUARDAR", "ERROR", MB_OK|MB_ICONERROR);
    }}
    else {
       MessageBox(NULL, "ALTA CANCELADA", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    }
}

bool buscarRepetido (char *pal, int tam, int x, int y){
    bool bR=true;
    celular obj;
    int i=0;
    FILE *p;
    p=fopen("celulares.dat", "rb");
        if(p == NULL) return bR;
        while(obj.leerDeDisco(i++)){
            if ((strcmp(pal, obj.getcodigo())==0)||(strcmp(pal, obj.getmodelo())==0)){
                gotoxy(x,y+1);
                cout<<"REINGRESE POR FAVOR: ";
                bR=false;
                return bR;
            }
        }
    fclose(p);
    return bR;
}

bool baja_Celular(int leg){
    celular obj;
    int i=0;
    char cod[20],dec;
    bool noExiste=true;
    system("cls");
    mostrarUsuario(leg);
    gotoxy(35, 10);
    cout<<"INGRESE EL CODIGO DE PRODUCTO: "<<"\t";
    cargarCadena(cod, 20);
    cout<<endl;
    while (obj.leerDeDisco(i++)){
        if( strcmp( obj.getcodigo(),cod)==0){
            if (obj.getEstado()==false){
                MessageBox(NULL, "EL PRODUCTO YA FUE DADO DE BAJA", "ERROR", MB_OK|MB_ICONERROR);
            }
            else {
                obj.mostrar();
                rlutil::setColor(4);
                dibujarCuadro(8,11,62,18);
                rlutil::setColor(2);
                getch();
                dec=MessageBox(NULL, "DAR DE BAJA EL PRODUCTO?", "BAJA", MB_OKCANCEL|MB_ICONQUESTION);
                if (dec==1){
                    obj.setEstado(false);
                    obj.guardarEnDisco(i-1);
                    MessageBox(NULL, "PRODUCTO DADO DE BAJA", "CONFIRMACION", MB_OK|MB_ICONEXCLAMATION);
                }
                else {
                    MessageBox(NULL, "ERROR AL DAR DE BAJA", "ERROR", MB_OK|MB_ICONERROR);
                }
            }
            noExiste=false;
        }
    }
    if(noExiste==true) MessageBox(NULL, "CODIGO INEXISTENTE", "ERROR", MB_OK|MB_ICONERROR);
}

void modificar_stock(char* codigo){
    celular obj;
    int i=0,nuevo_stock;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        if( strcmp( obj.getcodigo(),codigo)==0){
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            obj.mostrar();
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            cout<<endl;
            cout<< "\tEL STOCK DEL PRODUCTO ES: ";
            cout << obj.getstock();
            cout<<endl<< endl;
            cout<< "\tDE CUANTO ES EL NUEVO STOCK: ";
            cin >> nuevo_stock;
            obj.setstock(obj.getstock()+nuevo_stock);
            obj.guardarEnDisco(i-1);
            cout<<endl;
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            obj.mostrar();
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            getch();
            return;
        }
    }
    MessageBox(NULL, "CODIGO INEXISTENTE", "ERROR", MB_OK|MB_ICONERROR);


}

void modificar_Precio(char* codigo){
    celular obj;
    int i=0;
    float nuevo_precio;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        if( strcmp( obj.getcodigo(),codigo)==0){
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            obj.mostrar();
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            cout<<endl;
            cout << "\tEL PRECIO DEL PRODUCTO ES: ";
            cout << obj.getprecio();
            cout<<endl<<endl;
            cout << "\tCUAL ES EL NUEVO PRECIO: ";
            cin >> nuevo_precio;
            obj.setprecio(nuevo_precio);
            obj.guardarEnDisco(i-1);
            cout<<endl;
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            obj.mostrar();
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            getch();
            return;
        }
    }
  MessageBox(NULL, "CODIGO INEXISTENTE", "ERROR", MB_OK|MB_ICONERROR);
}

void descontar_stock(char* codigo, int cant){
    celular obj;
    int i=0;
    while (obj.leerDeDisco(i++)){
        if( strcmp( obj.getcodigo(),codigo)==0){
            obj.setstock(obj.getstock()- cant);
            obj.guardarEnDisco(i-1);
            return;
        }
    }
    MessageBox(NULL, "CODIGO INEXISTENTE", "ERROR", MB_OK|MB_ICONERROR);
    getch();
}

void devolver_stock(char* codigo, int cant){
    celular obj;
    int i=0;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        if( strcmp( obj.getcodigo(),codigo)==0){
            obj.setstock(obj.getstock()+ cant);
            obj.guardarEnDisco(i-1);
            return;
        }
    }
}


void mostrar_equipos(){
    celular obj;
    int i=0;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        rlutil::setColor(4);
        cout <<setw(50)<< "       ______________________________________________________"<< endl;
        rlutil::setColor(2);
        obj.mostrar();
    }
    rlutil::setColor(4);
    cout <<setw(50)<< "       ______________________________________________________"<< endl;
    rlutil::setColor(2);
    cout << endl;
    getch();
}

int buscar_equipo(char* codigo){
    celular obj;
    int i=0,j=0;
    system ("cls");
    if (obj.leerDeDisco(i)==false) return -1;
    while (obj.leerDeDisco(i++)){
        if( strcmp( obj.getcodigo(),codigo)==0){
            obj.mostrar();
            rlutil::setColor(4);
            dibujarCuadro(8,1,62,6);
            rlutil::setColor(2);
            j++;
        }
    }
    if(j==0){
        MessageBox(NULL, "CODIGO NO ENCONTRADO", "ERROR", MB_OK|MB_ICONWARNING);
    }
    getch();
    return i;
}


int buscar_equipo_marca(char* codigo){
    celular obj;
    int i=0,j=0;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        if( strcmpi( obj.getmarca(),codigo)==0){
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            obj.mostrar();
            j=1;
        }
    }
    rlutil::setColor(4);
    cout <<setw(50)<< "       ______________________________________________________"<< endl;
    rlutil::setColor(2);
    if (j==0){
        system("cls");
        MessageBox(NULL, "MARCA NO ENCONTRADA", "ERROR DE MARCA", MB_OK|MB_ICONERROR);
    }
    else {getch();}
    return i;
}

int buscar_equipo_precio(float precio){
    celular obj;
    int i=0,j=0;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        if((precio== obj.getprecio()) || ((precio-5000) < obj.getprecio() && ((precio+5000) > obj.getprecio()))){
            rlutil::setColor(4);
            cout <<setw(50)<< "       ______________________________________________________"<< endl;
            rlutil::setColor(2);
            obj.mostrar();
            j=1;
        }
    }
    rlutil::setColor(4);
    cout <<setw(50)<< "       ______________________________________________________"<< endl;
    rlutil::setColor(2);
    if(j==0){
        system("cls");
        MessageBox(NULL, "ERROR DE PRECIO", "ERROR", MB_OK|MB_ICONERROR);
    }
    else{getch();}
    return i;
}

float buscar_equipo2(char* codigo){
celular obj;
int i=0;
while (obj.leerDeDisco(i++)){
    if( strcmp( obj.getcodigo(),codigo)==0){
        dibujarCuadro(82,6,110,16);
        gotoxy(85,8);cout << "MARCA: " << obj.getmarca()<< endl;
        gotoxy(85,10);cout << "MODELO: " <<obj.getmodelo()<< endl;
        gotoxy(85,12);cout <<"PRECIO UNITARIO: $"<<  obj.getprecio()<< endl;
        gotoxy(85,14);cout<<"STOCK: "<< obj.getstock()<<endl;
        return obj.getprecio();
    }
}
return i;
}

bool buscar_equipo_baja(char* codigo){
    celular obj;
    bool estado=false;
    int i=0;
    while (obj.leerDeDisco(i++)){
        if( strcmp( codigo,obj.getcodigo())==0){
            if (obj.getEstado()==true){
            estado=true;
            return estado;
            }
            else{
            MessageBox(NULL, "EQUIPO DADO DE BAJA", "EQUIPO", MB_OK|MB_ICONERROR);
            return estado;
            }
        }
    }
   MessageBox(NULL, "CODIGO INEXISTENTE", "EQUIPO", MB_OK|MB_ICONERROR);
    return false;
}
