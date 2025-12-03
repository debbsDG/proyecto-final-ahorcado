#include "interfaz.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void iniciar_ncurses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    if(has_colors()){
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
    }
    refresh();
}

void terminar_ncurses(){
    endwin();
}

void dibujar_horca(int fallos, int max_fallos){
    int base_row = 2, base_col = 2;
    for(int r=base_row; r<base_row+12; r++)
        mvhline(r, base_col, ' ', 30);
    mvprintw(base_row+0, base_col+10, " _______");
    mvprintw(base_row+1, base_col+10, "|/      |");
    if(fallos >= 1) mvprintw(base_row+2, base_col+10, "|       O"); else mvprintw(base_row+2, base_col+10, "|");
    if(fallos == 2) mvprintw(base_row+3, base_col+10, "|       |");
    else if(fallos == 3) mvprintw(base_row+3, base_col+10, "|      /|");
    else if(fallos >= 4) mvprintw(base_row+3, base_col+10, "|      /|\\");
    else mvprintw(base_row+3, base_col+10, "|");
    if(fallos == 5) mvprintw(base_row+4, base_col+10, "|      /");
    else if(fallos >= 6) mvprintw(base_row+4, base_col+10, "|      / \\");
    else mvprintw(base_row+4, base_col+10, "|");
    mvprintw(base_row+6, base_col+10, "|");
    mvprintw(base_row+7, base_col+10, "|____");
}

void mostrar_tablero(const EstadoJuego *e, int dificultad, const char *jugador, int puntos){
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(0, 30, "JUEGO DEL AHORCADO (C + ncurses)");
    attroff(COLOR_PAIR(4));
    mvprintw(1, 2, "Jugador: %s    Dificultad: %d    Puntos: %d", jugador ? jugador : "Anon", dificultad, puntos);
    dibujar_horca(e->fallos, e->max_fallos);
    int row = 10, col = 40;
    mvprintw(row-1, col, "Palabra:");
    mvprintw(row, col, "");
    for(int i=0;i<e->longitud;i++)
        printw("%c ", e->oculto[i]);
    mvprintw(row+3, col, "Letras usadas: ");
    int pos = 0;
    for(int i=0;i<26;i++){
        if(e->usadas[i]){
            mvprintw(row+4 + pos/13, col + (pos%13)*2, "%c ", 'a'+i);
            pos++;
        }
    }
    refresh();
}

void mostrar_mensaje(const char *msg){
    attron(COLOR_PAIR(3));
    mvprintw(20, 2, " %s", msg);
    attroff(COLOR_PAIR(3));
    refresh();
}

char leer_letra(){
    int ch;
    while(true){
        ch = getch();
        if(ch == ERR) continue;
        if(isalpha(ch)){
            char c = (char)ch;
            if(isupper((unsigned char)c)) c = (char)tolower((unsigned char)c);
            return c;
        }
    }
}

int menu_seleccionar_nivel(){
    echo();
    curs_set(1);
    int nivel = 1;
    mvprintw(15, 2, "Selecciona dificultad: 1=Facil(3-5)  2=Medio(6-8)  3=Dificil(9+): ");
    refresh();
    int ch;
    while(true){
        ch = getch();
        if(ch == '1' || ch == '2' || ch == '3'){
            nivel = ch - '0';
            break;
        }
    }
    noecho();
    curs_set(0);
    return nivel;
}

void pedir_nombre(char *buf, int buflen){
    echo();
    curs_set(1);
    mvprintw(17, 2, "Introduce tu nombre: ");
    refresh();
    mvgetnstr(17, 22, buf, buflen-1);
    noecho();
    curs_set(0);
}

void presentar_inicio() {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    char *titulo[] = {
        "***  ***   ***  ***  ********  ***  ***********",
        "***  ****  ***  ***  ********  ***  ***********",
        "***  ***** ***  ***  ***       ***  ***     ***",
        "***  *********  ***  ***       ***  ***     ***",
        "***  *********  ***  **        ***  ***     ***",
        "***  *** *****  ***  ***       ***  ***     ***",
        "***  ***  ****  ***  ***       ***  ***     ***",
        "***  ***   ***  ***  ***       ***  ***     ***",
        "***  ***    **  ***  ********  ***  ***********",
        "***  ***     *  ***  ********  ***  ***********",
        NULL
    };
    int y_start = row/2 - 5;
    for (int i = 0; titulo[i] != NULL; i++) {
        mvprintw(y_start + i, (col - strlen(titulo[i]))/2, "%s", titulo[i]);
        refresh();
        napms(100);
    }
    mvprintw(row - 2, (col - 28)/2, "Presiona cualquier tecla para continuar");
    refresh();
    getch();
}

void presentar_final() {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    char *final[] = {
        "*********  ***  ***   ***         *****         ***",
        "*********  ***  ****  ***        *******        ***",
        "***        ***  ***** ***       ***   ***       ***",
        "*********  ***  *********      ***     ***      ***",
        "*********  ***  *********     *************     ***",
        "***        ***  *** *****    ***************    ***",
        "***        ***  ***  ****   ****         ****   ********",
        "***        ***  ***   ***  ****          *****  ********",
        NULL
    };
    int y_start = row/2 - 5;
    for (int i = 0; final[i] != NULL; i++)
        mvprintw(y_start + i, (col - strlen(final[i]))/2, "%s", final[i]);
    mvprintw(row - 2, (col - 28)/2, "Presiona cualquier tecla para salir");
    refresh();
    getch();
}

void presentar_menu_principal() {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    char *menu[] = {
        "*****         ****  ****  ********  *******      ********         *****",
        "*******        ****  ****  ********  ********     ********        *******",
        "***   ***       ****  ****  ***  ***  ***  ***     ****           ***   ***",
        "***     ***      **********  ***  ***  *******      ****          ***     ***",
        "*************     **********  ***  ***  ********     ****         *************",
        "***************    ****  ****  ***  ***  ***   ***    ****        ***************",
        "****         ****   ****  ****  ********  ***    ***   ********   ****         ****",
        "****          *****  ****  ****  ********  ***     ***  ********  ****          *****",
        NULL
    };
    int y_start = row/2 - 7;
    for (int i = 0; menu[i] != NULL; i++)
        mvprintw(y_start + i, (col - strlen(menu[i]))/2, "%s", menu[i]);
    mvprintw(y_start + 10, (col - 30)/2, "1) Jugar");
    mvprintw(y_start + 11, (col - 30)/2, "2) Opciones");
    mvprintw(y_start + 12, (col - 30)/2, "3) Salir");
    refresh();
}

int presentar_menu_opciones() {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row/2 - 2, (col - 20)/2, "MENU DE OPCIONES");
    mvprintw(row/2,     (col - 20)/2, "1) Dificultad Fácil");
    mvprintw(row/2 + 1, (col - 20)/2, "2) Dificultad Media");
    mvprintw(row/2 + 2, (col - 20)/2, "3) Dificultad Difícil");
    mvprintw(row/2 + 4, (col - 20)/2, "Elige una opción: ");
    refresh();
    int ch = getch();
    switch(ch) {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        default:  return 1;
    }
}
