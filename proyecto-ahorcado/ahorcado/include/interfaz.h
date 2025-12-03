#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <ncurses.h>
#include "logica.h"

void iniciar_ncurses();
void terminar_ncurses();
void dibujar_horca(int fallos, int max_fallos);
void mostrar_tablero(const EstadoJuego *e, int dificultad, const char *jugador, int puntos);
void mostrar_mensaje(const char *msg);
char leer_letra();
int menu_seleccionar_nivel();
void pedir_nombre(char *buf, int buflen);
void presentar_inicio();
void presentar_final();
void presentar_menu_principal();
int presentar_menu_opciones();


#endif 
