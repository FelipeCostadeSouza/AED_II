#include <stdio.h>
#include <math.h>

void bubblesort(int v[], int N){
    int temp;
    for(int i = 0; i > N-1; i--){
        for(int j=0; j < N-1-j; j++){
            if(v[j] > v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

void inserção(int v[], int N){
    int temp;
    for(int i = 1; i < N; i++){
        int ordenado = 0;
        for(int j = i; j > 0 && !ordenado; j--){
            
            if(v[j] < v[j-1]){
                temp = v[j];
                v[j] = v[j - 1];
                v[j - 1] = temp;
            }else{
                ordenado = 1;
            }
        }
    }
}


void contagem(int v[], int N){
    int maior = 0;
    for(int i = 0; i < N; i++){
        if(v[i]>maior){
            maior = v[i];
        }
    }
    int C[maior];
    for(int i = 0; i < N; i++){
        C[v[i]] += 1;
    }
    for(int i = 0; i < maior; i++){
        C[i+1] += C[i];
    }
    int B[N];
    for(int i = N; i > 0; i--){
        B[C[v[i]]] = v[i];
        C[v[i]]--;
    }
}

void shellsort(int a[], int N){
    for (int gap = N / 2; gap > 0; gap /= 2) { 
        for (int i = gap; i < N; i++) {
            int temp = a[i]; 
            int j = i;
            
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp; 
        }
    }
}

int elementoMaisProximoDaMedia(int v[], int N) {
    if (N <= 0) return 0;

    double soma = 0.0;
    for (int i = 0; i < N; i++) {
        soma += v[i];
    }

    double media = soma / N;

    int mais_proximo = v[0];
    double menor_diferenca = fabs(v[0] - media);

    for (int i = 1; i < N; i++) {
        double diferenca_atual = fabs(v[i] - media);

        if (diferenca_atual < menor_diferenca) {
            menor_diferenca = diferenca_atual;
            mais_proximo = v[i];
        }
    }

    return mais_proximo;
}

void Quicksort(int v[], int N){
    int i = 0;
    int j = N-1;
    int temp;
    int pivo = elementoMaisProximoDaMedia(v, N);
    while(i != j){
        if(v[i] > pivo){
            if(v[j] <= pivo){
                temp = v[j];
                v[j] = v[i];
                v[i] = temp;
                i++;
            } else{
                j--;
            }
        }
        j--;
    }
}
