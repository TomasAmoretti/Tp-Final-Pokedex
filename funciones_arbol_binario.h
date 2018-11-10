#ifndef ARBOL_BINARIO_FUNCIONES_H_INCLUDED
#define ARBOL_BINARIO_FUNCIONES_H_INCLUDED
#include <string.h>
#include<conio.h>
#include <dos.h>
#include <windows.h>
#include <winuser.h>
#include "FILAS.H"


typedef struct
{
    nodo_archivo campos;
    struct nodo3* izquierda;
    struct nodo3* derecha;
}nodo3;
typedef struct
{
    int columns, rows;
}tamanio_de_la_consola;

///.......................................................
/*FUNCIONES PARA MOSTRAR EL ARBOL*/
tamanio_de_la_consola obtener_area_de_la_consola ();
int gotoxy(int , int );
void hidecursor(int ver);
void mostrar_arbol_izquierda(nodo3*, tamanio_de_la_consola);
void mostrar_arbol_derecha(nodo3*, tamanio_de_la_consola, int );
void dibuja_lineas_izquierda(tamanio_de_la_consola);
void dibuja_lineas_derecha (tamanio_de_la_consola, int);
///.........................................................




nodo3* inic_arbol ();
nodo3* inic_nodo3 ();
nodo3* crear_nodo3 (nodo_archivo);
int esta_en_este (nodo3*, int);
int suma_de_un_campo_en_este (nodo3*);
nodo_archivo cargar_nodo3 ();
void mostrar_nodo3(nodo3*, tamanio_de_la_consola);
nodo3* insertar_en_este (nodo3*, nodo_archivo);
/*void mostrar_en_preorder_este(nodo3*);
void mostrar_en_orden_este(nodo3*);
void mostrar_en_postorder_este(nodo3*);*/
nodo3* cargar_este (nodo3*);
int es_hoja_este_nodo (nodo3* );
nodo3* buscar_nodo_en_este (nodo3* , int);
///..........Borrar_nodo......................................
nodo3* borrar_nodo3 (nodo3*, int);
nodo3* nodo_mas_derecha_de_este (nodo3*);
nodo3* nodo_mas_izquierda_de_este (nodo3*);
///...........................................................
tamanio_de_la_consola posActualDelCursor ();


#endif // ARBOL_BINARIO_FUNCIONES_H_INCLUDED
