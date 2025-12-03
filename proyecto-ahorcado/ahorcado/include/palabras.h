#ifndef PALABRAS_H
#define PALABRAS_H

#include <stddef.h>

typedef struct {
    char **list;     
    size_t count;    
} WordList;

int cargar_palabras(const char *filename, WordList *wl);

int seleccionar_palabra(const WordList *wl, int nivel, char *buf, size_t buflen);

void liberar_palabras(WordList *wl);

#endif 
