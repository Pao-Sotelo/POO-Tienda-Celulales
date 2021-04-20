#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED
#include "Fecha.h"

class vendedor{
private:
    char Dni [10];
    char Cuil [15];
    char Nombre [25];
    char Apellido [25];
    int Legajo;
    int Cargo; ///1 o 2
    char Contrasena[25];
    Fecha fechaIngreso;
    bool Estado;
public:
    vendedor(const char* d="DNI", const char* c="CUIT", const char* n="NOMBRE", const char* a="APELLIDO", int l=0, int car=1, const char* clave="DNI");
    void setDni(char*);
    void setCuil (char*);
    void setNombre(char*);
    void setApellido(char*);
    void setLegajo(int);
    void setCargo(int);
    void setContrasena (char*);
    void setFecha(Fecha);
    void setEstado(bool);
    char * getdni();
    char * getCuil();
    char * getnombre();
    char * getApellido();
    int getLegajo();
    int getCargo();
    char * getcontrasena();
    Fecha getFecha();
    bool getEstado();
    bool cargar();
    void mostrar();
    bool guardarEnDisco(int = -1);
    bool leerDeDisco(int);

};

bool cadenacero(char*);

#endif // VENDEDOR_H_INCLUDED
