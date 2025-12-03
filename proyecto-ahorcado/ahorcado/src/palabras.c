#include "palabras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *trim(char *s){
    char *end;
    while(*s && isspace((unsigned char)*s)) s++;
    if(*s == 0) return s;
    end = s + strlen(s) - 1;
    while(end > s && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return s;
}

int cargar_palabras(const char *filename, WordList *wl){
    if(!filename || !wl) return -1;
    FILE *f = fopen(filename, "r");
    if(!f) return -1;
    wl->list = NULL;
    wl->count = 0;
    char line[256];
    while(fgets(line, sizeof(line), f)){
        char *t = trim(line);
        if(strlen(t) == 0) continue;
        char tmp[256];
        size_t pos = 0;
        for(size_t i=0; t[i] && pos+1 < sizeof(tmp); ++i){
            if(!isspace((unsigned char)t[i])){
                tmp[pos++] = (char)tolower((unsigned char)t[i]);
            }
        }
        tmp[pos] = '\0';
        if(pos==0) continue;
        // guardar
        char *copy = malloc(pos+1);
        if(!copy) { fclose(f); return -1; }
        strcpy(copy, tmp);
        char **newlist = realloc(wl->list, sizeof(char*) * (wl->count + 1));
        if(!newlist) { free(copy); fclose(f); return -1; }
        wl->list = newlist;
        wl->list[wl->count++] = copy;
    }
    fclose(f);
    return 0;
}

void liberar_palabras(WordList *wl){
    if(!wl) return;
    for(size_t i=0;i<wl->count;i++) free(wl->list[i]);
    free(wl->list);
    wl->list = NULL;
    wl->count = 0;
}

int seleccionar_palabra(const WordList *wl, int nivel, char *buf, size_t buflen){
    if(!wl || wl->count == 0 || !buf) return -1;
    int tries = 0;
    while(tries < 1000){
        size_t idx = rand() % wl->count;
        const char *cand = wl->list[idx];
        size_t len = strlen(cand);
        int ok = 0;
        if(nivel == 1){
            ok = (len >= 3 && len <= 5);
        } else if(nivel == 2){
            ok = (len >= 6 && len <= 8);
        } else {
            ok = (len >= 9);
        }
        if(ok){
            strncpy(buf, cand, buflen-1);
            buf[buflen-1] = '\0';
            return 0;
        }
        tries++;
    }
    strncpy(buf, wl->list[rand() % wl->count], buflen-1);
    buf[buflen-1] = '\0';
    return 0;
}
