#include <stdio.h>
#include <stdlib.h>
#define m 30
#include "Listas.h"



nodo* inic_nodo ()
{
    nodo* aux=NULL;
    return aux;
}

nodo* crear_nodo (nodo_archivo valores /*y cualquier otro campo que tengo el nodo*/)
{
    nodo* nuevo_nodo=(nodo*)malloc(sizeof (nodo));
    nuevo_nodo->campos=valores;
    nuevo_nodo->siguiente=inic_nodo();

    return nuevo_nodo;
}
nodo* sacar_copia_de (nodo* este)
{
    nodo* copia =crear_nodo(este->campos);
    return copia;
}
nodo* inic_lista ()
{
    nodo* retorno=NULL;
    return retorno;
}

nodo* agregar_al_principio_de_esta (nodo* lista, nodo* este_nodo)
{
    if (lista == inic_lista()) ///Si la lista ya esta vacia, simplemente ingreso el nodo.
    {
        lista=este_nodo;
    }
    else ///sino engancho el segundo a mi nuevo primer nodo, y ahora lista apunta este ultimo.
    {
        este_nodo->siguiente=lista;
        lista=este_nodo;
    }
    return lista; ///actualizo la informcion de la lista.
}



nodo* borrar_nodo (nodo* lista, int valor /*o cualquier otra cosa como criterio de busqueda*/)
{
    if (lista != inic_lista())
    {
        nodo* seguidora=lista;
        nodo* anterior=seguidora;
        if (lista->campos.NroPokedex == valor)
        {
            lista=lista->siguiente;
            free(seguidora);
        }
        else
        {
            while (seguidora != inic_nodo() && seguidora->campos.NroPokedex != valor)
            {
                anterior=seguidora;
                seguidora=seguidora->siguiente;
            }
            if (seguidora != inic_nodo())
            {
                anterior->siguiente=seguidora->siguiente;
                free(seguidora);
            }
            else
            {
                printf("No existe dicho pokemon\n");
            }


        }

    }
    else
    {
        printf("La lista de pokemons esta vacia\n");
    }
    return lista;
}


nodo* buscar_nodo (nodo* en_esta_lista, int con_este_valor)
{
    nodo* a_devolver=inic_lista();
    if (en_esta_lista == inic_lista())
    {
        //printf("La lista esta vacia\n");
    }
    else
    {
        nodo* seguidora=en_esta_lista;
        while (seguidora != inic_nodo() && seguidora->campos.NroPokedex != con_este_valor)
        {
            seguidora=seguidora->siguiente;
        }
        if (seguidora == inic_nodo())
        {
            //printf("No existe nodo con ese valor\n");
            a_devolver=seguidora;
        }
        else
        {
            a_devolver=seguidora;
        }


    }
    return a_devolver;
}

int qDENodoDeLaLista (nodo* lista)
{
    nodo* seguidora=lista;
    int contador=0;
    while (seguidora != inic_lista())
    {
        contador++;
        seguidora=seguidora->siguiente;
    }
    return contador;
}

nodo* ultimo_nodo (nodo* lista)
{
    nodo* seguidora=lista;
    while (seguidora != inic_lista() && seguidora->siguiente != inic_lista())
    {
        seguidora=seguidora->siguiente;
    }
    return seguidora;
}

nodo* agregar_al_final_de_esta (nodo* lista, nodo* este_nodo)
{

    if (lista != inic_lista())
    {
        nodo* seguidora=ultimo_nodo(lista);
        seguidora->siguiente=este_nodo;
    }
    else
    {
        lista=este_nodo;
    }

    return lista;
}

nodo* agregar_en_orden_en_esta (nodo* lista, nodo* este_nodo)
{
    if (lista == inic_lista())
    {
        lista=este_nodo;
    }
    else
    {
        if (este_nodo->campos.NroPokedex < lista->campos.NroPokedex)
        {
            lista=agregar_al_principio_de_esta(lista, este_nodo);
            printf("B\n");
        }
        else
        {
            nodo* seguidora=lista;
            nodo* anterior=seguidora;
            while (seguidora != inic_lista() && este_nodo->campos.NroPokedex > seguidora->campos.NroPokedex)
            {
                anterior=seguidora;
                seguidora=seguidora->siguiente;
            }
            if (seguidora != inic_lista())
            {
                anterior->siguiente=este_nodo;
                este_nodo->siguiente=seguidora;

            }
            else
            {
                anterior->siguiente=este_nodo;
            }

        }
    }

    return lista;

}

nodo* borrar_lista (nodo* esta)
{

    nodo* seguidora=esta;
    nodo* anterior=seguidora;
    if (esta==inic_lista())
        printf("La lista ya esta vacia\n");
    else
    {

        while (seguidora != inic_lista())
        {
            seguidora=seguidora->siguiente;
            free(anterior);
            anterior=seguidora;
        }
    }

    return seguidora;
}

nodo* sumar_campo_de_esta (nodo* lista)
{
    int suma=0;
    nodo* seguidora=lista;
    while (seguidora != inic_lista())
    {
        suma=suma+seguidora->campos.valor;
        seguidora=seguidora->siguiente;
    }


    return suma;
}

nodo* eliminar_primer_nodo_de_esta (nodo* lista)
{
    nodo* seguidora=lista;
    if (lista!=NULL)
    {
        lista=lista->siguiente;
        free(seguidora);
    }

    return lista;
}

nodo* eliminar_ultimo_nodo_de_esta(nodo* lista)
{
    nodo* seguidora=lista;
    nodo* anterior=seguidora;
    while (seguidora->siguiente != inic_lista())
    {
        seguidora=seguidora->siguiente;
        anterior=seguidora;
    }
    anterior->siguiente=inic_nodo();
    free(seguidora);

    return lista;
}

void mostrar_nodo (nodo* a_mostrar)
{

    printf("Nro. Pokedex: %d                     \n",a_mostrar->campos.NroPokedex);
    printf("Nombre del Pokemon: %s               \n",a_mostrar->campos.Nombre);
    //printf("Tipo: %s\n",a_mostrar->campos.TipoDePokemon);
    printf("Ataque: %d                           \n",a_mostrar->campos.Ataque);
    printf("Defensa: %d                          \n",a_mostrar->campos.Defensa);
    printf("HP: %d                               \n",a_mostrar->campos.Salud);
    printf("Nivel: %d                            \n",a_mostrar->campos.Nivel);
}

void mostrarJ1 (nodo* a_mostrar)
{
    gotoxy(40,8);
    printf("Nro. Pokedex: %d  \n",a_mostrar->campos.NroPokedex);
    gotoxy(40,9);
    printf("Nombre del Pokemon: %s    \n",a_mostrar->campos.Nombre);
    gotoxy(40,10);
    printf("Ataque: %d \n",a_mostrar->campos.Ataque);
    gotoxy(40,11);
    printf("Defensa: %d \n",a_mostrar->campos.Defensa);
    gotoxy(40,12);
    printf("HP: %d \n",a_mostrar->campos.Salud);
    gotoxy(40,13);
    printf("Nivel: %d \n",a_mostrar->campos.Nivel);
}

void mostrarJ2 (nodo* a_mostrar)
{
    gotoxy(100,8);
    printf("Nro. Pokedex: %d    \n",a_mostrar->campos.NroPokedex);
    gotoxy(100,9);
    printf("Nombre del Pokemon: %s    \n",a_mostrar->campos.Nombre);
    gotoxy(100,10);
    printf("Ataque: %d \n",a_mostrar->campos.Ataque);
    gotoxy(100,11);
    printf("Defensa: %d \n",a_mostrar->campos.Defensa);
    gotoxy(100,12);
    printf("HP: %d \n",a_mostrar->campos.Salud);
    gotoxy(100,13);
    printf("Nivel: %d \n",a_mostrar->campos.Nivel);
}

void recorrer_y_mostrar (nodo* lista)
{
    nodo* seguidora=lista;
    while (seguidora != inic_lista())
    {
        printf("-----------------------------\n");
        mostrar_nodo(seguidora);
        printf("-----------------------------\n");
        seguidora=seguidora->siguiente;

    }

}


nodo* cargar_datos_al_final_de_esta (nodo* lista)
{
    nodo* seguidora=ultimo_nodo(lista);
    seguidora->campos=cargar_nodo();
    return lista;
}


nodo_archivo cargar_nodo ()
{
    nodo_archivo nuevos_valores;
    printf ("Ingrese el numero de Pokedex del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.NroPokedex);
    while (NroPokedexExiste(nuevos_valores.NroPokedex))
    {
        printf("Numero de Pokedex ya existe. Reingrese:\n");
        fflush(stdin);
        scanf("%d", &nuevos_valores.NroPokedex);
    }

    printf ("Ingrese el nombre del pokemon: \n");
    fflush(stdin);
    gets(nuevos_valores.Nombre);
    ingresarTipoDePokemon(nuevos_valores.TipoDePokemon);

    printf ("Ingrese el ataque del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Ataque);

    printf ("Ingrese la defensa del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Defensa);
    printf ("Ingrese la salud del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Salud);
    printf ("Ingrese el nivel del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Nivel);

    return nuevos_valores;
}

nodo_archivo modificar_nodo (int NroPokedex)
{
    nodo_archivo nuevos_valores;
    nuevos_valores.NroPokedex=NroPokedex;
    printf ("Ingrese el nombre del pokemon: \n");
    fflush(stdin);
    gets(nuevos_valores.Nombre);
    ingresarTipoDePokemon(nuevos_valores.TipoDePokemon);

    printf ("Ingrese el ataque del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Ataque);

    printf ("Ingrese la defensa del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Defensa);
    printf ("Ingrese la salud del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Salud);
    printf ("Ingrese el nivel del Pokemon: \n");
    fflush(stdin);
    scanf ("%i", &nuevos_valores.Nivel);

    return nuevos_valores;
}

void ingresarTipoDePokemon (char deNuevosValores [])
{
    int opcion=0;
    char respuesta [30];
    char flag='n';
    do
    {
        escribir(55,2,"Ingrese de que tipo es el pokemon:\n");
        escribir(65,8,"1. Planta\n");
        escribir(65,9,"2. Fuego\n");
        escribir(65,10,"3. Agua\n");
        escribir(65,11,"4. Volador\n");
        escribir(65,12,"5. Normal\n");
        escribir(65,13,"6. Bicho\n");
        escribir(65,14,"7. Tierra\n");
        escribir(65,15,"8. Electrico\n");
        escribir(65,16,"9. Lucha\n");
        escribir(65,17,"10. Psiquico\n");
        escribir(65,18,"11. Fantasma\n");
        escribir(65,19,"12. Dragon\n");
        escribir(65,20,"0. Cancelar\n");
        gotoxy(65,22);
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            strcpy(respuesta, "Planta");
            flag='s';
            break;
        case 2:
            strcpy(respuesta, "Fuego");
            flag='s';
            break;
        case 3:
            strcpy(respuesta, "Agua");
            flag='s';
            break;
        case 4:
            strcpy(respuesta, "Volador");
            flag='s';
            break;
        case 5:
            strcpy(respuesta, "Normal");
            flag='s';
            break;
        case 6:
            strcpy(respuesta, "Bicho");
            flag='s';
            break;
        case 7:
            strcpy(respuesta, "Tierra");
            flag='s';
            break;
        case 8:
            strcpy(respuesta, "Electrico");
            flag='s';
            break;
        case 9:
            strcpy(respuesta, "Lucha");
            flag='s';
            break;
        case 10:
            strcpy(respuesta, "Psiquico");
            flag='s';
            break;
        case 11:
            strcpy(respuesta, "Fantasma");
            flag='s';
            break;
        case 12:
            strcpy(respuesta, "Dragon");
            flag='s';
            break;
        case 0:
            strcpy(respuesta, "salir");
            flag='s';
            break;
        default:
            printf("Opcion Invalida. Reingrese.\n");
            break;
        }

    }
    while (flag != 's');
    strcpy(deNuevosValores, respuesta);

}

nodo* cargar_datos_al_principio_de_esta(nodo* lista)
{
    lista->campos=cargar_nodo();

    return lista;

}

void guardar_lista_en_un_archivo (nodo* lista, FILE* archi)
{
    nodo* seguidora=lista;
    while(seguidora != inic_lista())
    {
        fwrite(&seguidora->campos, sizeof(nodo_archivo),1, archi);
        seguidora=seguidora->siguiente;
    }
}

nodo* recuperar_lista_del_archivo ( char tipoDePokemom [])
{
    nodo_archivo registro;
    nodo* nuevo_nodo;
    nodo* lista=inic_lista();
    FILE* puntero_al_archivo=fopen(ruta_al_archivo_de_la_lista, "r+b");
    while (fread(&registro,sizeof(nodo_archivo),1,puntero_al_archivo)>0)
    {
        if (strcmp(registro.TipoDePokemon,tipoDePokemom)==0)
        {
            nuevo_nodo=crear_nodo(registro);
            lista=agregar_al_final_de_esta(lista,nuevo_nodo);
        }
    }
    return lista;
}

nodo* crear_lista_ordenada ()
{
    char control='s';
    nodo* lista=inic_lista();
    while (control!= 'n')
    {
        lista=agregar_en_orden_en_esta(lista, crear_nodo(cargar_nodo()));
        printf ("\nDesea cargar otro nodo? s/n\n");
        fflush (stdin);
        scanf("%c", &control);
    }

    return lista;
}

int menu ()
{
    int operacion;
    printf("---------Menu batalla---------\n"
           "1. PvP\n"
           "2. P vs Oak\n"
           "0. Salir\n");
    printf("------------------------------\n"
           "Seleccione una opcion:\n");
    scanf("%i", &operacion);
    system("cls");

    return operacion;
}


int NroPokedexExiste(int NroPokedex)
{

    nodo_archivo p;
    int flag = 0;
    FILE* archivo=fopen(ruta_al_archivo_de_la_lista, "rb");
    if (archivo != NULL)
    {
        rewind(archivo);
        while(fread(&p,sizeof(nodo_archivo),1,archivo)>0)
        {

            if(p.NroPokedex == NroPokedex)
                flag = 1;
        }


    }
    fclose(archivo);

    return flag;
}
