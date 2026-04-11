#include "listadlc.h"

/* Crea un nuevo nodo en memoria */
nodo_cir *crear_elemento(DATO dato) {
    nodo_cir *nuevo = (nodo_cir *)malloc(sizeof(nodo_cir));
    if (nuevo == NULL) return NULL;
    nuevo->dato = dato;
    nuevo->previo = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

/* Inicializa la estructura de control de la lista */
ListaDLC *crear_lista(void) {
    ListaDLC *lista = (ListaDLC *)malloc(sizeof(ListaDLC));
    if (lista == NULL) return NULL;
    lista->cabeza = NULL;
    lista->longitud = 0;
    return lista;
}

/* Inserta un nodo al inicio de la lista circular */
void insertar_inicio(ListaDLC *lista, DATO dato) {
    nodo_cir *nuevo = crear_elemento(dato);
    if (nuevo == NULL) return;

    if (lista->cabeza == NULL) {
        /* Inserción en lista vacía: el nodo se apunta a sí mismo */
        nuevo->siguiente = nuevo;
        nuevo->previo = nuevo;
        lista->cabeza = nuevo;
    } else {
        /* Inserción normal: conectamos con la cabeza actual y la cola (cabeza->previo) */
        nodo_cir *ultimo = lista->cabeza->previo;
        
        nuevo->siguiente = lista->cabeza;
        nuevo->previo = ultimo;
        
        lista->cabeza->previo = nuevo;
        ultimo->siguiente = nuevo;
        
        /* Actualizamos la cabeza al nuevo nodo */
        lista->cabeza = nuevo;
    }
    lista->longitud++;
}

/* Inserta un nodo al final de la lista circular */
void insertar_final(ListaDLC *lista, DATO dato) {
    nodo_cir *nuevo = crear_elemento(dato);
    if (nuevo == NULL) return;

    if (lista->cabeza == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->previo = nuevo;
        lista->cabeza = nuevo;
    } else {
        nodo_cir *ultimo = lista->cabeza->previo;
        
        nuevo->siguiente = lista->cabeza;
        nuevo->previo = ultimo;
        
        lista->cabeza->previo = nuevo;
        ultimo->siguiente = nuevo;
        /* A diferencia de insertar_inicio, aquí la cabeza NO cambia */
    }
    lista->longitud++;
}

/* Inserta un nodo en una posición específica (0-indexada) */
void insertar_en_posicion(ListaDLC *lista, DATO dato, int posicion) {
    if (posicion < 0 || posicion > lista->longitud) return;
    if (posicion == 0) { insertar_inicio(lista, dato); return; }
    if (posicion == lista->longitud) { insertar_final(lista, dato); return; }

    nodo_cir *nuevo = crear_elemento(dato);
    if (nuevo == NULL) return;

    nodo_cir *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++) {
        actual = actual->siguiente;
    }

    nuevo->previo = actual->previo;
    nuevo->siguiente = actual;
    actual->previo->siguiente = nuevo;
    actual->previo = nuevo;
    lista->longitud++;
}

/* Elimina el primer nodo y retorna su valor */
DATO eliminar_inicio(ListaDLC *lista) {
    if (lista->cabeza == NULL) return -1; // Retorno de error

    nodo_cir *eliminado = lista->cabeza;
    DATO dato = eliminado->dato;

    if (lista->longitud == 1) { 
        /* Si solo hay un elemento, la lista queda vacía */
        lista->cabeza = NULL;
    } else {
        nodo_cir *ultimo = lista->cabeza->previo;
        lista->cabeza = eliminado->siguiente;
        
        /* Reconectamos el círculo saltando el nodo eliminado */
        lista->cabeza->previo = ultimo;
        ultimo->siguiente = lista->cabeza;
    }

    free(eliminado);
    lista->longitud--;
    return dato;
}

/* Elimina el último nodo y retorna su valor */
DATO eliminar_final(ListaDLC *lista) {
    if (lista->cabeza == NULL) return -1;

    /* En una circular, llegar al final es O(1) */
    nodo_cir *eliminado = lista->cabeza->previo; 
    DATO dato = eliminado->dato;

    if (lista->longitud == 1) {
        lista->cabeza = NULL;
    } else {
        nodo_cir *nuevo_ultimo = eliminado->previo;
        nuevo_ultimo->siguiente = lista->cabeza;
        lista->cabeza->previo = nuevo_ultimo;
    }

    free(eliminado);
    lista->longitud--;
    return dato;
}

/* Elimina un nodo en una posición específica */
DATO eliminar_en_posicion(ListaDLC *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud) return -1;
    if (posicion == 0) return eliminar_inicio(lista);
    if (posicion == lista->longitud - 1) return eliminar_final(lista);

    nodo_cir *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++) {
        actual = actual->siguiente;
    }

    DATO dato = actual->dato;
    actual->previo->siguiente = actual->siguiente;
    actual->siguiente->previo = actual->previo;
    free(actual);
    lista->longitud--;
    return dato;
}

/* Busca un valor y retorna su posición. Retorna -1 si no lo encuentra. */
int buscar(ListaDLC *lista, DATO dato) {
    if (lista->cabeza == NULL) return -1;

    nodo_cir *actual = lista->cabeza;
    int posicion = 0;
    
    /* Usamos do-while para dar la vuelta y detenernos al llegar de nuevo a la cabeza */
    do {
        if (actual->dato == dato) return posicion;
        actual = actual->siguiente;
        posicion++;
    } while (actual != lista->cabeza);
    
    return -1;
}

/* Obtiene el valor en una posición específica */
DATO obtener(ListaDLC *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud) return -1;

    nodo_cir *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++) {
        actual = actual->siguiente;
    }
    return actual->dato;
}

/* Verifica si la lista está vacía */
int esta_vacia(ListaDLC *lista) {
    return lista->cabeza == NULL;
}

/* Retorna el número de elementos en la lista */
int longitud(ListaDLC *lista) {
    return lista->longitud;
}

/* Imprime el contenido de la lista desde la cabeza hasta el final */
void imprimir_lista(ListaDLC *lista) {
    if (lista->cabeza == NULL) {
        printf("Lista vacia\n");
        return;
    }
    
    nodo_cir *actual = lista->cabeza;
    do {
        printf("[%d] <-> ", actual->dato);
        actual = actual->siguiente;
    } while (actual != lista->cabeza);
    printf("(Cabeza)\n"); /* Indica que vuelve a conectar */
}

/* Imprime la lista desde el final hacia atrás */
void imprimir_lista_reversa(ListaDLC *lista) {
    if (lista->cabeza == NULL) {
        printf("Lista vacia\n");
        return;
    }
    
    nodo_cir *actual = lista->cabeza->previo; 
    nodo_cir *ultimo = actual;
    
    do {
        printf("[%d] <-> ", actual->dato);
        actual = actual->previo;
    } while (actual != ultimo);
    printf("(Ultimo)\n"); /* Indica que vuelve a conectar */
}

/* Libera la memoria de todos los nodos y de la estructura de control */
void liberar_lista(ListaDLC *lista) {
    if (lista->cabeza != NULL) {
        nodo_cir *actual = lista->cabeza;
        nodo_cir *siguiente;
        
        do {
            siguiente = actual->siguiente;
            free(actual);
            actual = siguiente;
        } while (actual != lista->cabeza);
    }
    free(lista);
}