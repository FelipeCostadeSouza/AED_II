#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    RED,
    BLACK
} Color;

typedef struct arv2 {
    int info;
    struct arv2 *esq1;
    struct arv2 *dir1;
} TArvABB;
typedef TArvABB *PArvABB;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

typedef struct Node1 {
    int data;
    Color color;
    struct Node1 *left;
    struct Node1 *right;
    struct Node1 *parent;
} Node1;

typedef struct RedBlackTree {
    Node1 *root;
    Node1 *NIL; 
} RedBlackTree;

Node1* createNode(int data, Node1 *NIL) {
    Node1 *newNode = (Node1*)malloc(sizeof(Node1));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

void leftRotateVP(RedBlackTree *tree, Node1 *x) {
    Node1 *y = x->right;
    x->right = y->left;

    if (y->left != tree->NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rightRotateVP(RedBlackTree *tree, Node1 *x) {
    Node1 *y = x->left;
    x->left = y->right;

    if (y->right != tree->NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void fixInsert(RedBlackTree *tree, Node1 *k) {
    while (k != tree->root && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node1 *uncle = k->parent->parent->right;

            if (uncle->color == RED) {
                k->parent->color = BLACK;
                uncle->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotateVP(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotateVP(tree, k->parent->parent);
            }
        } else {
            Node1 *uncle = k->parent->parent->left;

            if (uncle->color == RED) {
                k->parent->color = BLACK;
                uncle->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotateVP(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotateVP(tree, k->parent->parent);
            }
        }
    }
    tree->root->color = BLACK; 
}

RedBlackTree* createRedBlackTree() {
    RedBlackTree *tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    
    tree->NIL = (Node1*)malloc(sizeof(Node1));
    tree->NIL->data = 0;
    tree->NIL->color = BLACK;
    tree->NIL->left = tree->NIL;
    tree->NIL->right = tree->NIL;
    tree->NIL->parent = NULL;
    
    tree->root = tree->NIL;
    return tree;
}

void insert(RedBlackTree *tree, int data) {
    Node1 *node = createNode(data, tree->NIL);

    Node1 *parent = NULL;
    Node1 *current = tree->root;

    while (current != tree->NIL) {
        parent = current;
        if (node->data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;

    if (parent == NULL) {
        tree->root = node;
    } else if (node->data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    if (node->parent == NULL) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == NULL) {
        return;
    }

    fixInsert(tree, node);
}

Node1* searchVP(RedBlackTree *tree, int data) {
    Node1 *current = tree->root;
    while (current != tree->NIL) {
        if (data == current->data) {
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

Node* searchAVL(Node *a, int x) {
    while (a != NULL && a->key != x) {
        if (x < a->key) {
            a = a->left;
        } else {
            a = a->right;
        }
    }
    return a;
}

PArvABB inserirABB(PArvABB a, int x) {
    if(a==NULL) {
        PArvABB novo=(PArvABB)malloc(sizeof(TArvABB));
        novo->info=x;
        novo->esq1=novo->dir1=NULL;
        return novo;
    }
    if(x<a->info) {
        a->esq1=inserirABB(a->esq1, x);
    } else {
        a->dir1=inserirABB(a->dir1, x);
    }
    return a;
}

PArvABB searchABB(PArvABB a, int x) {
    while (a != NULL && a->info != x) {
        if (x < a->info) {
            a = a->esq1;
        } else {
            a = a->dir1;
        }
    }
    return a;
}

PArvABB remover(PArvABB a, int x) {
    PArvABB t,pai;
    if(a==NULL) {
        return NULL;
    }
    if(x<a->info) {
        a->esq1=remover(a->esq1, x);
    } else if(x>a->info) {
        a->dir1=remover(a->dir1, x);
    } else {
        if(a->esq1==NULL && a->dir1==NULL) {
            free(a);
            return NULL;
        }
        if(a->dir1==NULL) {
            t=a->esq1;
            free(a);
            return t;
        }
        if(a->esq1==NULL) {
            t=a->dir1;
            free(a);
            return t;
        }
        pai=a;
        t=a->esq1;
        while(t->dir1!=NULL) {
            pai=t;
            t=t->dir1;
        }
        a->info=t->info;
        if(pai==a) {
            pai->esq1=t->esq1;
        } else {
            pai->dir1=t->esq1;
        }
        free(t);
        return a;
    }
}

int altura(PArvABB a) {
    if(a==NULL) {
        return -1;
    }

    int alturaesq=altura(a->esq1);
    int alturadir=altura(a->dir1);

    if(alturaesq>alturadir) {
        return (alturaesq + 1);
    } else {
        return (alturadir+1);
    }
}

void buscaBinaria(int v[], int x) {
    int inicio = 0;
    int fim = 10000 - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (v[meio] == x) {
            printf("-----encontrado-----\n");
            return; 
        }

        if (v[meio] < x) {
            inicio = meio + 1; 
        } else {
            fim = meio - 1; 
        }
    }

    return; 
}

void shellsort(int a[]){
    for (int gap = 10000 / 2; gap > 0; gap /= 2) { 
        for (int i = gap; i < 10000; i++) {
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

void busca(int v[], int x){
    for(int i=0; i<10000; i++){
        if(v[i]==x){
            printf("encontrado\n");
            return; 
        }
    }
    return;
}

int height(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}

int get_balance(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* rotate_right(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
  
    return x;
}

Node* rotate_left(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
  
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert_node(Node* node, int key) {
    if (node == NULL) {
        return create_node(key);
    }

    if (key < node->key) {
        node->left = insert_node(node->left, key);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

int alturaVP(Node1 *node, Node1 *NIL) {
    if (node == NIL || node == NULL) {
        return -1;
    }

    int alturaEsq = alturaVP(node->left, NIL);
    int alturaDir = alturaVP(node->right, NIL);

    if (alturaEsq > alturaDir) {
        return alturaEsq + 1;
    } else {
        return alturaDir + 1;
    }
}

int main() {
    int a=10000;
    int v[a];
    clock_t inicio_v = clock();
    
    srand(time(NULL));
    for (int i = 0; i < a; i++) {
        v[i] = (rand() % 10000) + 1;
    }
    clock_t fim_v = clock();
    double tempo_v = (double)(fim_v - inicio_v) / CLOCKS_PER_SEC;
    printf("Tempo de inserção vetor aleatorio: %f segundos\n", tempo_v);
    
    int v1[a];
    
    clock_t inicio_v1 = clock();
    
    for (int i = 0; i < a; i++) {
        v1[i] = v[i];
    }
    shellsort(v1);
    
    clock_t fim_v1 = clock();
    double tempo_v1 = (double)(fim_v1 - inicio_v1) / CLOCKS_PER_SEC;
    printf("Tempo de inserção vetor ordenado: %f segundos\n", tempo_v1);
    
    PArvABB A = NULL;
    
    clock_t inicio_a = clock();
    
    for (int i = 0; i < a; i++) {
        A = inserirABB(A, v[i]);
    }
    
    clock_t fim_a = clock();
    double tempo_a = (double)(fim_a - inicio_a) / CLOCKS_PER_SEC;
    printf("Tempo de inserção árvore ABB: %f segundos\n", tempo_a);
    
    Node *A2 = NULL;
    
    clock_t inicio_AVL = clock();
    
    for (int i = 0; i < a; i++) {
        A2 = insert_node(A2, v[i]);
    }
    
    clock_t fim_AVL = clock();
    double tempo_AVL = (double)(fim_AVL - inicio_AVL) / CLOCKS_PER_SEC;
    printf("Tempo de inserção árvore AVL: %f segundos\n", tempo_AVL);

    RedBlackTree *treeVP = createRedBlackTree();

    clock_t inicio_VP = clock();
    for (int i = 0; i < a; i++) {
        insert(treeVP, v[i]);
    }
    clock_t fim_VP = clock();
    double tempo_VP = (double)(fim_VP - inicio_VP) / CLOCKS_PER_SEC;
    printf("Tempo de inserção árvore Rubro-Negra: %f segundos\n", tempo_VP);

    clock_t inicio_B = clock();
    busca(v, 50);
    clock_t fim_B = clock();
    double tempo_B = (double)(fim_B - inicio_B) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 vetor aleatorio: %f segundos\n", tempo_B);
    
    clock_t inicio_B1 = clock();
    busca(v, 5000);
    clock_t fim_B1 = clock();
    double tempo_B1 = (double)(fim_B1 - inicio_B1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 vetor aleatorio: %f segundos\n", tempo_B1);
    
    clock_t inicio_v1B = clock();
    buscaBinaria(v1, 50);
    clock_t fim_v1B = clock();
    double tempo_v1B = (double)(fim_v1B - inicio_v1B) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 vetor ordenado: %f segundos\n", tempo_v1B);
    
    clock_t inicio_v1B2 = clock();
    buscaBinaria(v1, 5000);
    clock_t fim_v1B2 = clock();
    double tempo_v1B2 = (double)(fim_v1B2 - inicio_v1B2) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 vetor ordenado: %f segundos\n", tempo_v1B2);
    
    PArvABB C = NULL;
    PArvABB B = NULL;
    
    clock_t inicio_ab = clock();
    C = searchABB(A, 50);
    clock_t fim_ab = clock();
    double tempo_ab = (double)(fim_ab - inicio_ab) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 arvore: %f segundos\n", tempo_ab);
    
    clock_t inicio_ab1 = clock();
    B = searchABB(A, 5000);
    clock_t fim_ab1 = clock();
    double tempo_ab1 = (double)(fim_ab1 - inicio_ab1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 arvore: %f segundos\n", tempo_ab1);
    
    Node *B1 = NULL;
    Node *C1 = NULL;
    
    clock_t inicio_AVL1 = clock();
    C1 = searchAVL(A2, 50);
    clock_t fim_AVL1 = clock();
    double tempo_AVL1 = (double)(fim_AVL1 - inicio_AVL1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 arvoreAVL: %f segundos\n", tempo_AVL1);
    
    clock_t inicio_AVL2 = clock();
    B1 = searchAVL(A2, 5000);
    clock_t fim_AVL2 = clock();
    double tempo_AVL2 = (double)(fim_AVL2 - inicio_AVL2) / CLOCKS_PER_SEC;
    printf("Tempo de busca 5000 arvoreAVL: %f segundos\n", tempo_AVL2);
    
    clock_t inicio_VP1 = clock();
    Node1 *C2 = searchVP(treeVP, 50);
    clock_t fim_VP1 = clock();
    double tempo_VP1 = (double)(fim_VP1 - inicio_VP1) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 arvore Rubro-Negra: %f segundos\n", tempo_VP1);
    
    clock_t inicio_VP2 = clock();
    Node1 *C3 = searchVP(treeVP, 50);
    clock_t fim_VP2 = clock();
    double tempo_VP2 = (double)(fim_VP2 - inicio_VP2) / CLOCKS_PER_SEC;
    printf("Tempo de busca 50 arvore Rubro-Negra: %f segundos\n", tempo_VP2);
    
    int h = height(A2->right);
    int h1 = height(A2->left);
    
    printf("Altura sub-esquerda AVL: %d \n", h1);
    printf("Altura sub-direita AVL: %d \n", h);
    
    int x = altura(A->dir1);
    int x1 = altura(A->esq1);
    
    printf("Altura sub-esquerda: %d \n", x1);
    printf("Altura sub-direita: %d \n", x);
    
    int Y = alturaVP(treeVP->root->left, treeVP->NIL);
    int Y1 = alturaVP(treeVP->root->right, treeVP->NIL);
    
    printf("Altura sub-esquerda VP: %d \n", Y);
    printf("Altura sub-direita VP: %d \n", Y1);

    return 0;
}
