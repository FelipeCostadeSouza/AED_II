#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define T 100000


void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify_iterativo(int v[], int n, int i) {
    int p = i;
    while (1) {
        int maior = p;
        int esq = 2 * p + 1;
        int dir = 2 * p + 2;

        if (esq < n && v[esq] > v[maior])
            maior = esq;
        if (dir < n && v[dir] > v[maior])
            maior = dir;

        if (maior != p) {
            trocar(&v[p], &v[maior]);
            p = maior;
        } else {
            return;
        }
    }
}

void heapSortIterativo(int v[], int n) {
   
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_iterativo(v, n, i);
    }
   
    for (int i = n - 1; i > 0; i--) {
        trocar(&v[0], &v[i]);
        heapify_iterativo(v, i, 0);
    }
}


void quickSortRecursivo(int v[], int inicio, int fim) {
    if (inicio < fim) {
    
        int pivo = v[(inicio + fim) / 2];
        int i = inicio;
        int j = fim;

        while (i <= j) {
            while (v[i] < pivo) i++;
            while (v[j] > pivo) j--;
            if (i <= j) {
                trocar(&v[i], &v[j]);
                i++;
                j--;
            }
        }

        quickSortRecursivo(v, inicio, j);
        quickSortRecursivo(v, i, fim);
    }
}


void quickSortIterativo(int v[], int inicio, int fim) {
    
    int *pilha = (int *)malloc((fim - inicio + 1) * sizeof(int));
    if (pilha == NULL) return;

    int topo = -1;

  
    pilha[++topo] = inicio;
    pilha[++topo] = fim;

   
    while (topo >= 0) {
        int dir = pilha[topo--];
        int esq = pilha[topo--];

        if (esq < dir) {
           
            int pivo = v[(esq + dir) / 2];
            int i = esq;
            int j = dir;

            while (i <= j) {
                while (v[i] < pivo) i++;
                while (v[j] > pivo) j--;
                if (i <= j) {
                    trocar(&v[i], &v[j]);
                    i++;
                    j--;
                }
            }

         
            if (esq < j) {
                pilha[++topo] = esq;
                pilha[++topo] = j;
            }

            
            if (i < dir) {
                pilha[++topo] = i;
                pilha[++topo] = dir;
            }
        }
    }

    free(pilha);
}

int main() {
    srand(time(NULL));
    
    int *vetor = (int *)malloc(T * sizeof(int));

    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    for (int i = 0; i < T; i++) {
        vetor[i] = T - i;
    }

    int *v  = (int *)malloc(T * sizeof(int)); 
    int *v2 = (int *)malloc(T * sizeof(int)); 
    int *v3 = (int *)malloc(T * sizeof(int)); 

    if (v == NULL || v2 == NULL || v3 == NULL) {
        printf("Erro ao alocar memória para as cópias.\n");
        free(vetor); free(v); free(v2); free(v3);
        return 1;
    }

    for (int i = 0; i < T; i++) {
        vetor[i] = rand(); 
    }

    
    clock_t inicio = clock();
    for (int gap = 1000; gap > 0; gap /= 2) {
        for (int i = gap; i < T; i++) {
            int temp = vetor[i];
            int j = i;

            while (j >= gap && vetor[j - gap] > temp) {
                vetor[j] = vetor[j - gap];
                j -= gap;
            }
            vetor[j] = temp;
        }
    }
    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de processamento (Shellsort iterativo):  %.6f s (%.3f ms)\n", tempo_execucao);

    
    inicio = clock();
    heapSortIterativo(v, T);
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de processamento (HeapSort Iterativo):  %.6f s (%.3f ms)\n", tempo_execucao);

    
    inicio = clock();
    quickSortRecursivo(v2, 0, T - 1);
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de processamento (QuickSort Recursivo): %.6f s (%.3f ms)\n", tempo_execucao);

    
    inicio = clock();
    quickSortIterativo(v3, 0, T - 1);
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de processamento (QuickSort Iterativo): %.6f s (%.3f ms)\n", tempo_execucao);

    
    free(vetor);
    free(v);
    free(v2);
    free(v3);

    return 0;
}
