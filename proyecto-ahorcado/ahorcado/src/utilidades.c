#include "utilidades.h"

char sanitizar_letra(int ch){
    if(ch == 0) return 0;
    if(isalpha(ch)){
        char c = (char)ch;
        if(c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
        return c;
    }
    return 0;
}
