#ifndef LIBRARY_FILAS_H_INCLUDED
#define LIBRARY_FILAS_H_INCLUDED
#include "Listas.h"

typedef struct
{
    nodo* lista;
    nodo* fin_lista;
}fila;

fila inic_fila (fila );
int fila_vacia (fila );
fila agregar_en_esta (fila, nodo* );
fila eliminar_elemento_de_la (fila );
void mostrar_fila (fila);


#endif // LIBRARY_FILAS_H_INCLUDED
