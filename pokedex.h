#ifndef POKEDEX_H_INCLUDED
#define POKEDEX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include  <time.h>
#include "funciones_arbol_binario.h"
#define dimension 15
#define cantidadEquipo 6
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#include <windows.h>

typedef struct
{
    char TipoDePokemon[30];
    nodo* lista;
} Celda;

///Funciones
void MenuLogin();///Terminar
void MenuPrincipal();
int CargarPokemonesA_LaPokedex(Celda ArrayPokemon[], int);
int CargarEnLaPokedex(Celda ArrayPokemon[],nodo_archivo,int validos);
int BuscarPosicionArray(Celda arrayPokemon[],char TipoDePokemon2[],int validos);
int AgregarTipoDePokemon(Celda arraPokemon[],char TipoDePokemon2[],int validos);
void MostrarCelda (Celda a_mostrar);
void MostarCeldaPokemon(Celda arrayPokemon[],int validos);
void subMenuMostrarListado(Celda arrayPokemon[],int validos);
int recurperarCeldasDelArchivo (Celda arrayPokemon [], int validosArreglo);
void actualizaArchivo (Celda arrayPokemon[], int validos);
void guardaCelda (Celda a_guardar, FILE*);
void actualizaArchivo (Celda arrayPokemon[], int validos);
void guardaCelda (Celda a_guardar, FILE*);
int cuantosPokemonesTengo();
///Submenus del menu principal.
int subMenuCargarPokemones (Celda arrayPokemon [],int validos);
void subMenuLiberarPokemon (Celda arrayPokemon [], int validos);
void subMenuModificarPokemon (Celda arrayPokemon [], int validos);
void subMenuMostrarCantidadDePokemon();
///................funciones batalla...........................................
fila elegirPokemones (Celda arrayPokemon [], int validos);
void  unoContraUno (Celda arrayPokemon [], int validos);
void subMenuBatallaPokemon (Celda arrayPokemon [], int validos);
void mostrarEquipo (fila j1);
fila elegirPokemonesAutomaticamente (Celda arrayPokemon [], int validos);
nodo* buscarPokemon (Celda arrayPokemon [], int validos, int NroPokedex);
nodo3* listaAarbol (nodo* lista);
#endif // POKEDEX_H_INCLUDED
