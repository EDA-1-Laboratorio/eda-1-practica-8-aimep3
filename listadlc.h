#ifndef LISTADLC_H
#define LISTADLC_H

#include <stdio.h>
#include <stdlib.h>

/* Definimos el tipo de dato genérico que almacenará la lista */
typedef int DATO;

/* Estructura del Nodo para la Lista Doblemente Ligada Circular */
typedef struct nodo_cir {
    DATO dato;
    struct nodo_cir *previo;
    struct nodo_cir *siguiente;
} nodo_cir;

/* Estructura de control de la Lista Doblemente Ligada Circular */
typedef struct lista_dlc {
    nodo_cir *cabeza;
    int longitud;
} ListaDLC;

/* Declaración de operaciones básicas (Prototipos) */

/* Creación */
nodo_cir *crear_elemento(DATO dato);
ListaDLC *crear_lista(void);

/* Inserción */
void insertar_inicio(ListaDLC *lista, DATO dato);
void insertar_final(ListaDLC *lista, DATO dato);
void insertar_en_posicion(ListaDLC *lista, DATO dato, int posicion);

/* Eliminación */
DATO eliminar_inicio(ListaDLC *lista);
DATO eliminar_final(ListaDLC *lista);
DATO eliminar_en_posicion(ListaDLC *lista, int posicion);

/* Utilidades */
int buscar(ListaDLC *lista, DATO dato);
DATO obtener(ListaDLC *lista, int posicion);
int esta_vacia(ListaDLC *lista);
int longitud(ListaDLC *lista);
void imprimir_lista(ListaDLC *lista);
void imprimir_lista_reversa(ListaDLC *lista);
void liberar_lista(ListaDLC *lista);

#endif /* LISTADLC_H */