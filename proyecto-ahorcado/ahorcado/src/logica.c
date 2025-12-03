#include "logica.h"
#include <string.h>
#include <ctype.h>

void inicializar_juego(EstadoJuego *e, const char *palabra, int max_fallos){
    if(!e || !palabra) return;
    memset(e, 0, sizeof(EstadoJuego));
    strncpy(e->secreto, palabra, sizeof(e->secreto)-1);
    e->longitud = (int)strlen(e->secreto);
    for(int i=0;i<e->longitud;i++){
        if(e->secreto[i] >= 'a' && e->secreto[i] <= 'z')
            e->oculto[i] = '_';
        else
            e->oculto[i] = e->secreto[i]; 
    }
    e->oculto[e->longitud] = '\0';
    e->max_fallos = max_fallos;
    e->fallos = 0;
    for(int i=0;i<26;i++) e->usadas[i] = false;
}

static int idx_letra(char c){
    if(c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
    if(c >= 'a' && c <= 'z') return c - 'a';
    return -1;
}

bool verificar_letra(EstadoJuego *e, char letra){
    if(!e) return false;
    if(isupper((unsigned char)letra)) letra = (char)tolower((unsigned char)letra);
    int idx = idx_letra(letra);
    if(idx < 0) return false;
    if(e->usadas[idx]) return false; // letra ya usada
    e->usadas[idx] = true;
    bool encontrado = false;
    for(int i=0;i<e->longitud;i++){
        if(e->secreto[i] == letra){
            e->oculto[i] = letra;
            encontrado = true;
        }
    }
    if(!encontrado) e->fallos++;
    return encontrado;
}


bool es_ganador(const EstadoJuego *e){
    return (strncmp(e->secreto, e->oculto, e->longitud) == 0);
}

bool es_perdedor(const EstadoJuego *e){
    return (e->fallos >= e->max_fallos);
}

void reiniciar_estado(EstadoJuego *e){
    if(!e) return;
    memset(e, 0, sizeof(EstadoJuego));
}
