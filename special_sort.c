#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLS_SIZE 250
#define ROWS_SIZE 100000
#define MAX_INT 2147483647

char **caux;
int *bInt;
int *cInt;

int binCompare(const char *s1, const char *s2){
    int size_s1 = strlen(s1), size_s2 = strlen(s2);
    int diferenca = size_s1 - size_s2;
    if(diferenca<=0){ //s2 maior
        for(int i=0; i<(-diferenca);i++){
            if(s2[i]>'0')
                return -1;
        }
        for(int i = (-diferenca), j=0; i<size_s2; i++,j++){
            if(s1[j]<s2[i])
                return -1;
            else{
                if(s1[j]>s2[i])
                    return 1;
            }
        }
        return 0;
    }
    if(diferenca>=0){ //s1 maior
        for(int i=0; i<diferenca; i++){
            if(s1[i]>'0')
                return 1;
        }

        for(int i = diferenca, j=0; i<size_s1; i++,j++){
            if(s1[i]>s2[j])
                return 1;
            else{
                if(s1[i]<s2[j])
                    return -1;
            }
        }
        return 0;
    }

}

void mergeInt(int *v, unsigned int inicio, unsigned int fim){
    if(inicio>=fim)
        return;
    unsigned int meio = inicio + (fim-inicio)/2;
    mergeInt(v, inicio, meio);
    mergeInt(v, meio+1, fim);
    unsigned int k;

    for(k=inicio; k<=meio; k++)
        bInt[k-inicio] = v[k];
    for(k=meio+1; k<=fim; k++)
        cInt[k-meio-1] = v[k];
    bInt[meio-inicio+1] = MAX_INT;
    cInt[fim-(meio+1)+1] = MAX_INT;

    int i=0, j=0;
    for(k=inicio; k<=fim; k++){
        if(bInt[i]<cInt[j])
            v[k] = bInt[i++];
        else
            v[k] = cInt[j++];
    }
}

void binMerge(char **v, int inicio, int fim) {
    int v1 = inicio, meio = inicio + ((fim - inicio) >> 1), v2 = meio + 1, tamanho = fim - inicio + 1, flag1 = 0, flag2 = 0;
    int i, j;
    for(i = 0; i < tamanho; i++) {
        if(!flag1 && !flag2) {
            if(binCompare(v[v1], v[v2]) < 0)
                strcpy(caux[i], v[v1++]);
            else
                strcpy(caux[i], v[v2++]);
        } else {
            if(!flag1)
                strcpy(caux[i], v[v1++]);
            else
                strcpy(caux[i], v[v2++]);
        }
        if(v1 > meio) flag1 = 1;
        if(v2 > fim)  flag2 = 1;
    }
    for(i = 0, j = inicio; j < fim + 1; i++, j++) {
        strcpy(v[j], caux[i]);
    }
}

void stringMerge(char **v, int inicio, int fim) {
    int v1 = inicio, meio = inicio + ((fim - inicio) >> 1), v2 = meio + 1, tamanho = fim - inicio + 1, flag1 = 0, flag2 = 0;
    int i, j;
    for(i = 0; i < tamanho; i++) {
        if(!flag1 && !flag2) {
            if(strcmp(v[v1], v[v2]) < 0)
                strcpy(caux[i], v[v1++]);
            else
                strcpy(caux[i], v[v2++]);
        } else {
            if(!flag1)
                strcpy(caux[i], v[v1++]);
            else
                strcpy(caux[i], v[v2++]);
        }
        if(v1 > meio) flag1 = 1;
        if(v2 > fim)  flag2 = 1;
    }
    for(i = 0, j = inicio; j < fim + 1; i++, j++) {
        strcpy(v[j], caux[i]);
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

void mergeString(char **v, int n) {
    _mergeString(v, 0, n-1);
}

void mergeLen(char **v, int inicio, int fim) {
    int v1 = inicio, meio = inicio + ((fim - inicio) >> 1), v2 = meio + 1, tamanho = fim - inicio + 1, flag1 = 0, flag2 = 0;
    int i, j;
    for(i = 0; i < tamanho; i++) {
        if(!flag1 && !flag2) {
            if(strlen(v[v1]) < strlen(v[v2]))
                strcpy(caux[i], v[v1++]);
            else
                strcpy(caux[i], v[v2++]);
        } else {
            if(!flag1)
                strcpy(caux[i], v[v1++]);
            else
                strcpy(caux[i], v[v2++]);
        }
        if(v1 > meio) flag1 = 1;
        if(v2 > fim)  flag2 = 1;
    }
    for(i = 0, j = inicio; j < fim + 1; i++, j++) {
        strcpy(v[j], caux[i]);
    }
}

void _lenMerge(char **v, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + ((fim - inicio) >> 1);
        _lenMerge(v, inicio, meio);
        _lenMerge(v, meio + 1, fim);
        mergeLen(v, inicio, fim);
    }
}

void lenMerge(char **v, int n) {
    _lenMerge(v, 0, n - 1);
}

int ehBin(char *v) {
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
    if(scanf("%s", cinput[n]) != EOF) { //TODO: Alterar esse if para dentro dos whiles
        if(cinput[n][0] < '0' || cinput[n][0] > '9') {
			printf("String reconhecido\n");
            caux = (char**) malloc(ROWS_SIZE * sizeof(char*));
            caux[n++] = (char*) malloc(COLS_SIZE * sizeof(char));
            cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            while(scanf("%s", cinput[n]) != EOF) {
                n++;
                cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
                caux[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            }
            printf("Recebeu:\n");
            for(int i=0;i<n;i++)
                printf("%s\n",cinput[i]);
            printf("fim\n");
            mergeString(cinput, n);
            printf("Ordenou para:\n\n");
            for(int i=0;i<n;i++)
                printf("%s\n",cinput[i]);
            printf("fim\n");
        } else if(ehBin(caux[n])) {
			printf("Binario reconhecido\n");
            caux = (char**) malloc(ROWS_SIZE * sizeof(char*));
            caux[n++] = (char*) malloc(COLS_SIZE * sizeof(char));
            cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            while(scanf("%s", cinput[n]) != EOF) {
                cinput[n] = (char*) malloc(COLS_SIZE * sizeof(char));
                caux[n] = (char*) malloc(COLS_SIZE * sizeof(char));
            }
            binMerge(cinput,0, n-1);
        } else {
			printf("Inteiro reconhecido\n");
            iinput = (int*) malloc(ROWS_SIZE * sizeof(int));
            iinput[n] = atoi(cinput[n]);
            bInt = (int*) malloc((ROWS_SIZE>>2)+1 * sizeof(int));
            cInt = (int*) malloc(ROWS_SIZE>>2 * sizeof(int));
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
    if(caux != NULL)
    	free(caux);
	else{
		free(bInt);
		free(cInt);
	}
    free(cinput);
    return 0;
}
