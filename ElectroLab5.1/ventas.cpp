#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<vector>
#include<iomanip>
using namespace std;
#include "ventas.h"
#include "detalleVenta.h"
#include "Fecha.h"
#include "menu.h"
#include "funciones.h"
#include "rlutil.h"
#include <windows.h>

void Venta::cargar(int legajo2, float Precio){
    fechaVenta;
    gotoxy(80,8);cout << "FECHA: ";
    //fechaVenta.cargar();
    fechaVenta.mostrar();
    gotoxy(80,12);cout << "INGRESE EL TIPO DE PAGO ";
    gotoxy(78,14);cout << "(1- EFECTIVO/ DEBITO o 2- TARJETA):  ";
    cin >> TipoPago;
    while (TipoPago<=0 || TipoPago>=3){
        gotoxy(80,16);  cout<<"1- EFECTIVO/ DEBITO o 2- TARJETA: "<<"\t";
        cin>>TipoPago;
    }
    if (TipoPago==2){
         preciototal=Precio*1.15;
    }
    else {
        preciototal=Precio;
    }
    Legajo=legajo2;
     gotoxy(80,18);cout << "PRESIONE ENTER";getch();
}

void Venta::mostrar(){
    cout << setw(48)<< "FECHA: ";
    fechaVenta.mostrar();
    cout<<endl<<endl;
    cout << setw(20)<< "* TIPO DE PAGO";
    cout << setw(15)<<"LEGAJO";
    cout << setw(27)<<"PRECIO TOTAL"<<endl;
    cout << setw(18)<< TipoPago;
    cout << setw(16)<< Legajo;
    cout << setw(18)<<"$ "<< preciototal<<endl;
}

bool Venta::guardarEnDisco(int posicion){
 bool grabo;
    FILE *p;
        if (posicion == -1){
            p = fopen("Ventas.dat", "ab");
            if (p == NULL)return false;
        }
        else{
            p = fopen("Ventas.dat", "rb+");
            if (p == NULL)return false;
            fseek(p, posicion * sizeof(Venta), 0);
        }
        grabo = fwrite(this, sizeof(Venta), 1, p);
        fclose(p);
        return grabo;
}

bool Venta::leerDeDisco(int posicion){
    bool leyo;
    FILE *p;
    p = fopen("Ventas.dat", "rb");
    if (p == NULL)return false;
    fseek(p, posicion * sizeof(Venta), 0);
    leyo = fread(this, sizeof(Venta), 1, p);
    fclose(p);
    return leyo;
}

//------------------- SET ------------------------
void Venta::setNumeroTicket(int num){
    NumeroTicket=num;
}

void Venta::setFecha(Fecha f){
    fechaVenta=f;
}

void Venta::setpreciototal(float tot){
    preciototal=tot;
}

//------------------- GET ------------------------
int Venta::getNumeroTicket(){
    return NumeroTicket;
}

int Venta::getlegajo(){
 return Legajo;
}

Fecha Venta::getFecha(){
    return fechaVenta;
}

int Venta::gettipopago(){
    return TipoPago;
}
//----------------------------------------------------------
void realizar_venta(int legajo2){
    system ("cls");
    int numero,seguir;
    float ptotal=0,bandera=0;
    Venta obj;
    DetalleVenta obj2;
    celular obj3;
    vector<DetalleVenta> vDvta;
    numero=nroVenta();
    obj2.setNroVenta(numero);
    do{
        bandera=0;
        dibujarCuadro(2,1,119,29);
        dibujarCuadro(30,4,72,6);
        mostrarUsuario(legajo2);
        rlutil::setColor(2);
        gotoxy(40,5);
        cout << "NUMERO DE VENTA: "<<numero<<endl;
        rlutil::setColor(4);
        dibujarCuadro(105,26,118,28);
        rlutil::setColor(2);
        gotoxy (107,27);cout << "0|CANCELAR";
        bandera= obj2.cargar();
        if (bandera==-2) {
            seguir=0;
        }
        else {
        ptotal+= bandera;
            if (bandera!=0){
                vDvta.push_back(obj2);
                descontar_stock(obj2.getcodigo(),obj2.getCantidad());
                cout<<endl;
                seguir= MessageBox(NULL, "DESEA SEGUIR CARGANDO?", "VENTA", MB_OKCANCEL|MB_ICONQUESTION);
                system("cls");
            }
        }
    }while(seguir ==1 || bandera==0);
    system("cls");
    dibujarCuadro(2,1,119,29);
    mostrarUsuario(legajo2);
    if (seguir==2){
        dibujarCuadro(30,4,72,6);
        gotoxy(43,5);cout << "NUMERO DE VENTA: "<<numero<<endl<<endl;
        rlutil::setColor(4);
        gotoxy(43,7);cout<<"FINALIZAR COMPRA"<<endl<<endl<< endl;
        rlutil::setColor(2);
        for(unsigned int i=0; i<vDvta.size(); i++){
            vDvta.at(i).mostrar(10,7,i+1);
            cout<<endl;
        }
        seguir=MessageBox(NULL, "CONFIRMAR COMPRA?", "VENTA", MB_OKCANCEL|MB_ICONQUESTION);
        if(seguir ==1) {
            for(unsigned int i=0; i<vDvta.size(); i++){
                vDvta.at(i).guardarEnDisco();
            }
            obj.setNumeroTicket(numero);
            obj.cargar(legajo2,ptotal);
            obj.guardarEnDisco();
            system("cls");
            buscar_detalle(numero);
        }
        else {
            for(unsigned int i=0; i<vDvta.size(); i++){
                devolver_stock(vDvta.at(i).getcodigo(),vDvta.at(i).getCantidad());
            }
            MessageBox(NULL, "COMPRA CANCELADA", "VENTA", MB_OK|MB_ICONEXCLAMATION);
        }
    }
    else{
        for(unsigned int i=0; i<vDvta.size(); i++){
            devolver_stock(vDvta.at(i).getcodigo(),vDvta.at(i).getCantidad());
        }
        MessageBox(NULL, "COMPRA CANCELADA", "VENTA", MB_OK|MB_ICONEXCLAMATION);
    }
}

void buscar_detalle(int codigo){
    DetalleVenta obj;
    Venta obj2;
    bool entro=false;
    int i=0;
    system ("cls");
    dibujarCuadro(4,1,65,3);
    gotoxy(25,2);
    cout << "NUMERO DE VENTA "  << codigo <<endl<< endl;
    while (obj2.leerDeDisco(i++)){
        if(obj2.getNumeroTicket()==codigo){
        cout << endl;
        obj2.mostrar();}
    }
    dibujarCuadro(4,4,65,9);
    cout<<endl<<endl;
    i=0;
    while (obj.leerDeDisco(i++)){
        if(obj.getNroVenta()==codigo){
            obj.mostrar();
            cout << endl<< endl;
            entro=true;
        }
    }
    if (entro==false){
        system("cls");
        MessageBox(NULL, "CODIGO NO ENCONTRADO", "VENTA", MB_OK|MB_ICONERROR);
    }
    getch();
}

void buscar_detalle(char* codigo){
    system ("cls");
    DetalleVenta obj;
    Venta obj2;
    celular obj3;
    char codigobuscado [20];
    bool entro=false,entro1=false;
    int i=0,j,f;
    while (obj3.leerDeDisco(i++)){
        if (strcmpi(codigo,obj3.getmarca())==0)


    j=0;
    cout << endl;
    while (obj.leerDeDisco(j++)){
        if(strcmp(obj3.getcodigo(),obj.getcodigo())==0){
            rlutil::setColor(4);
            cout << setw(35)<< "NUMERO DE VENTA: " << obj.getNroVenta()<<endl;
            cout<<"    ____________________________________________________________";
            rlutil::setColor(2);
            cout << endl<<endl;

            f=0;
            while (obj2.leerDeDisco(f++)){
                if (obj2.getNumeroTicket()==obj.getNroVenta()) obj2.mostrar();
            }
            cout <<endl<< endl;
            obj.mostrar();
            cout <<endl<< endl;
            entro=true;
            cout << endl<< endl;
        }
    }}
    if (entro==false){
        system("cls");
        MessageBox(NULL, "CODIGO NO ENCONTRADO", "VENTA", MB_OK|MB_ICONERROR);
    }
    getch();
}

void buscar_detalle_legajo(int legajo){
    DetalleVenta obj;
    Venta obj2;
    vendedor obj3;
    bool entro=false,entro1=false;
    int i=0,j,f;
    system ("cls");
    dibujarCuadro(4,1,65,3);
    gotoxy(6,2);
    cout << "LEGAJO: "<< legajo;
    while (obj3.leerDeDisco(i++)){
        if(obj3.getLegajo()==legajo){
            gotoxy(20,2);
            cout << "NOMBRE Y APELLIDO: "<< obj3.getnombre()<<" "<<obj3.getApellido();
        }
    }
    cout<<endl<<endl;
    f=0;
    while (obj2.leerDeDisco(f++)){

        if(obj2.getlegajo()==legajo){
            j=0;
            rlutil::setColor(4);
            cout << setw(35)<< "NUMERO DE VENTA: " << obj2.getNumeroTicket()<<endl;
            cout<<"    ____________________________________________________________";
            rlutil::setColor(2);
            cout << endl<<endl;
            obj2.mostrar();
            cout <<endl<< endl;
            while (obj.leerDeDisco(j++)){
                if(obj.getNroVenta()==obj2.getNumeroTicket()){
                    obj.mostrar();
                }
            }
            cout << endl << endl;
            entro=true;
        }
    }
    if (entro==false){
            system("cls");
            MessageBox(NULL, "LEGAJO NO ENCONTRADO", "VENTA", MB_OK|MB_ICONERROR);
        }
    return;
}

void detalle_fecha_DMA(){
    DetalleVenta obj;
    Venta obj2;
    Fecha fI;
    Fecha fF;
    gotoxy(30,10);
    cout<<"CONSULTA FECHA DESDE (DD/MM/AAAA): "<<"\t";
    while(fI.cargar()==false){
        MessageBox(NULL, "INGRESE UNA FECHA VALIDA", "VENTAS", MB_OK|MB_ICONERROR);
    }
    gotoxy(30,20);
    cout<<"CONSULTA FECHA HASTA (DD/MM/AAAA): "<<"\t";
    while(fF.cargar()==false){
        MessageBox(NULL, "INGRESE UNA FECHA VALIDA", "VENTAS", MB_OK|MB_ICONERROR);
    }
    bool entro=false,entro1=false;
    int i=0,j;
    system ("cls");
    while (obj2.leerDeDisco(i++)){
        if (((obj2.getFecha().getAnio() > fI.getAnio()) || (obj2.getFecha().getAnio() == fI.getAnio()) && (obj2.getFecha().getMes() > fI.getMes())) ||
            ((obj2.getFecha().getAnio() == fI.getAnio()) && (obj2.getFecha().getMes() >= fI.getMes()) && (obj2.getFecha().getDia() >= fI.getDia()))){
            if(((obj2.getFecha().getAnio() < fF.getAnio()) || (obj2.getFecha().getAnio() == fF.getAnio()) && (obj2.getFecha().getMes() < fF.getMes())) ||
              ((obj2.getFecha().getAnio() == fF.getAnio()) && (obj2.getFecha().getMes() <= fF.getMes()) && (obj2.getFecha().getDia() <= fF.getDia()))){
            j=0;
            cout << endl << endl;
            rlutil::setColor(4);
            cout << setw(35)<< "NUMERO DE VENTA: " << obj2.getNumeroTicket()<<endl;
            cout<<"    ____________________________________________________________";
            rlutil::setColor(2);
            cout<<endl<<endl;
            obj2.mostrar();
            cout << endl << endl;
            while (obj.leerDeDisco(j++)){
                if(obj.getNroVenta()==obj2.getNumeroTicket()){
                    obj.mostrar();
                }
            }

            entro=true;
        }}
    }
    if (entro==false){

        MessageBox(NULL, "RANGO NO ENCONTRADO", "ERROR", MB_OK|MB_ICONERROR);
        return;
    }
    getch();
}




int contarRegVenta(){
  int cantReg;
  FILE *p;
  p=fopen("Ventas.dat", "rb");
  if(p==NULL) return -1;
  fseek(p,0,2);
  cantReg=ftell(p)/sizeof(Venta);
  fclose(p);
  return cantReg;
}
int nroVenta(){
    int cant;
    cant=contarRegVenta();
        if (cant==-1) return 1;
        else cant++;
    return cant;
}
