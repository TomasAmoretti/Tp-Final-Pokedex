#include <stdio.h>
#include <stdlib.h>
#include "pokedex.h"
#include <windows.h>
#include <mmsystem.h>
#include <pthread.h>

void Cancion()
{
    while(TRUE)
        PlaySound(TEXT("Opening.wav"),NULL, SND_FILENAME);
}

void AltEnter()
{
    keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}

int main()
{
    AltEnter();
    pthread_t hilo0;
    int id0=0;
    pthread_create(&hilo0, NULL, (void *) &Cancion,(void *) &id0);
    MenuPrincipal(&hilo0);

    return 0;
}

void MenuPrincipal(pthread_t *hilo0)
{
    int opcionSeleccionada=1;
    int validos=0;
    Celda arrayPokemon[dimension];
    validos=recurperarCeldasDelArchivo(arrayPokemon, validos);

    do
    {

        escribir(55,2,"-------------------Menu Pokedex----------------------");
        gotoxy(0,4);
        ImagenPokemon(0);
        escribir(60,22,"1) Cargar Pokemones a la Pokedex ");
        escribir(60,24,"2) Liberar un Pokemon");
        escribir(60,26,"3) Modificar un Pokemon");
        escribir(60,28,"4) Batalla Pokemon");
        escribir(60,30,"5) Listado de Pokemon");
        escribir(60,32,"6) Cuantos Pokemones tengo?");
        escribir(60,34,"0) Salir");
        escribir(55,36,"----------------------------------------------------");

        opcionSeleccionada= menuInicial(7,3);
        gotoxy(9,20);

        switch(opcionSeleccionada)
        {
        case 1:
            if(cuantosPokemonesTengo()<151)
            {
                validos=subMenuCargarPokemones(arrayPokemon, validos);
                actualizaArchivo(arrayPokemon,validos);
            }
            else
            {
                system("cls");
                printf("La pokedex esta llena!!\n");
                system("pause");
                system("cls");
            }
            opcionSeleccionada=1;
            break;
        case 2:
            subMenuLiberarPokemon(arrayPokemon, validos);
            actualizaArchivo(arrayPokemon, validos);
            system("cls");
            opcionSeleccionada=1;
            break;
        case 3:
            subMenuModificarPokemon(arrayPokemon, validos);
            actualizaArchivo(arrayPokemon, validos);
            system("cls");
            opcionSeleccionada=1;
            break;
        case 4:
            subMenuBatallaPokemon(arrayPokemon, validos);
            system("cls");
            opcionSeleccionada=1;
            break;
        case 5:
            subMenuMostrarListado(arrayPokemon,validos);
            system("cls");
            opcionSeleccionada=1;
            break;
        case 6:
            subMenuMostrarCantidadDePokemon();
            system("cls");
            opcionSeleccionada=1;
            break;
        case 0:
            opcionSeleccionada=0;
            exit(0);
            break;

        }
    }while(opcionSeleccionada==1);
    actualizaArchivo(arrayPokemon, validos);
}
