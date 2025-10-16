#include <stdio.h>
#include <stdlib.h>


int main() 
{
const int tamanho = 5;
int *numeros = (int*)malloc(tamanho * sizeof(int));
if (numeros == NULL) {
    printf("erro de alocaçao de memoria");
    return 1;
}

numeros[0] = 10;
numeros[1] = 20;
numeros[2] = 30;
numeros[3] = 40;
numeros[4] = 50;

for(int i = 0; i < 5; i++) {
    printf("numero[%d] = %d\n", i, numeros[i]);
}
/*apos realloc vem os parametros que ee o bloco que desejo mudar no caso numero 
e a quantidade vezes sizeof(e o tipo de dado que vai usar int, float, etc)*/
int* num2 = (int*) realloc(numeros, 7 * sizeof(int));
if (num2 != NULL) {
    numeros = num2;
} else {
    printf("nao foi possivel continuar com a alocacao de memoria");
}

numeros[5] = 60;
numeros[6] = 70;

printf("numeros com o array aumentado apos o realloc\n\n");
for (int y = 0; y < 7; y++) {
    printf("numeros[%d] = %d\n", y, numeros[y]);
}

free(numeros);

    return 0;
}