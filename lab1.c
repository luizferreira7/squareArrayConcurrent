#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define M 5
#define N 101


typedef struct {
    int *array;
    int start;
    int end;
} ThreadArgs;


// Metodo que preenche o vetor
void fillArray(int array[]) {
    for (int i = 0; i < N; i++) {
        array[i] = i;
    }
}

// Metodo que eleva os elementos de um vetor ao quadrado
void squareArray(int array[], int start, int end) {
    for (int i = start; i < end; i++) {
        array[i] *= i;
    }
}

// Metodo que imprime o vetor
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);

        if ( (i + 1) != size) {
            printf(", ");
        }
    }

    printf("\n");
}

// Metodo usado para passar os argumentos da Thread e invocar a função que eleva os elementos do vetor ao quadrado.
void *squareArrayThread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;

    squareArray(thread_args -> array, thread_args -> start, thread_args -> end);

    free(args);

    pthread_exit(NULL);
}


// Verifica se os elementos dos vetores são iguais
int arraysAreEqual(int array1[], int array2[]) {
    for (int i = 0; i < N; i++) {
        if (array1[i] != array2[i]) {
            return -1;
        }
    }
    return 0;
}

int main() {
    pthread_t tid_sistema[M];

    int *array = malloc(sizeof (int) * N);
    fillArray(array);

    // Calcula o numero de elementos que cada Thread vai processar
    int subArraySize = N/M;
    int remainder = N % M;

    printf("Vetor original: \n");
    printArray(array, N);

    for(int i = 0; i < M; i++) {
        printf("\n--Cria a thread %d\n", i);

        // Prepara os argumentos da Thread
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        args -> array = array;
        args -> start = i * subArraySize;
        args -> end = (i + 1) * subArraySize;

        // Garante que a ultima Thread executa os elementos que sobram da divisam de N/M caso não seja exata
        if ( (i + 1) == M) {
            args -> end += remainder;
        }

        if (pthread_create(&tid_sistema[i], NULL, squareArrayThread, args)) {
            printf("--ERRO: pthread_create()\n"); exit(-2);
        }
    }

    for (int i = 0; i < M; i++) {
        if (pthread_join(tid_sistema[i], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        }
    }

    printf("\n--Thread principal terminou\n");

    printf("\nVetor ao quadrado: \n");
    printArray(array, N);

    // Recria o vetor original para poder comparar o resultado
    int *auxArray = malloc(sizeof (int) * N);
    fillArray(auxArray);
    // Usa o metodo de forma sequencial para comparar com o resultado obtido de forma concorrente
    squareArray(auxArray, 0, N);

    if (arraysAreEqual(array, auxArray) == -1) {
        printf("\nVetores possuem elementos diferentes\n");
    }

    free(auxArray);
    free(array);

    return 0;
}