#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <windows.h>


void cargarCadena(char *, int);
int verificar_usuario(int, char[]);
bool cadenaVacia(char *, int, int, int);
void dibujarCuadro(int,int,int,int);

//------------------ PRODUCTOS ---------------------
void alta_producto();
void mostrar_equipos();
int buscar_equipo(char*);
float buscar_equipo2(char*);
void modificar_stock(char*);
bool buscarRepetido (char*, int, int, int);
bool baja_Celular(int);
void modificar_Precio(char*);
int buscar_equipo_marca(char*);
int buscar_equipo_precio(float);
bool buscar_equipo_baja(char*);

//------------------ USUARIOS -------------------
void alta_Usuario();
int buscar_Usuario(int);
bool baja_Usuario();
void ver_usuarios();
bool buscarRepetido1(char*, int, int, int);
bool verificar_Legajo (int, int, int);
void mostrar_Vendedores();
bool listar_Vendedores();
void mostrarUsuario(int);
void cambiar_clave(int);

//------------------ VENTAS ----------------------
bool verif_Cant(int, char*);
void descontar_stock(char*, int);
int contarRegVenta();
int nroVenta();
void buscar_detalle(int);
void buscar_detalle(char*);
void buscar_detalle_legajo(int);
void detalle_fecha_DMA();
void devolver_stock(char*, int);

#endif // FUNCIONES_H_INCLUDED


