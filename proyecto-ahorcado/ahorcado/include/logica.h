#ifndef LOGICA_H
#define LOGICA_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_WORD_LEN 128

typedef struct {
    char secreto[MAX_WORD_LEN];   
    char oculto[MAX_WORD_LEN];    
    bool usadas[26];              
    int longitud;
    int fallos;
    int max_fallos;
} EstadoJuego;

void inicializar_juego(EstadoJuego *e, const char *palabra, int max_fallos);
bool verificar_letra(EstadoJuego *e, char letra); 
bool es_ganador(const EstadoJuego *e);
bool es_perdedor(const EstadoJuego *e);
void reiniciar_estado(EstadoJuego *e);

#endif 
