#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define T 1000

typedef struct{
    int dia;
    int mes;
    int ano;
}data;

void shellsortdia(data a[]){
    for (int gap = T / 4; gap > 0; gap /= 2) { 
        for (int i = gap; i < T; i++) {
            data temp = a[i]; 
            int j = i;
            
            while (j >= gap && a[j - gap].dia > temp.dia) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp; 
        }
    }
}
void shellsortmes(data a[]){
    for (int gap = T / 4; gap > 0; gap /= 2) { 
        for (int i = gap; i < T; i++) {
            data temp = a[i]; 
            int j = i;
            
            while (j >= gap && a[j - gap].mes > temp.mes) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp; 
        }
    }
}
void shellsortano(data a[]){
    for (int gap = T / 4; gap > 0; gap /= 2) { 
        for (int i = gap; i < T; i++) {
            data temp = a[i]; 
            int j = i;
            
            while (j >= gap && a[j - gap].ano > temp.ano) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp; 
        }
    }
}
void contagemdia(data a[]){
    int maior=0;
    for(int i=0; i<T; i++){
        if(a[i].dia > maior){
            maior = a[i].dia;
        }
    }
    
    int c[maior+1];
    
    for(int i = 0; i <= maior; i++){
        c[i] = 0;
    }
    
    for(int i=0; i<T; i++){
        c[a[i].dia]++;
    }
    
    
    for(int i = 1; i <= maior; i++){
        c[i] += c[i - 1];
    }
    
    
    data b[T];
    
    for (int i = T - 1; i >= 0; i--) {
        b[c[a[i].dia] - 1] = a[i]; 
        c[a[i].dia]--;
    }
    
    for (int i = 0; i < T; i++) {
        a[i] = b[i];
    }
    
}
void contagemmes(data a[]){
    int maior=0;
    for(int i=0; i<T; i++){
        if(a[i].mes > maior){
            maior = a[i].mes;
        }
    }
    
    int c[maior+1];
    
    for(int i = 0; i <= maior; i++){
        c[i] = 0;
    }
    
    for(int i=0; i<T; i++){
        c[a[i].mes]++;
    }
    
    
    for(int i = 1; i <= maior; i++){
        c[i] += c[i - 1];
    }
    
    
    data b[T];
    
    for (int i = T - 1; i >= 0; i--) {
        b[c[a[i].mes] - 1] = a[i]; 
        c[a[i].mes]--;
    }
    
    for (int i = 0; i < T; i++) {
        a[i] = b[i];
    }
    
}
void contagemano(data a[]){
    int maior = a[0].ano;
    int menor = a[0].ano;

    for(int i = 1; i < T; i++){
        if(a[i].ano > maior) maior = a[i].ano;
        if(a[i].ano < menor) menor = a[i].ano;
    }

    int H = maior - menor + 1;
    int c[H];

    for(int i = 0; i < H; i++){
        c[i] = 0;
    }

    for(int i = 0; i < T; i++){
        c[a[i].ano - menor]++;
    }

    for(int i = 1; i < H; i++){
        c[i] += c[i - 1];
    }

    data b[T];
    for (int i = T - 1; i >= 0; i--) {
        b[c[a[i].ano - menor] - 1] = a[i]; 
        c[a[i].ano - menor]--;
    }

    for (int i = 0; i < T; i++) {
        a[i] = b[i];
    }
}

int main() {
    srand(time(NULL));
    data v[T];
    for(int i=0; i<T; i++){
        v[i].dia = (rand() % 31) + 1;
        v[i].mes = (rand() % 12) + 1;
        v[i].ano = (rand() % 25) + 2000;
    }
    data v2[T];
    for(int i=0; i<T; i++){
        v2[i].dia = v[i].dia;
        v2[i].mes = v[i].mes;
        v2[i].ano = v[i].ano;
    }    
    clock_t inicio_contagem = clock();
    contagemdia(v);
    contagemmes(v);
    contagemano(v);
    clock_t fim_contagem = clock();
    
    clock_t inicio_shell = clock();
    shellsortdia(v2);
    shellsortmes(v2);
    shellsortano(v2);
    clock_t fim_shell = clock();
    
    double tempo_contagem = (double)(fim_contagem - inicio_contagem) / CLOCKS_PER_SEC;
    double tempo_shell = (double)(fim_shell - inicio_shell) / CLOCKS_PER_SEC;

    printf("Tempo Contagem: %f segundos\n", tempo_contagem);
    printf("Tempo Shellsort: %f segundos\n", tempo_shell);


    return 0;
}
