/*
 * ==========================================================================
 *  EJERCICIO 1 — Simulación del juego "Snake"
 * ==========================================================================
 *
 *  La víbora se representa como una lista doblemente ligada donde:
 *    - La CABEZA de la lista es la cabeza de la víbora.
 *    - Cada nodo almacena la posición (fila * 100 + columna) de un segmento.
 *    - El último nodo es la cola de la víbora.
 *
 *  ¿Por qué lista doblemente ligada?
 *    • Crecer: al comer comida, se agrega un segmento al final (insertar_final).
 *    • Moverse: se agrega un nuevo segmento en la cabeza (insertar_inicio)
 *      y se elimina el último segmento (eliminar_final). Ambas operaciones
 *      requieren recorrer eficientemente la lista.
 *    • Colisión consigo misma: se necesita recorrer el cuerpo para verificar
 *      si la nueva posición de la cabeza coincide con algún segmento.
 *    • El puntero "previo" permite recorrer la víbora desde la cola cuando
 *      es necesario (por ejemplo, para imprimirla en reversa).
 *
 *  Las y los alumnos deben completar las funciones marcadas con TODO.
 *  Compile con:
 *      gcc -Wall -Wextra -o snake snake.c listadl.c
 *
 * ==========================================================================
 */

#include "listadl.h"
#include <string.h>

/* ---------- Configuración del tablero ---------- */
#define FILAS    15
#define COLUMNAS 30

/* Codificación de posición: fila * 100 + columna */
#define POS(f, c) ((f) * 100 + (c))
#define FILA(p)   ((p) / 100)
#define COL(p)    ((p) % 100)

/* Direcciones */
#define ARRIBA    0
#define ABAJO     1
#define IZQUIERDA 2
#define DERECHA   3

/* Caracteres para dibujar */
#define CH_CABEZA 'O'
#define CH_CUERPO 'o'
#define CH_COMIDA '*'
#define CH_VACIO  '.'

/* ================================================================
 *  Funciones proporcionadas (no modificar)
 * ================================================================ */

/*
 * Genera una posición aleatoria para la comida que no coincida
 * con ningún segmento de la víbora.
 */
DATO generar_comida(ListaDL *vibora) {
    DATO pos;
    do {
        int f = 1 + rand() % (FILAS - 2);
        int c = 1 + rand() % (COLUMNAS - 2);
        pos = POS(f, c);
    } while (buscar(vibora, pos) != -1);
    return pos;
}

/*
 * Dibuja el tablero en la terminal.
 */
void dibujar_tablero(ListaDL *vibora, DATO comida) {
    char tablero[FILAS][COLUMNAS + 1];

    /* Fondo vacío */
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            if (f == 0 || f == FILAS - 1 || c == 0 || c == COLUMNAS - 1)
                tablero[f][c] = '#';
            else
                tablero[f][c] = CH_VACIO;
        }
        tablero[f][COLUMNAS] = '\0';
    }

    /* Colocar comida */
    tablero[FILA(comida)][COL(comida)] = CH_COMIDA;

    /* Colocar cuerpo de la víbora */
    dllista *seg = vibora->cabeza;
    int primero = 1;
    while (seg != NULL) {
        int f = FILA(seg->dato);
        int c = COL(seg->dato);
        tablero[f][c] = primero ? CH_CABEZA : CH_CUERPO;
        primero = 0;
        seg = seg->siguiente;
    }

    /* Imprimir */
    printf("\n");
    for (int f = 0; f < FILAS; f++)
        printf("  %s\n", tablero[f]);
    printf("\n");
}

/*
 * Imprime el estado del juego.
 */
void mostrar_estado(int turno, int puntaje, int dir) {
    const char *nombres[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};
    printf("  Turno: %d | Puntaje: %d | Dirección: %s\n",
           turno, puntaje, nombres[dir]);
}

/* ================================================================
 *  Funciones por completar
 * ================================================================ */
DATO calcular_nueva_cabeza(DATO cabeza_actual, int direccion) {
    int f = FILA(cabeza_actual);
    int c = COL(cabeza_actual);

  switch (direccion) {
      case ARRIBA: 
          f--;
          break;
      case ABAJO:
          f++;
          break;
      case IZQUIERDA:
          c--;
          break;
      case DERECHA:
          c++;
          break;
    return POS(f, c);
}

/*
 *  TODO 2: colision_pared
 *
 *  Verifica si la posición dada está fuera de los límites del tablero
 *  (es decir, sobre el borde '#').
 *
 *  Retorna: 1 si hay colisión con la pared, 0 si no.
 */
int colision_pared(DATO posicion) {
    int f = FILA(posicion);
    int c = COL(posicion);

    /* -------- COMPLETAR --------
     * Retorna 1 si f o c están en el borde del tablero:
     *   f <= 0, f >= FILAS-1, c <= 0, c >= COLUMNAS-1
     * --------------------------- */

if (f <= 0 || f >= FILAS-1 || c <= 0 || c >= COLUMNAS-1) {
    return 1;
    }
    return 0; /* Sustituir por la condición correcta */
}

/*
 *  TODO 3: colision_cuerpo
 *
 *  Verifica si la nueva posición de la cabeza coincide con algún
 *  segmento del cuerpo de la víbora.
 *
 *  Pista: usa la función buscar() de listadl.
 *
 *  Retorna: 1 si hay colisión, 0 si no.
 */
int colision_cuerpo(ListaDL *vibora, DATO nueva_pos) {
    /* -------- COMPLETAR --------
     * Usa buscar(vibora, nueva_pos) para saber si la posición
     * ya está ocupada por un segmento.
     * --------------------------- */
if (buscar(vibora, nueva_pos)) {
    return 1;
    }

    return 0; /* Sustituir */
}

/*
 *  TODO 4: mover_vibora
 *
 *  Mueve la víbora en la dirección indicada.
 *
 *  Pasos:
 *    1. Calcula la nueva posición de la cabeza con calcular_nueva_cabeza().
 *    2. Inserta la nueva posición AL INICIO de la lista (la cabeza avanza).
 *    3. Si la nueva posición NO coincide con la comida:
 *       - Elimina el ÚLTIMO elemento de la lista (la cola se recoge).
 *       - comio = 0
 *    4. Si coincide con la comida:
 *       - NO elimina la cola (la víbora crece).
 *       - comio = 1
 *
 *  Retorna: 1 si comió, 0 si no.
 *
 *  Pista: usa insertar_inicio() y eliminar_final() de listadl.
 */
int mover_vibora(ListaDL *vibora, int direccion, DATO comida) {
    DATO nueva_pos = calcular_nueva_cabeza(vibora->cabeza->dato, direccion);

    /* -------- COMPLETAR --------
     * 1. Inserta nueva_pos al inicio de la lista.
     * 2. Si nueva_pos == comida, retorna 1 (comió).
     * 3. Si no, elimina el último elemento y retorna 0.
     * --------------------------- */
insertar_inicio(vibora,nueva_pos);
if (nueva_pos == comida) {
    return 1;
}
eliminar_final(vibora);
    return 0; /* Sustituir */
}

/* ================================================================
 *  Secuencia de movimientos predefinida (simulación automática)
 * ================================================================ */

int main(void) {
    srand(42);

    /* Crear la víbora con 3 segmentos en el centro del tablero */
    ListaDL *vibora = crear_lista();
    int f_ini = FILAS / 2;
    int c_ini = COLUMNAS / 2;
    insertar_final(vibora, POS(f_ini, c_ini));
    insertar_final(vibora, POS(f_ini, c_ini - 1));
    insertar_final(vibora, POS(f_ini, c_ini - 2));

    DATO comida = generar_comida(vibora);
    int puntaje = 0;

    /* Secuencia de movimientos predeterminada para la simulación */
    int movimientos[] = {
        DERECHA, DERECHA, DERECHA, DERECHA, DERECHA,
        ABAJO, ABAJO, ABAJO,
        IZQUIERDA, IZQUIERDA, IZQUIERDA, IZQUIERDA,
        ARRIBA, ARRIBA,
        DERECHA, DERECHA, DERECHA,
        ABAJO, ABAJO, ABAJO, ABAJO,
        IZQUIERDA, IZQUIERDA,
        ARRIBA, ARRIBA, ARRIBA,
        DERECHA, DERECHA, DERECHA, DERECHA
    };
    int total_movimientos = sizeof(movimientos) / sizeof(movimientos[0]);

    printf("╔══════════════════════════════════════╗\n");
    printf("║        SIMULACIÓN DE SNAKE           ║\n");
    printf("╚══════════════════════════════════════╝\n");

    dibujar_tablero(vibora, comida);
    mostrar_estado(0, puntaje, DERECHA);

    for (int i = 0; i < total_movimientos; i++) {
        int dir = movimientos[i];
        DATO nueva = calcular_nueva_cabeza(vibora->cabeza->dato, dir);

        /* Verificar colisiones */
        if (colision_pared(nueva)) {
            printf("  ¡GAME OVER! La víbora chocó con la pared.\n");
            break;
        }
        if (colision_cuerpo(vibora, nueva)) {
            printf("  ¡GAME OVER! La víbora se mordió a sí misma.\n");
            break;
        }

        int comio = mover_vibora(vibora, dir, comida);
        if (comio) {
            puntaje += 10;
            comida = generar_comida(vibora);
            printf("  ¡Ñam! +10 puntos\n");
        }

        dibujar_tablero(vibora, comida);
        mostrar_estado(i + 1, puntaje, dir);
        printf("  Longitud de la víbora: %d segmentos\n", longitud(vibora));
    }

    printf("\n  Puntaje final: %d\n", puntaje);
    printf("  Longitud final: %d segmentos\n", longitud(vibora));

    /* Demostrar recorrido inverso (utilidad del puntero previo) */
    printf("\n  Víbora (cabeza -> cola): ");
    imprimir_lista(vibora);
    printf("  Víbora (cola -> cabeza): ");
    imprimir_lista_reversa(vibora);

    liberar_lista(vibora);
    return 0;
}
