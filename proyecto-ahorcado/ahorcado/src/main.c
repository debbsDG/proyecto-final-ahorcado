#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include <stdbool.h>

#include "palabras.h"
#include "logica.h"
#include "interfaz.h"

#define MAX_NAME 64
#define MAX_PAL 128

int main(void) {
    srand((unsigned int)time(NULL));

    WordList wl = {0};
    if (cargar_palabras("assets/palabras.txt", &wl) != 0) {
        fprintf(stderr, "Error: no se pudo abrir assets/palabras.txt\n");
        return 1;
    }

    iniciar_ncurses();

    presentar_inicio();

    char nombre[MAX_NAME] = "jugador";
    pedir_nombre(nombre, MAX_NAME);

    bool salir = false;
    int puntos = 0;
    int max_fallos = 6;
    int nivel = 1;

    while (!salir) {
        presentar_menu_principal();
        int opcion = getch();
        switch (opcion) {
            case '1': {
                bool jugar = true;
                while (jugar) {
                    char palabra[MAX_PAL];
                    if (seleccionar_palabra(&wl, nivel, palabra, sizeof(palabra)) != 0) {
                        mostrar_mensaje("No se pudo seleccionar palabra.");
                        break;
                    }

                    EstadoJuego estado;
                    inicializar_juego(&estado, palabra, max_fallos);

                    while (!es_ganador(&estado) && !es_perdedor(&estado)) {
                        mostrar_tablero(&estado, nivel, nombre, puntos);
                        mostrar_mensaje("Introduce una letra:");
                        char letra = leer_letra();

                        int idx = (letra >= 'a' && letra <= 'z') ? letra - 'a' : -1;
                        if (idx >= 0 && estado.usadas[idx]) {
                            mostrar_mensaje("Letra ya usada. Prueba otra.");
                            napms(600);
                            continue;
                        }

                        if (verificar_letra(&estado, letra)) {
                            mostrar_mensaje("CORRECTO!");
                        } else {
                            mostrar_mensaje("INCORRECTO!");
                        }
                        napms(400);
                    }

                    if (es_ganador(&estado)) {
                        puntos += (nivel == 1 ? 20 : nivel == 2 ? 30 : 50);
                        mostrar_tablero(&estado, nivel, nombre, puntos);
                        mostrar_mensaje("¡Victoria! Presiona 'r' para jugar otra, 'q' para salir.");
                    } else {
                        mostrar_tablero(&estado, nivel, nombre, puntos);
                        char derrota_msg[128];
                        snprintf(derrota_msg, sizeof(derrota_msg), "DERROTA. La palabra era: %s", estado.secreto);
                        mostrar_mensaje(derrota_msg);
                        mvprintw(22, 2, "Presiona 'r' para jugar otra, 'q' para salir.");
                    }

                    int ch;
                    while (true) {
                        ch = getch();
                        if (ch == 'r' || ch == 'R') {
                            break;
                        } else if (ch == 'q' || ch == 'Q') {
                            jugar = false;
                            break;
                        }
                    }
                }
                break;
            }

            case '2': {
                nivel = presentar_menu_opciones();
                break;
            }

            case '3':
                salir = true;
                break;
        }
    }

    presentar_final();
    terminar_ncurses();
    liberar_palabras(&wl);

    printf("Has salido. Puntos finales: %d\n", puntos);
    return 0;
}
