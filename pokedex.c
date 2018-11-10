#include <stdio.h>
#include <stdlib.h>
#include "pokedex.h"


const char NombreArchivo[30]=ruta_al_archivo_de_la_lista;

int cuantosPokemonesTengo()
{
    long v;
    FILE* archi=fopen(NombreArchivo, "r+b");
    if (archi != NULL)
    {

        fseek(archi,0,SEEK_END);
        v=ftell(archi);
        v=v/sizeof(nodo_archivo);

    }
    else
    {
        printf("El archivo no se puede abrir, se retorno 0\n");
        v=0;
    }
    fclose(archi);
    return v;
}


///.................MOSTRAR TODOS INDISCRIMINADAMENTE................................................................................................

void MostarCeldaPokemon(Celda arrayPokemon[],int validos)
{
    int i=0;
    while(i<validos)
    {
        MostrarCelda(arrayPokemon[i]);
        i++;
    }
}

void MostrarCelda (Celda a_mostrar)
{
    if (a_mostrar.lista != NULL)
    {
        printf("%s\n", a_mostrar.TipoDePokemon);
        recorrer_y_mostrar(a_mostrar.lista);
    }
    else
    {
        printf("Usted No dispone de Pokemones de ese tipo\n");
    }

}

///..................MOSTRAR POR TIPO...............................................................................................................

void mostrarPokemonesPorTipo (Celda arrayPokemon[], int validos)
{
    char tipoDePokemon [30];
    int posicion;
    do
    {
        ingresarTipoDePokemon(tipoDePokemon);
        posicion=BuscarPosicionArray(arrayPokemon, tipoDePokemon, validos);
        if (posicion ==-1)
        {
            printf("\nUsted  no tiene pokemones de ese tipo.\n");
            strcpy(tipoDePokemon, "salir");
        }
        system("cls");
    }
    while (posicion == -1 && strcmp(tipoDePokemon, "salir")!=0);
    if (strcmp(tipoDePokemon, "salir")!=0)
    {
        MostrarCelda(arrayPokemon[posicion]);
    }

}

///........................CARGAR LAS POKEMONES........................................................................

int CargarPokemonesA_LaPokedex(Celda ArrayPokemon[],int validos) ///CREAR Y CARGA UNA ESTRUCTURA COMUN A LOS NODOS (POKEMONES)
{
    char control='s';
    nodo_archivo pokemon2;

    while(control=='s'&&(cuantosPokemonesTengo()<151))
    {
        pokemon2=cargar_nodo();
        validos=CargarEnLaPokedex(ArrayPokemon,pokemon2,validos);
        system("cls");
        printf("Desea seguir cargando Pokemones a la Pokedex?\n");
        fflush(stdin);
        scanf("%c",&control);
    }

    return validos;
}

int CargarEnLaPokedex(Celda ArrayPokemon[],nodo_archivo poke,int validos)
{
    nodo* aux=crear_nodo(poke);
    int posicion;
    posicion=BuscarPosicionArray(ArrayPokemon,poke.TipoDePokemon,validos);
    if(posicion==-1)
    {
        validos=AgregarTipoDePokemon(ArrayPokemon,poke.TipoDePokemon,validos);
        posicion=validos-1;

    }
    ArrayPokemon[posicion].lista=agregar_al_principio_de_esta(ArrayPokemon[posicion].lista,aux);
    return validos;
}
///............................BUSCA Y DEVULVE POSICION DEL ARREGLO DONDE ESTA LA CELDA DONDE ESTA LA LISTA CON LOS POKEMONES DE ESE TIPO BUSCADO....
int BuscarPosicionArray(Celda arrayPokemon[],char TipoDePokemon2[],int validos)
{

    int rta=-1;
    int i=0;
    while((i<validos) && (rta==-1))
    {
        if(strcmp(arrayPokemon[i].TipoDePokemon,TipoDePokemon2)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

///...........................AGREGAR UNA CELDA CON UN NUEVO TIPO DE POKEMON Y ACTUALIZA LOS VALIDOS.........................................................................
int AgregarTipoDePokemon(Celda arrayPokemon[],char TipoDePokemon2[],int validos)
{
    strcpy(arrayPokemon[validos].TipoDePokemon,TipoDePokemon2);
    arrayPokemon[validos].lista=inic_nodo();
    validos++;
    return validos;
}

///..............RECUPERA Y ACOMODA LOS REGFISTROS GUARDADOS EN EL ARCHIVO PARA COMENZAR CON EL PROGRAMA............................................


int recurperarCeldasDelArchivo (Celda arrayPokemon [], int validosArreglo)
{
    int posicion=0;
    nodo_archivo registro;
    FILE* archivo=fopen(NombreArchivo, "rb");
    if (archivo != NULL)
    {
        rewind(archivo);
        while (fread(&registro, sizeof(nodo_archivo), 1, archivo)>0)
        {
            posicion=BuscarPosicionArray(arrayPokemon, registro.TipoDePokemon,validosArreglo);
            if (posicion == -1)
            {
                validosArreglo=AgregarTipoDePokemon(arrayPokemon, registro.TipoDePokemon, validosArreglo);
                posicion=BuscarPosicionArray(arrayPokemon, registro.TipoDePokemon,validosArreglo);

            }
            arrayPokemon[posicion].lista=agregar_al_principio_de_esta(arrayPokemon[posicion].lista, crear_nodo(registro));
        }


    }
    else
    {
        validosArreglo=0;
    }
    fclose(archivo);
    return validosArreglo;
}

///..........................................ACTUALIZA LA INFORMACION EN EL ARCHIVO.................................................................

void actualizaArchivo (Celda arrayPokemon[], int validos)
{
    int i=0;
    FILE* archi=fopen(NombreArchivo, "wb");

    for(i=0; i<validos; i++)
    {
        guardaCelda(arrayPokemon[i], archi);
    }
    fclose(archi);

}


void guardaCelda (Celda a_guardar, FILE* archi)
{
    guardar_lista_en_un_archivo(a_guardar.lista,archi);
}


///...........................SUBMENUS DEL MENU PRINCIPAL QUE LLAMAN A LAS FUNCIONES ANTERIORES......................................................
int subMenuCargarPokemones(Celda arrayPokemon[],int validos)
{
    system("cls");
    validos=CargarPokemonesA_LaPokedex(arrayPokemon, validos);
    actualizaArchivo(arrayPokemon, validos);
    system("pause");
    system("cls");
    return validos;
}

void subMenuLiberarPokemon (Celda arrayPokemon [], int validos)
{
    char tipoDepokemon [30];
    int numPokedex=-1;
    int posDelArray;
    if (validos>0)
    {
        ingresarTipoDePokemon(tipoDepokemon);
        system("cls");
        posDelArray=BuscarPosicionArray(arrayPokemon, tipoDepokemon, validos);
        if (posDelArray != -1 && (strcmp(tipoDepokemon,"salir")!=0))
        {
            MostrarCelda(arrayPokemon[posDelArray]);
            if (arrayPokemon[posDelArray].lista != inic_lista())
            {
                printf("Ingrese el numero de Pokedex del pokemon a liberar:\n");
                fflush(stdin);
                scanf("%i", &numPokedex);
                arrayPokemon[posDelArray].lista=borrar_nodo(arrayPokemon[posDelArray].lista,numPokedex);
                if(inic_lista()==buscar_nodo(arrayPokemon[posDelArray].lista, numPokedex))
                {
                    printf("El pokemon fue liberado con exito\n");
                }
                else
                {
                    printf("El pokemon no se pudo liberar\n");
                }

            }
        }
        else
        {
            if(strcmp(tipoDepokemon,"salir")!=0)
            {
                printf("Usted no dispone de pokemones de ese tipo todavia\n");
                system("pause");
            }
        }
    }
    else
    {
        if(strcmp(tipoDepokemon,"salir")!=0)
        {
            printf("Usted no dispone de Pokemones para liberar\n");
            system("pause");
        }
    }
    system("cls");
}


void subMenuModificarPokemon (Celda arrayPokemon [], int validos)
{
    char tipoDepokemon [30];
    int numPokedex=-1;
    int posDelArray;
    nodo* auxiliar;
    if (validos > 0)
    {
        ingresarTipoDePokemon(tipoDepokemon);
        posDelArray=BuscarPosicionArray(arrayPokemon, tipoDepokemon, validos);
        if (posDelArray != -1)
        {
            MostrarCelda(arrayPokemon[posDelArray]);
            if (arrayPokemon[posDelArray].lista != inic_lista())
            {
                printf("Ingrese el numero de Pokedex del pokemon a modificar:\n");
                fflush(stdin);
                scanf("%i", &numPokedex);
                auxiliar=buscar_nodo(arrayPokemon[posDelArray].lista,numPokedex);
                auxiliar->campos=modificar_nodo(auxiliar->campos.NroPokedex);
            }
        }
        else
        {
            printf("Usted no dispone de ese tipo de pokemon todavia\n");
        }
    }
    else
    {
        printf("Usted no dispone de Pokemones para modificar\n");
    }
    system("pause");
    system("cls");

}

void subMenuMostrarListado(Celda arrayPokemon[],int validos)
{
    int opcionSeleccionada=1,Pkbuscar;
    char tipoDePokemon[12];
    system("cls");
    do
    {
        escribir(55,6,"----------Menu Listado Pokemon----------\n");
        escribir(60,8,"1).Mostrar Todos\n");
        escribir(60,10,"2).Mostrar por Tipo de Pokemon\n");
        escribir(60,12,"3).Mostrar por Nro de Pokedex\n");
        escribir(60,14,"0).Exit\n");
        escribir(55,16,"--------------------------------\n");

        opcionSeleccionada= menuG(4,3);
        gotoxy(9,14);
        switch(opcionSeleccionada)
        {
        case 1:
            system("cls");
            if (validos > 0)
            {
                MostarCeldaPokemon(arrayPokemon, validos);
                system("pause");
            }
            else
            {
                printf("Usted no tiene pokemones para mostrar\n");
                system("pause");
            }
            system("cls");
            opcionSeleccionada=1;
            break;
        case 2:
            if (validos >0)
            {
                mostrarPokemonesPorTipo(arrayPokemon, validos);
            }
            else
            {
                printf("No hay pokemones de ningun tipo para mostrar\n");
                system("pause");
            }
            system("cls");
            opcionSeleccionada=1;
            break;
        case 3:
            system("cls");
            printf("Ingrese numero de pokedex a mostrar:\n");
            scanf("%i",&Pkbuscar);
            system("cls");
            ImagenPokemon(Pkbuscar);
            mostrar_nodo(buscarPokemon(arrayPokemon,validos,Pkbuscar));
            system("pause");
            system("cls");
            opcionSeleccionada=1;
            break;
        case 0:
            opcionSeleccionada=0;
            break;
        }
    }
    while(opcionSeleccionada==1);
    system("cls");
}


void subMenuMostrarCantidadDePokemon()
{
    unsigned cantidadDePokemons=cuantosPokemonesTengo();
    gotoxy(65,16);
    printf("Usted tiene %d Pokemones\n", cantidadDePokemons);
    system("pause");
    system("cls");
}

void ImagenPokemon(int numeroPkdx)
{
    FILE *f;
    char nombre [100];
    sprintf(nombre,"pokepack/%d.txt", numeroPkdx);
    f=fopen(nombre,"rb");
    char a;
    if(f==NULL)
    {
        printf("Error al abrir el fichero\n");
    }
    else
    {
        while(fread(&a, sizeof(char), 1, f)>0)
            printf("%c",a);
    }
    printf("\n");
    fclose(f);
}

///.............................batallaa..............................................................

void subMenuBatallaPokemon (Celda arrayPokemon [], int validos)
{

    int opcionSelecionada=1;
    system("cls");
    do
    {

        escribir(55,6,"----------Menu Batalla Pokemon----------\n");
        escribir(60,8,"1).PvP\n");
        escribir(60,10,"2).Player vs Oak\n");
        escribir(60,12,"0).Exit\n");
        escribir(55,14,"--------------------------------\n");

        opcionSelecionada= menuG(3,3);
        gotoxy(9,12);
        switch (opcionSelecionada)
        {
        case 1:
            system("cls");
            unoContraUno (arrayPokemon, validos);
            system("pause");
            system("cls");
            opcionSelecionada=1;
            break;
        case 2:
            system("cls");
            unoContraPc(arrayPokemon, validos);
            system("pause");
            system("cls");
            opcionSelecionada=1;
            break;
        case 0:
            opcionSelecionada=0;
            break;
        }
    }
    while(opcionSelecionada==1);


}


void unoContraUno (Celda arrayPokemon [], int validos)
{
    fila pokemonesJugador1=inic_fila(pokemonesJugador1);
    fila pokemonesJugador2=inic_fila(pokemonesJugador2);
    printf("Jugador1:\n");
    pokemonesJugador1=elegirPokemones(arrayPokemon, validos);
    system("pause");
    printf("Estos son tus pokemones Jugador1:\n");
    mostrarEquipo(pokemonesJugador1);
    system("pause");
    system("cls");
    printf("Jugador2:\n");
    pokemonesJugador2=elegirPokemones(arrayPokemon, validos);
    system("pause");
    printf("Estos son tus pokemones Jugador2:\n");
    mostrarEquipo(pokemonesJugador2);
    system("pause");
    system("cls");
    batalla(pokemonesJugador1, pokemonesJugador2,0);
}

void unoContraPc (Celda arrayPokemon[], int validos)
{
    fila pokemonesJ1=inic_fila(pokemonesJ1);
    fila pokemonesPc=inic_fila(pokemonesPc);
    pokemonesJ1=elegirPokemones(arrayPokemon, validos);
    printf("Sus Pokemones\n");
    mostrarEquipo(pokemonesJ1);
    system("pause");
    system("cls");
    pokemonesPc=elegirPokemonesAutomaticamente(arrayPokemon, validos);
    mostrarEquipo(pokemonesPc);
    system("pause");
    system("cls");
    batalla(pokemonesJ1, pokemonesPc,1);
}

void mostrarEquipo (fila j1)
{
    nodo3* arbol=inic_arbol();
    arbol=listaAarbol(j1.lista);
    mostrar_arbol(arbol);
}

void batalla (fila pokemonesj1, fila pokemonesj2,int flag)
{
    nodo* j1;
    nodo* j2;
    int i=22, j=22, p1=1, p2=1, cont1=0, cont2=0;
    system("cls");
    char J2[5];
    if(flag==0)
    {
        strcpy(J2,"J2");
    }
    else
    {
        strcpy(J2,"Oak");
    }
    j1=sacar_copia_de(pokemonesj1.lista);
    pokemonesj1=eliminar_elemento_de_la(pokemonesj1);
    j2=sacar_copia_de(pokemonesj2.lista);
    pokemonesj2=eliminar_elemento_de_la(pokemonesj2);
    tamanio_de_la_consola posicionDelCursor;
    while (cont1<6 && cont2<6)
    {
        while (j1->campos.Salud >0 && j2->campos.Salud >0)
        {
            gotoxy(40,6);
            printf("Pokemon de J1:\n");
            mostrarJ1(j1);
            gotoxy(75,4);
            printf("VS\n");
            gotoxy(100,6);
            printf("Pokemon de %s:\n",J2);
            mostrarJ2(j2);
            Sleep(300);

            if (j1->campos.Ataque > j2->campos.Defensa)
            {
                j2->campos.Salud=j2->campos.Salud-((j1->campos.Ataque)-(j2->campos.Defensa));
            }
            else
            {
                j2->campos.Salud=j2->campos.Salud-((j2->campos.Defensa)/(j1->campos.Ataque));
            }
            if (j1->campos.Salud <=0)
            {
                j1->campos.Salud=0;
            }

            if (j2->campos.Ataque > j1->campos.Defensa)
            {
                j1->campos.Salud=j1->campos.Salud-((j2->campos.Ataque)-(j1->campos.Defensa));
            }
            else
            {
                j1->campos.Salud=j1->campos.Salud-((j1->campos.Defensa)/(j2->campos.Ataque));

            }
            if (j2->campos.Salud <=0)
            {
                j2->campos.Salud=0;
            }
            gotoxy(40,6);
            printf("Pokemon de J1:\n");
            mostrarJ1(j1);
            gotoxy(75,4);
            printf("VS\n");
            gotoxy(100,6);
            printf("Pokemon de %s:  \n",J2);
            mostrarJ2(j2);
            Sleep(300);
        }
        if (j1->campos.Salud <=0)
        {
            gotoxy(40,18);
            printf("Pokemones derrotados J1:\n");
            gotoxy(40, i+1);
            printf("%i- %s del jugador 1 has fainted \n",p1,j1->campos.Nombre);
            Sleep(3000);
            if(!fila_vacia(pokemonesj1))
            {
                j1=sacar_copia_de(pokemonesj1.lista);
                pokemonesj1=eliminar_elemento_de_la(pokemonesj1);
            }
            cont1++;
            p1++;
            i++;
        }
        if (j2->campos.Salud <= 0)
        {
            gotoxy(100,18);
            printf("Pokemones derrotados %s:  \n",J2);
            gotoxy(100, j+1);
            printf("%i- %s del jugador 2 has fainted \n",p2,j2->campos.Nombre);
            Sleep(3000);
            if(!fila_vacia(pokemonesj2))
            {
                j2=sacar_copia_de(pokemonesj2.lista);
                pokemonesj2=eliminar_elemento_de_la(pokemonesj2);
            }
            cont2++;
            p2++;
            j++;
        }

    }
    if (fila_vacia(pokemonesj1) && fila_vacia(pokemonesj2))
    {
        gotoxy(70,30);
        printf("Es un Empate!\n");
    }
    if (fila_vacia(pokemonesj1) && !fila_vacia(pokemonesj2))
    {
        gotoxy(70,30);
        printf("Gano %s!\n",J2);
    }
    if (fila_vacia(pokemonesj2) && !fila_vacia(pokemonesj1))
    {
        gotoxy(70,30);
        printf("Gano J1!\n");
    }
}

fila elegirPokemones (Celda arrayPokemon [], int validos)
{
    printf("Elija %d pokemons\n", cantidadEquipo);
    int i=0;
    int nropoke;
    int posicion=-1;
    fila filita=inic_fila(filita);
    nodo* pokemon;
    nodo* pokemon2;
    for (i=0; i<cantidadEquipo; i++)
    {
        do
        {
            posicion=buscar_pos_lista (arrayPokemon, validos);
            printf("Indique el pokemon numero %d:\n", i+1);
            fflush(stdin);
            scanf("%d", &nropoke);
            pokemon=buscar_nodo(arrayPokemon[posicion].lista, nropoke);
            if (pokemon ==inic_lista())
                printf("Numero de pokemon no valido. Reingrese.\n");
        }
        while (pokemon ==inic_lista());
        pokemon2=sacar_copia_de(pokemon);
        filita=agregar_en_esta(filita, pokemon2);
    }
    return filita;
}


int buscar_pos_lista (Celda arrayPokemon [], int validos)
{
    char tipoDePokemon [30];
    char control='s';
    int posicion;
    do
    {
        ingresarTipoDePokemon(tipoDePokemon);
        posicion=BuscarPosicionArray(arrayPokemon, tipoDePokemon, validos);
        if (posicion ==-1)
        {
            printf("\nUsted  no tiene pokemones de ese tipo.\n");
            strcpy(tipoDePokemon, "salir");
        }
    }
    while (posicion == -1 && strcmp(tipoDePokemon, "salir")!=0);
    printf("Desea mostrar la lista de este tipo s/n\n");
    fflush(stdin);
    scanf("%c", &control);
    if (strcmp(tipoDePokemon, "salir")!=0 && control =='s')
    {
        MostrarCelda(arrayPokemon[posicion]);
    }

    return posicion;
}


fila elegirPokemonesAutomaticamente (Celda arrayPokemon [], int validos)
{
    srand(time(NULL));
    int Nropokemon=0;
    nodo* pokemon;
    fila aDevolver=inic_fila(aDevolver);
    int i;
    for (i=0; i<cantidadEquipo; i++)
    {

        Nropokemon=rand()%151;
        printf("%d", Nropokemon);
        pokemon=buscarPokemon(arrayPokemon, validos, Nropokemon);
        aDevolver=agregar_en_esta(aDevolver, pokemon);
    }

    return aDevolver;
}


nodo* buscarPokemon (Celda arrayPokemon [], int validos, int NroPokedex)
{
    nodo* pokemonADevolver=inic_nodo();
    int pos=0;
    while (pos<validos && pokemonADevolver == inic_nodo())
    {
        pokemonADevolver=buscar_nodo(arrayPokemon[pos].lista, NroPokedex);
        pos++;
    }
    if (pokemonADevolver != NULL)
    {
        pokemonADevolver=sacar_copia_de(pokemonADevolver);
    }
    return pokemonADevolver;
}


nodo3* listaAarbol (nodo* lista)
{
    nodo* seguidora=lista;
    nodo3* arbol=inic_arbol();
    while (seguidora != inic_lista())
    {
        arbol=insertar_en_este(arbol, seguidora->campos);
        seguidora=seguidora->siguiente;
    }
    return arbol;
}


tamanio_de_la_consola posActualDelCursor ()
{
    POINT cursor;
    tamanio_de_la_consola posicion;
    GetCursorPos(&cursor);
    posicion.columns=cursor.x;
    posicion.rows=cursor.y;

    return posicion;
}
///MENU GOTOXY
void escribir(int x, int y, char palabra[])
{
    gotoxy(x,y);
    printf("%s",palabra);
}


int menuG(int n,int posicionInic)
{
    hidecursor(0);
    int opcionSeleccionada = 1;  // Indica la opcionSeleccionada

    int tecla;

    int repite = 1; // controla el bucle para regresar a la rutina que lo llamo, al presionar ENTER

    do
    {
        //system("cls");
        system("color 7c");
        gotoxy(55,3+(opcionSeleccionada*2)+3);
        printf("==>");

        do
        {
            tecla = getch();
        }
        while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);

        switch (tecla)
        {

        case ARRIBA:   // En caso que se presione ARRIBA

            gotoxy(55, 3+ (opcionSeleccionada*2)+3);
            printf( "   " );
            opcionSeleccionada--;

            if (opcionSeleccionada < 1)
            {
                opcionSeleccionada = n;
            }

            break;

        case ABAJO:
            gotoxy(55, 3 + (opcionSeleccionada*2)+3);
            printf( "   " );
            opcionSeleccionada++;

            if (opcionSeleccionada > n)
            {
                opcionSeleccionada = 1;
            }

            break;

        case ENTER:
            repite = 0;
            break;
        }

    }
    while (repite);
    system("cls");

    return opcionSeleccionada;
}

int menuInicial(int n,int posicionInic)
{
    hidecursor(0);
    int opcionSeleccionada = 1;  // Indica la opcionSeleccionada

    int tecla;

    int repite = 1; // controla el bucle para regresar a la rutina que lo llamo, al presionar ENTER

    do
    {
        //system("cls");
        system("color 7c");
        gotoxy(55,3+(opcionSeleccionada*2)+17);
        printf("==>");

        do
        {
            tecla = getch();
        }
        while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);

        switch (tecla)
        {

        case ARRIBA:   // En caso que se presione ARRIBA

            gotoxy(55, 3+ (opcionSeleccionada*2)+17);
            printf( "   " );
            opcionSeleccionada--;

            if (opcionSeleccionada < 1)
            {
                opcionSeleccionada = n;
            }

            break;

        case ABAJO:
            gotoxy(55, 3 + (opcionSeleccionada*2)+17);
            printf( "   " );
            opcionSeleccionada++;

            if (opcionSeleccionada > n)
            {
                opcionSeleccionada = 1;
            }

            break;

        case ENTER:
            repite = 0;
            break;
        }

    }
    while (repite);
    system("cls");

    return opcionSeleccionada;
}
