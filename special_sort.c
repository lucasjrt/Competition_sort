#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLS_SIZE 250
#define ROWS_SIZE 100000

char **caux;
int *cint;

void stringMerge(char **v, int inicio, int fim) {
    int v1 = inicio, meio = inicio + ((fim - inicio) >> 1), v2 = meio + 1, tamanho = fim - inicio + 1, flag1 = 0, flag2 = 0;
    int i, j;
    for(i = 0; i < tamanho; i++) {
        if(!flag1 && !flag2) {
            if(strcmp(v[v1], v[v2]) < 0) 
                strcpy(aux[i], v[v1++]);
            else
                strcpy(aux[i], v[v2++]);
        } else {
            if(!flag1)
                strcpy(aux[i], v[v1++]);
            else 
                strcpy(aux[i], v[v2++]);
        }
        if(v1 > meio) flag1 = 1;
        if(v2 > fim)  flag2 = 1;
    }
    for(i = 0, j = inicio; j < fim + 1; i++, j++) {
        strcpy(v[j], aux[i]);
    }
}

void _mergeString(char **v, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + ((fim - inicio) >> 1);
        _mergeString(v, inicio, meio);
        _mergeString(v, meio + 1, fim);
        stringMerge(v, inicio, fim);
    }

}

inline void mergeString(char **v, int n) {
    _mergeString(v, 0, n-1);
}

void lenMerge(char **v, int inicio, int fim) {
    int v1 = inicio, meio = inicio + ((fim - inicio) >> 1), v2 = meio + 1, tamanho = fim - inicio + 1, flag1 = 0, flag2 = 0;
    int i, j;
    for(i = 0; i < tamanho; i++) {
        if(!flag1 && !flag2) {
            if(strlen(v[v1]) < strlen(v[v2]))
                strcpy(aux[i], v[v1++]);
            else
                strcpy(aux[i], v[v2++]);
        } else {
            if(!flag1)
                strcpy(aux[i], v[v1++]);
            else 
                strcpy(aux[i], v[v2++]);
        }
        if(v1 > meio) flag1 = 1;
        if(v2 > fim)  flag2 = 1;
    }
    for(i = 0, j = inicio; j < fim + 1; i++, j++) {
        strcpy(v[j], aux[i]);
    }
}

void _lenMerge(char **v, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + ((fim - inicio) >> 1);
        _lenMerge(v, inicio, meio);
        _lenMerge(v, meio + 1, fim);
        lenMerge(v, inicio, fim);
    }
}

inline void lenMerge(char **v, int n) {
    _lenMerge(v, 0, n);
}

inline int ehBin(char *v) {
    int i;

    for(i = 0; i < strlen(v); i++)
        if(v[i] != '1' && v[i] != '0')
            return 0;
    return 1;
}

int main() {
    int i, n = 0;
    int *iinput;
    char **cinput = (char**) malloc(ROWS_SIZE * sizeof(char*));
    cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
    i = scanf("%s", cinput[n]);
    if(i != EOF) { //TODO: Alterar esse if para dentro dos whiles
        if(cinput[n] < '0' || cinput[n] > '9') {
            caux = (char**) malloc(ROWS_SIZE * sizeof(char*));
            caux[n++] = (char*) malloc(COLS_SIZE * sizeof(char));
            cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            while(scanf("%s", cinput[n]) != EOF) {
                cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
                aux[n] = (char*) malloc(COLS_SIZE * sizeof(char));
                n++;
            }
            mergeString(cinput, n);
        } else if(ehBin(caux[n])) {
            caux = (char**) malloc(ROWS_SIZE * sizeof(char*));
            caux[n++] = (char*) malloc(COLS_SIZE * sizeof(char));
            cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            while(scanf("%s", cinput[n]) != EOF) {
                cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
                aux[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            }
            mergeBin(cinput, n);
        } else {
            iinput = (int*) malloc(ROWS_SIZE * sizeof(int));
            iinput[n] = atoi(cinput[n]);
            iaux = (int*) malloc(ROWS_SIZE * sizeof(int));
            n++;
            while(scanf("%s", cinput[n]) != EOF) {
                n++;
                iinput[n] = atoi(cinput[n]);
            }
        }
    }
    for(i = 0; i <= n; i++) {
       printf("%s\n", cinput[i]); 
    }
    free(aux);
    free(cinput);
    return 0;
}
