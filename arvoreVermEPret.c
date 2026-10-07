#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RED,
    BLACK
} Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct RedBlackTree {
    Node *root;
    Node *NIL; 
} RedBlackTree;

Node* createNode(int data, Node *NIL) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

void leftRotate(RedBlackTree *tree, Node *x) {
    Node *y = x->right;
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

void rightRotate(RedBlackTree *tree, Node *x) {
    Node *y = x->left;
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

static void rbTransplant(RedBlackTree *tree, Node *u, Node *v) {
    if (u->parent == tree->NIL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

static Node* treeMinimum(RedBlackTree *tree, Node *x) {
    while (x->left != tree->NIL) {
        x = x->left;
    }
    return x;
}

static void deleteFixup(RedBlackTree *tree, Node *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root; 
            }
        } else {

            Node *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}


void deleteNode(RedBlackTree *tree, Node *z) {
    if (z == NULL || z == tree->NIL) return;

    Node *y = z;
    Node *x;
    Color yOriginalColor = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == BLACK) {
        deleteFixup(tree, x);
    }
}

Node* search(RedBlackTree *tree, int data) {
    Node *current = tree->root;
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

void deleteByVal(RedBlackTree *tree, int data) {
    Node *z = search(tree, data);
    if (z == NULL) {
        printf("Valor %d nao encontrado na arvore.\n", data);
        return;
    }
    deleteNode(tree, z);
}

void fixInsert(RedBlackTree *tree, Node *k) {
    while (k != tree->root && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node *uncle = k->parent->parent->right;

            if (uncle->color == RED) {
                
                k->parent->color = BLACK;
                uncle->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    
                    k = k->parent;
                    leftRotate(tree, k);
                }
                
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(tree, k->parent->parent);
            }
        } else {
           
            Node *uncle = k->parent->parent->left;

            if (uncle->color == RED) {
                k->parent->color = BLACK;
                uncle->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(tree, k->parent->parent);
            }
        }
    }
    tree->root->color = BLACK; 
}

RedBlackTree* createRedBlackTree() {
    RedBlackTree *tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->data = 0;
    tree->NIL->color = BLACK;
    tree->NIL->left = tree->NIL;
    tree->NIL->right = tree->NIL;
    tree->NIL->parent = NULL;
    
    tree->root = tree->NIL;
    return tree;
}

void insert(RedBlackTree *tree, int data) {
    Node *node = createNode(data, tree->NIL);

    Node *parent = NULL;
    Node *current = tree->root;

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

void inorder(RedBlackTree *tree, Node *node) {
    if (node != tree->NIL) {
        inorder(tree, node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "RED" : "BLACK");
        inorder(tree, node->right);
    }
}

void inorder2(RedBlackTree *tree, Node *node) {
    if (node != tree->NIL) {
        printf("%d(%s) ", node->data, node->color == RED ? "RED" : "BLACK");
        inorder2(tree, node->left);
        inorder2(tree, node->right);
    }
}



int main() {
    RedBlackTree *rbt = createRedBlackTree();
    
    insert(rbt, 41);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 38);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 31);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 12);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 19);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 8);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 50);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 1);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 100);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    insert(rbt, 101);

    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    deleteByVal(rbt, 50);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");
    
    deleteByVal(rbt, 8);
    inorder(rbt, rbt->root);
    printf("\n");
    inorder2(rbt, rbt->root);
    printf("\n-----------------------\n");

    return 0;
}
