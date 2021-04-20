#ifndef CELULAR_H_INCLUDED
#define CELULAR_H_INCLUDED

class celular {

private:
    char marca [20];
    char modelo [50];
    float precio;
    char codigo[20];
    int stock;
    bool Estado;

public:

    void setmarca(char*);
    void setmodelo (char*);
    void setprecio (float);
    void setcodigo (char*);
    void setstock(int);
    void setEstado(bool);
    char* getmarca  ();
    char* getmodelo ();
    float getprecio ();
    char* getcodigo ();
    int getstock();
    int getEstado();
    bool cargar();
    void mostrar();
    bool guardarEnDisco(int = -1);
    bool leerDeDisco(int);
};

#endif // CELULAR_H_INCLUDED
