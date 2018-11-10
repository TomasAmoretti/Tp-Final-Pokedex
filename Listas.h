#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED
#define ruta_al_archivo_de_la_lista "registrosPokedex.bin"
typedef struct
{
    int valor;  /// campos
    int NroPokedex;
    char TipoDePokemon[30];
    char Nombre[30];
    int Nivel;
    int Ataque;
    int Salud;
    int Defensa;
}nodo_archivo;

typedef struct
{
    nodo_archivo campos; ///esto es para que ambos tengan los mismos campos y ASI pasar todo de una.
    struct nodo* siguiente;
} nodo;

///................................................................................................................................
nodo* inic_nodo ();
nodo* crear_nodo (nodo_archivo  /*y cualquier otro campo que tengo el nodo*/);
nodo* agregar_al_principio_de_esta (nodo*, nodo* );
nodo* inic_lista ();
nodo* buscar_nodo (nodo*, int);
nodo* borrar_nodo (nodo*, int /*o cualquier otra cosa como criterio de busqueda*/);
nodo* ultimo_nodo (nodo*);
nodo* sacar_copia_de (nodo*);
nodo* agregar_al_final_de_esta (nodo*, nodo*);
nodo* agregar_en_orden_en_esta (nodo* , nodo*);
nodo* borrar_lista (nodo* );
nodo* sumar_campo_de_esta (nodo*);
nodo* eliminar_primer_nodo_de_esta (nodo*);
nodo* eliminar_ultimo_nodo_de_esta(nodo*);
void mostrar_nodo (nodo* );
void recorrer_y_mostrar (nodo* );
nodo* cargar_datos_al_final_de_esta (nodo* );
nodo_archivo cargar_nodo ();
nodo* cargar_datos_al_principio_de_esta(nodo* );
void guardar_lista_en_un_archivo (nodo*, FILE*);
nodo* recuperar_lista_del_archivo (char []);
nodo* crear_lista_ordenada ();
int menu ();
nodo_archivo modificar_nodo (int);
///...........extra......................................
void ingresarTipoDePokemon (char []);
int qDENodoDeLaLista (nodo*);
int NroPokedexExiste(int);

#endif // LISTAS_H_INCLUDED
