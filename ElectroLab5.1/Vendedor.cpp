#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iomanip>
using namespace std;
#include "Vendedor.h"
#include "rlutil.h"
#include "Fecha.h"
#include "funciones.h"
#include "conio.h"
#include "menu.h"

//-----------CONSTRUCTOR-------------
vendedor::vendedor(const char* d, const char* c, const char* n, const char* a, int l, int car, const char* clave){
    strcpy(Dni,d);
    strcpy(Cuil,c);
    strcpy(Nombre,n);
    strcpy(Apellido,a);
    Legajo=l;
    Cargo=car;
    clave= getdni();
    strcpy(Contrasena, clave);
}

bool vendedor::cargar(){
    bool cV=true;
    bool bR=true;
    bool vL=true;
    rlutil::setColor(4);
    dibujarCuadro(106,29,117,31);
    rlutil::setColor(2);
    gotoxy (107,30);cout << "0|CANCELAR";
    dibujarCuadro(30,5,85,7);
    dibujarCuadro(30,5,85,100);
    gotoxy(52,6);
    cout << "NUEVO REGISTRO"<<endl;
    gotoxy(35,10);
    cout << "DNI:       " <<"\t";
    do{
        cargarCadena(Dni, 10);
        if (cadenacero(Dni)==false) return false;
        cV=cadenaVacia(Dni, 10, 35, 10);
        bR=buscarRepetido1(Dni,10, 35, 10);
    }while ((cV==false)|| (bR==false));
    gotoxy(35,12);
    cout << "CUIL:      " <<"\t";
    do{
    cargarCadena(Cuil,15);
    if (cadenacero(Cuil)==false) return false;
    cV=cadenaVacia(Cuil, 10, 35, 12);
    bR=buscarRepetido1(Cuil,15, 35, 12);
    }while ((cV==false)|| (bR==false));
    gotoxy(35,14);
    cout << "NOMBRE:    " <<"\t";
    do{
    cargarCadena(Nombre, 50);
    if (cadenacero(Nombre)==false) return false;
    cV=cadenaVacia(Nombre, 50, 35, 14);
    }while (cV==false);
    gotoxy(35,16);
    cout << "APELLIDO:  " <<"\t";
    do{
    cargarCadena(Apellido, 50);
    if (cadenacero(Apellido)==false) return false;
    cV=cadenaVacia(Apellido, 50, 35, 16);
    }while (cV==false);
    gotoxy(35,18);  rlutil::setColor(2);
    cout << "LEGAJO:    " <<"\t";
    cin>>Legajo;
     if (Legajo==0) return false;
    vL=verificar_Legajo(Legajo, 35,18);
    while ((Legajo<0) || (vL==false)){
        gotoxy(55,18);
        cout<<"REINGRESE: "<<"\t";
        cin>>Legajo;
        if (Legajo==0) return false;
        vL=verificar_Legajo(Legajo, 35, 18);
    }
    gotoxy(35,20);
    cout << "CARGO(1 EMPLEADO/2 SUPERVISOR):     " <<"\t";
    cin>>Cargo;
    while (Cargo<=0 || Cargo>=3){
        MessageBox(NULL, "INTENTE NUEVAMENTE", "ERROR", MB_OK|MB_ICONERROR);
        gotoxy(35,22);cout<<"1- EMPLEADO o 2- ADMINISTRADOR: "<<"\t";
        cin>>Cargo;
    }
    gotoxy(35,22);
    cout << "CLAVE:     " <<"\t";
    cargarCadena(Contrasena, 25);
    cV=cadenaVacia(Contrasena, 10, 35, 22);
    while (cV==false){
        cargarCadena(Contrasena, 10);
        cV=cadenaVacia(Contrasena, 10, 35, 22);
    }
    gotoxy(35,24);
    cout << "FECHA DE INGRESO:     " <<"\t";
    while(fechaIngreso.cargar()==false){
        MessageBox(NULL, "INGRESE UNA FECHA VALIDA", "VENTAS", MB_OK|MB_ICONERROR);
    }
    Estado=true;
    gotoxy(35,28);
    return true;
}

void vendedor::mostrar(){
    if (Estado==true){
    cout << endl;
    left;
    cout <<setw(50) <<"DNI:              " << Dni <<endl;
    cout <<setw(50) <<"CUIT:             " << Cuil << endl;
    cout << setw(50)<<"NOMBRE:           " << Nombre <<endl;
    cout << setw(50)<<"APELLIDO:         " << Apellido << endl;
    cout << setw (18)<<"(FOTO)";
    cout <<setw(32) <<"LEGAJO:           " << Legajo <<endl;
    cout <<setw(50) <<"CARGO:            " << Cargo <<endl;
    cout <<setw(50) <<"CLAVE:            " << Contrasena <<endl;
    cout <<setw(50) <<"FECHA DE INGRESO: ";
    fechaIngreso.mostrar();
    cout <<endl<<endl;
    }
    return;
}




bool vendedor::guardarEnDisco(int posicion){
bool grabo;
    FILE *p;
        if (posicion == -1){
            p = fopen("vendedores.dat", "ab");
                if (p == NULL){
                    return false;
                }
        }
        else{
            p = fopen("vendedores.dat", "rb+");
                if (p == NULL){
                    return false;
                }
            fseek(p, posicion * sizeof(vendedor), 0);
        }
        grabo = fwrite(this, sizeof(vendedor), 1, p);
        fclose(p);
        return grabo;
}

bool vendedor::leerDeDisco(int posicion){
    bool leyo;
    FILE *p;
    p = fopen("vendedores.dat", "rb");
    if (p == NULL){
        return false;
    }
    fseek(p, posicion * sizeof(vendedor), 0);
    leyo = fread(this, sizeof(vendedor), 1, p);
    fclose(p);
    return leyo;
}

//---------------SET-----------------
void vendedor::setDni(char* DNI){
    strcpy(Dni,DNI);
}
void vendedor::setCuil(char* CUIT){
    strcpy(Cuil, CUIT);
}
void vendedor::setNombre(char* nom){
    strcpy(Nombre,nom);
}
void vendedor::setApellido(char* ape){
    strcpy(Apellido, ape);
}
void vendedor::setLegajo(int leg){
    Legajo=leg;
}
void vendedor::setCargo(int car){
    Cargo=car;
}
void vendedor::setContrasena (char* clave){
    strcpy(Contrasena, clave);
}
void vendedor::setFecha(Fecha f){
    fechaIngreso=f;
}
void vendedor::setEstado(bool e){
    Estado=e;
}

//------------GET-------------------
char* vendedor::getdni(){
    return Dni;
}
char * vendedor::getCuil(){
    return Cuil;
}
char * vendedor::getnombre(){
    return Nombre;
}
char * vendedor::getApellido(){
    return Apellido;
}
int vendedor::getLegajo(){
    return Legajo;
}
int vendedor::getCargo(){
    return Cargo;
}
char * vendedor::getcontrasena(){
    return Contrasena;
}
Fecha vendedor::getFecha(){
    return fechaIngreso;
}
bool vendedor::getEstado(){
    return Estado;
}

//---------------------------------------------------

void alta_Usuario(){
    vendedor obj;
    bool cancel;
    int conf;
    cancel=obj.cargar();
    if (cancel==true){
        conf=MessageBox(NULL, "DESEA GUARDAR EL USUARIO?", "NUEVO USUARIO", MB_OKCANCEL|MB_ICONQUESTION);
        if (conf==1){
            if(obj.guardarEnDisco()==true){
                MessageBox(NULL, "USUARIO GRABADO", "CONFIRMACION", MB_OK|MB_ICONINFORMATION);
                rlutil::cls();
                cout << "PRESIONE ENTER";
                getch();
                return;
            }
            else{
                MessageBox(NULL, "ERROR AL GRABAR", "ERROR", MB_OK|MB_ICONERROR);
                getch();
            }
        }
        else  MessageBox(NULL, "CARGA DE USUARIO CANCELADA", "NUEVO USUARIO", MB_OK|MB_ICONQUESTION);
    }
    else {
        MessageBox(NULL, "CARGA DE USUARIO CANCELADA", "NUEVO USUARIO", MB_OK|MB_ICONQUESTION);
    }
    rlutil::cls();
}

void ver_usuarios(){
vendedor obj;
int i=0;
while (obj.leerDeDisco(i++)){
    if (obj.getEstado()==true){
       rlutil::setColor(4);
     cout <<setw(50)<< "   _______________________________________________________________"<< endl;
     rlutil::setColor(2);
    obj.mostrar();
    }
}
    rlutil::setColor(4);
     cout <<setw(50)<< "   _______________________________________________________________"<< endl;
     rlutil::setColor(2);
 cout << endl;
getch();
return;
}


int buscar_Usuario(int leg){
    vendedor obj;
    int i=-1;
    system ("cls");
    while (obj.leerDeDisco(++i)){
        if(obj.getLegajo()==leg){
            return i;
        }
    }
    return i;
}

bool baja_Usuario(){
    vendedor obj;
    int leg, i=0;
    int dec,enc=0;
    gotoxy (107,30);cout << "0|CANCELAR";
    gotoxy(50,26);
    cout<<"INGRESE EL LEGAJO: "<<"\t";
    cin>>leg;
    if(leg==0) {
        MessageBox(NULL, "ACCION CANCELADA", "USUARIO", MB_OK|MB_ICONEXCLAMATION);
        return false;}
    while (obj.leerDeDisco(i++)){
        if (leg == obj.getLegajo()){
            enc=1;
            if (obj.getEstado()==false){
                MessageBox(NULL, "EL USUARIO YA FUE DADO DE BAJA", "USUARIO", MB_OK|MB_ICONEXCLAMATION);
            }
            else {
                system ("cls");
                cout<<endl;
                obj.mostrar();
                rlutil::setColor(4);
                dibujarCuadro(8,2,70,11);
                rlutil::setColor(2);
                getch();
                dec= MessageBox(NULL, "DESEA DAR DE BAJA AL USUARIO?", "USUARIO", MB_OKCANCEL|MB_ICONQUESTION);
                if (dec==1){
                    obj.setEstado(false);
                    obj.guardarEnDisco(i-1);
                    MessageBox(NULL, "USUARIO ELIMINADO", "USUARIO", MB_OK|MB_ICONEXCLAMATION);}
                else {
                    MessageBox(NULL, "ACCION CANCELADA", "USUARIO", MB_OK|MB_ICONEXCLAMATION);
                }
            }
        }

    }
    if (enc=0) MessageBox(NULL, "USUARIO NO ENCONTRADO", "USUARIO", MB_OK|MB_ICONERROR);
}

bool listar_Vendedores(){
    vendedor obj;
    int i=0;
    while(obj.leerDeDisco(i++)){
        obj.mostrar();
        cout<<endl;
    }
    return true;
}

bool buscarRepetido1 (char *pal, int tam, int x, int y){
    bool bR=true;
    vendedor obj;
    int i=0;
    FILE *p;
    p=fopen("vendedores.dat", "rb");
        if(p == NULL) return bR;
        while(obj.leerDeDisco(i++)){
            if ((strcmp(pal, obj.getdni())==0)||(strcmp(pal, obj.getCuil())==0)){
                gotoxy(x,y+1);
                cout<<"REINGRESE POR FAVOR: ";
                bR=false;
                return bR;
            }
        }
    fclose(p);
    return bR;
}

bool verificar_Legajo (int leg, int x, int y){
    bool bR=true;
    vendedor obj;
    int i=0;
    FILE *p;
    p=fopen("vendedores.dat", "rb");
        if(p == NULL) return bR;
        while(obj.leerDeDisco(i++)){
            if (leg == obj.getLegajo()){
                gotoxy(x,y+1);
                 MessageBox(NULL, "CODIGO INEXISTENTE", "ERROR", MB_OK|MB_ICONERROR);
                bR=false;
                return bR;
            }
        }
    fclose(p);
    return bR;
}

void mostrar_Vendedores(){
    vendedor obj;
    int i=0;
    system ("cls");
    while (obj.leerDeDisco(i++)){
        obj.mostrar();
        cout << "-----------------"<< endl;
        }
    getch();
}

void mostrarUsuario(int leg){
    vendedor obj;
    int i=0;
    while (obj.leerDeDisco(i++)){
        if (obj.getLegajo()==leg){
            dibujarCuadro(75,2,117,4);
            gotoxy(80,3);
            if(obj.getCargo()==1){
                cout<< "VENDEDOR: ";
                cout<<obj.getApellido()<<" ";
                cout<<obj.getnombre();
            }
            else{
                cout<< "SUPERVISOR: ";
                cout<<obj.getApellido()<<" ";
                cout<<obj.getnombre();
            }
        }
    }
}


bool cadenacero(char cadena[]){
if (cadena[0]=='0') return false;
return true;

}


void cambiar_clave(int leg){
    vendedor v;
    bool reintente=false;
    char nuevaclave[25],nuevaclave2[25],claveactual[25];
    int i=0,ban;
    system("cls");

    while (v.leerDeDisco(i++)){
        if (v.getLegajo()== leg ){
           do{
                   rlutil::setColor(4);
            dibujarCuadro(106,25,117,27);
            rlutil::setColor(2);
            gotoxy (107,26);cout << "0|CANCELAR";
            dibujarCuadro(2,1,119,29);
            dibujarCuadro(40,1,80,3);
            gotoxy(48,2);cout << "Hola " << v.getnombre() << " " << v.getApellido() << endl;
            gotoxy(48,6);cout << "INGRESE SU CLAVE ACTUAL: " ;
            cargarCadena(claveactual,25);
            if(cadenacero(claveactual)==false) {
                    MessageBox(NULL, "CAMBIO DE CLAVE CANCELADO", "CLAVE", MB_OK|MB_ICONINFORMATION);
                    return;}
            ban=strcmp(v.getcontrasena(),claveactual);
            if(ban!=0){
                MessageBox(NULL, "CLAVE INCORRECTA", "CLAVE", MB_OK|MB_ICONERROR);
                system("cls");}
            }while(ban!=0);
            do{
            if (ban==0){

                 if (reintente==true){
                        gotoxy(48,2);cout << "Hola " << v.getnombre() << " " << v.getApellido() << endl;;
                  rlutil::setColor(4);
                  dibujarCuadro(106,25,117,27);
                  rlutil::setColor(2);
                  gotoxy (107,26);cout << "0|CANCELAR";
                  dibujarCuadro(2,1,119,29);
                  dibujarCuadro(40,1,80,3);
                 }

                gotoxy(48,8);cout << "INGRESE SU NUEVA CLAVE: " ;
                cargarCadena(nuevaclave,25);
                if (strcmp(claveactual,nuevaclave)!=0){
                if(cadenacero(nuevaclave)==false){
                        MessageBox(NULL, "CAMBIO DE CLAVE CANCELADO", "CLAVE", MB_OK|MB_ICONINFORMATION);
                        return;}
                gotoxy(48,10);cout << "REINGRESE SU NUEVA CLAVE: ";
                cargarCadena(nuevaclave2,25);
                if(cadenacero(nuevaclave2)==false) {
                        MessageBox(NULL, "CAMBIO DE CLAVE CANCELADO", "CLAVE", MB_OK|MB_ICONINFORMATION);
                        return;}
                 if (strcmp(nuevaclave,nuevaclave2)==0){
                    MessageBox(NULL, "CLAVE CAMBIADA", "CLAVE", MB_OK|MB_ICONINFORMATION);
                    v.setContrasena(nuevaclave2);
                    v.guardarEnDisco(i-1);
                    return;
                 }
                 else {
                    MessageBox(NULL, "LAS CLAVES NO COINCIDEN", "CLAVE", MB_OK|MB_ICONERROR);
                    reintente=true;
                 }}
                 else {
                    MessageBox(NULL, "LA NUEVA CLAVE NO PUEDE SER IGUAL A LA ACTUAL", "CLAVE", MB_OK|MB_ICONERROR);
                    reintente=true;
                 }
                 }
                    else {
                    MessageBox(NULL, "CLAVE INCORRECTA", "CLAVE", MB_OK|MB_ICONERROR);

                 }
                 system("cls");
                }while(reintente);





        }
    } }
