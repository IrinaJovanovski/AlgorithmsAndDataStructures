#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// delovi koda su uzeti sa sajta predmeta i prilagodjeni zadatku - dokument "02_BinTree_src.doc"
// funkcija insertNode je uzeta iz knjige i prilagodjena specifikacijama zadatka
typedef struct st
{
    void **content;
    int top;
    int max_size;
} Stack;

typedef struct queue
{
    void **content;
    int front, rear;
    int max_size;
} Queue;


typedef struct btNode
{
    int key;
    int b;
    struct btNode *parent, *left, *right;
} BinTreeNode;

typedef struct binTree
{
    BinTreeNode *root;
    int treeHeight;
} BinTree;

typedef struct btVisitor
{
    BinTree     *tree;
    Stack       *stack;
    BinTreeNode *current;
} BinTreeVisitor;

Stack *createStack(int initial_size)
{
    if( initial_size < 1 ) return 0;
    else
    {
        Stack *ret = (Stack *)calloc(1, sizeof(Stack));

        if( ! ret ) return 0;
        ret->content = calloc(initial_size, sizeof(void *));
        if( ! ret->content )
        {
            free(ret);
            return 0;
        }
        ret->max_size = initial_size;
        return ret;
    }
}

void emptyStack(Stack *s)
{
    if( s )  s->top = 0;
}

void eraseStack(Stack *s)
{
    if( s )
    {
        free(s->content);
        free(s);
    }
}

int push(Stack *s, void *dat)
{
    if( ! s ) return 0;

    if( s->top == s->max_size*9/10 )
    {
        Stack **tmp=(Stack **)realloc(s->content,sizeof(void *)*s->max_size*2);
        if( ! tmp ) return 0;

        s->content = tmp;
        s->max_size *= 2;
    }
    s->content[s->top++] = dat;
    return 1;
}

void *pop(Stack *s)
{
    if( ! s ) return 0;
    if( s->top == 0 ) return 0;
    return s->content[--s->top];
}

int isEmptyStack(Stack *s)
{
    if( ! s )  return 1;
    return s->top == 0;
}

Queue *createQueue(int initial_size)
{
    Queue *ret = (Queue *)calloc(1, sizeof(Queue));

    if( ! ret ) return 0;
    ret->content = calloc(initial_size, sizeof(void *) );
    if( ! ret->content )
    {
        free(ret);
        return 0;
    }
    ret->max_size = initial_size;
    return ret;
}

void emptyQueue(Queue *q)
{
    if( q ) q->front = q->rear = 0;
}

void eraseQueue(Queue *q)
{
    if( q )
    {
        free(q->content);
        free(q);
    }
}

int insertIntoQueue(Queue *q, void *dat)
{
    if( ! q ) return 0;
    if( (q->rear + 1)%q->max_size == q->front )
    {
        void **c = (void **)calloc(q->max_size*2, sizeof(void *));
        int i, j;

        if( ! c )   return 0;
        for(i = 0, j = q->front; j != q->rear; j = (j+1) % q->max_size, i++)
            c[i] = q->content[j];

        q->front = 0; q->rear = i;
        free(q->content);
        q->content = c;
        q->max_size *= 2;
    }
    q->content[q->rear++] = dat;
    q->rear = q->rear % q->max_size;
    return 1;
}

void *removeFromQueue(Queue *q)
{
    void *ret = 0;
    if( ! q ) return 0;
    if( q->front == q->rear ) return 0;
    ret = q->content[q->front++];
    q->front = q->front % q->max_size;
    return ret;
}

int isEmptyQueue(Queue *q)
{
    if( ! q )  return 1;
    return q->front == q->rear;
}


BinTree *createBinTree() {
    BinTree *bt = (BinTree *)calloc(1, sizeof(BinTree) );
    if( ! bt )  return 0;
    bt->treeHeight = -1;
    return bt;
}

BinTreeVisitor *createVisitor(BinTree *bt) {
    if( ! bt ) return 0;
    else {
        BinTreeVisitor *ret=(BinTreeVisitor*)calloc(1,sizeof(BinTreeVisitor));
        if( ! ret ) return 0;

        ret->tree = bt;
        ret->stack = createStack(bt->treeHeight*2);
        if( ! ret->stack ) {
            free(ret);
            return 0;
        }
        return ret;
    }
}

void visitInOrder(BinTreeVisitor *v) {
    if( v ) {
        BinTreeNode *next;

        if( isEmptyStack(v->stack) && v->current ) {
            v->current = 0;
            return;
        }

        if( ! v->current ) {
            next = v->tree->root;
            while( next ) {
                push(v->stack, next);
                next = next->left;
            }
        }

        next = (BinTreeNode *)pop(v->stack);
        v->current = next;

        next = next->right;
        while(next){
            push(v->stack, next);
            next = next->left;
        }
    }
}


void visitPostOrder(BinTreeVisitor *v) {
    if( v ) {
        BinTreeNode *next;

        if( isEmptyStack(v->stack) && v->current ) {
            v->current = 0;
            return;
        }

        if( ! v->current ) {
            next = v->tree->root;
            while( next ) {
                push(v->stack, next);
                push(v->stack, next);
                next = next->left;
            }
        }
        while( ! isEmptyStack(v->stack) )
        {
            next = (BinTreeNode *)pop(v->stack);
            if( next ) {
                push(v->stack, 0);
                next = next->right;
                while(next)  {
                    push(v->stack, next);
                    push(v->stack, next);
                    next = next->left;
                }
            }  else {
                next = (BinTreeNode *)pop(v->stack);
                v->current = next;
                return;
            }
        }
        v->current = 0;
    }
}

BinTreeNode* exists(BinTree *bt,int k) {
    BinTreeNode *fp = NULL, *fx = NULL, *q = NULL;
    BinTreeNode *p = bt->root;
    BinTreeNode *x = p;
    while (p != NULL) {
        if (k == p->key) {
            return p;
        }
        if (k < p->key) {
            q = p->left;
        } else {
            q = p->right;
        }
        if (q != NULL) {
            if (q->b != 0) {
                fx = p;
                x = q;
            }
        }
        fp = p;
        p = q;
    }
    return NULL;
}

void rightRotation(BinTreeNode* x){
    BinTreeNode *y = x->left;
    BinTreeNode *temp = y->right;
    y->right = x;
    x->left = temp;
}

void leftRotation(BinTreeNode* x){
    BinTreeNode *y = x->right;
    BinTreeNode *temp = y->left;
    y->left = x;
    x->right = temp;
}

BinTreeNode* insertNode(BinTree *bt,int k){
    BinTreeNode *fp = NULL,*fx = NULL,*q = NULL;
    BinTreeNode *p = bt->root;
    BinTreeNode *x = p;
    int imbal;
    while(p != NULL){
        if(k == p->key){
            return p;
        }
        if(k < p->key){
            q = p->left;
        }else{
            q = p->right;
        }
        if(q != NULL){
            if(q->b != 0){
                fx = p;
                x = q;
            }
        }
        fp = p;
        p = q;
    }
    bt->treeHeight += 1;
    q = (BinTreeNode*)malloc(sizeof(BinTreeNode)); // stvaranje novog cvora
    q->key = k;
    q->b = 0;
    q->left = NULL;
    q->right = NULL;
    if(k < fp->key) {
        fp->left = q;
    }else{
        fp->right = q;
    }
    if(k < x->key){       // azuriranje balansa od kriticnog cvora
        p = x->left;
    }else{
        p = x->right;
    }
    BinTreeNode *y = p;
    while(p != q){
        if(k < p->key){
            p->b = 1;
            p = p->left;
        }else{
            p->b = -1;
            p = p->right;
        }
    }
    if(k < x->key){        //provera da li je narusena balansiranost
        imbal = 1;
    }else{
        imbal = -1;
    }
    if(x->b == 0){            // balans u x nije narusen
        x->b = imbal;
        return q;
    }
    if(x->b != imbal){        // balans u x je potpuno uravnotezen
        x->b = 0;
        return q;
    }
    if(y->b == imbal){         // balans narusen - jednostruka rotacija
        p = y;
        if(imbal == 1){
            rightRotation(x);
        }else{
            leftRotation(x);
        }
        x->b = 0;
        y->b = 0;
    }else{                     // dvostruka rotacija
        if(imbal == 1){
            p = y->right;
            leftRotation(y);
            x->left = p;
            rightRotation(x);
        }else{
            p = y->left;
            x->right = p;
            rightRotation(y);
            leftRotation(x);
        }
        if(p->b == 0){        // azuriranje balansa
            x->b = 0;
            y->b = 0;
        }else{
            if(p->b == imbal){
                x->b = -imbal;
                y->b = 0;
            }else{
                x->b = 0;
                y->b = imbal;
            }
            p->b = 0;
        }
    }
    if(fx == NULL){          //azuriranje novog korena podstabla u ocu krit. cvora
        bt->root = p;
    }else{
        if(x == fx->right){
            fx->right = p;
        }else{
            fx->left = p;
        }
    }
    return q;
}

void emptyBinTree(BinTree *bt){
    if( bt ) {
        BinTreeVisitor *visitor = createVisitor(bt);
        if( ! visitor )   return;
        visitPostOrder(visitor);
        while( visitor->current ) {
            free(visitor->current);
            visitPostOrder(visitor);
        }
        bt->root = 0;
        bt->treeHeight = -1;
    }
}

void deleteBinTree(BinTree *bt) {
    emptyBinTree(bt);
    free(bt);
}

void printTree(BinTree *tree) {
    if( ! tree )   return;
    if( ! tree->root )  return;
    else {
        Queue *q = createQueue( (int)pow(2, tree->treeHeight)  );
        int i, line_len = 62;
        int first_skip = line_len, in_between_skip;

        if( ! q )   return;
        insertIntoQueue(q, tree->root);
        for( i = 0; i <= tree->treeHeight; i++ ) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip-2)/2;
            for( k = 0; k < first_skip; k++) putchar(' ');
            for(k = 0; k < j; k++) {
                BinTreeNode *btn = (BinTreeNode *)removeFromQueue(q);
                if( btn ) {
                    insertIntoQueue(q, btn->left);
                    insertIntoQueue(q, btn->right);
                } else  {
                    insertIntoQueue(q, 0);
                    insertIntoQueue(q, 0);
                }
                if( btn )  printf("%2d", btn->key );
                else       printf("  ");
                for( l = 0; l < in_between_skip; l++) putchar(' ');
            }
            putchar('\n');
            putchar('\n');
        }
        eraseQueue(q);
    }
}

void difference(BinTree *A,BinTree *B){
    int array[100];
    int i = 0;

    BinTreeVisitor *visB = createVisitor(B);
    visitInOrder(visB);
    while( visB->current ) {
        array[i++] = visB->current->key;
        visitInOrder(visB);
    }
    BinTreeVisitor *visA = createVisitor(A);
    visitInOrder(visA);
    int true = 0;
    while( visA->current ) {
        for(int j=0;j<i;j++){
            if(visA->current->key == array[j]){
                true = 1;
            }
        }
        if(true == 0){
            printf("%d   ",visA->current->key);
        }
        visitInOrder(visA);
        true = 0;
    }

}

int main() {
    int i,key;
    BinTree *bt,*btB;
    while(1){
        printf("\nUnesite broj opcije:\n"
               "1. Formiranje praznog skupa A\n"
               "2. Umetanje novog elementa u skup A\n"
               "3. Provera pripadnosti skupu A\n"
               "4. Ispis skupa/stabla A\n"
               "5. Brisanje skupa A\n"
               "6. Formiranje praznog skupa B\n"
               "7. Umetanje novog elementa u skup B\n"
               "8. Provera pripadnosti skupu B\n"
               "9. Ispis skupa/stabla B\n"
               "10. Brisanje skupa B\n"
               "11. Razlika skupova A i B\n"
               "12. Razlika skupova B i A\n"
               "13. Kraj\n");
        scanf("%d",&i);
        if(i == 1){
            bt = createBinTree();
        }else if(i == 2){
            printf("\nUnesite element: ");
            scanf("%d",&key);
            if(bt->treeHeight == -1){
                bt->root = (BinTreeNode*)malloc(sizeof(BinTreeNode));
                bt->root->key = key;
                bt->root->b = 0;
                bt->root->left = NULL;
                bt->root->right = NULL;
                bt->treeHeight += 1;
                //bt->root->parent = NULL;
            }else{
                BinTreeNode *inserted = insertNode(bt,key);
            }

        }else if(i == 3){
            printf("\nUnesite element za proveru: ");
            scanf("%d",&key);
            BinTreeNode *check = exists(bt,key);
            if(check != NULL){
                printf("\nPretraga je bila USPESNA - cvor postoji u stablu.");
            }else{
                printf("\nPretraga je bila NEUSPESNA - cvor ne postoji u stablu.");
            }
        }else if(i == 4) {
            printTree(bt);
        }else if(i == 5){
            deleteBinTree(bt);
        }else if(i == 6){
            btB = createBinTree();
        }else if(i == 7){
            printf("\nUnesite element: ");
            scanf("%d",&key);
            if(btB->treeHeight == -1){
                btB->root = (BinTreeNode*)malloc(sizeof(BinTreeNode));
                btB->root->key = key;
                btB->root->b = 0;
                btB->root->left = NULL;
                btB->root->right = NULL;
                btB->treeHeight += 1;
                //btB->root->parent = NULL;
            }else{
                BinTreeNode *inserted = insertNode(btB,key);
            }

        }else if(i == 8){
            printf("\nUnesite element za proveru: ");
            scanf("%d",&key);
            BinTreeNode *check = exists(btB,key);
            if(check != NULL){
                printf("\nPretraga je bila USPESNA - cvor postoji u stablu.");
            }else{
                printf("\nPretraga je bila NEUSPESNA - cvor ne postoji u stablu.");
            }
        }else if(i == 9) {
            printTree(btB);
        }else if(i == 10){
            deleteBinTree(btB);
        }else if(i == 11){
            printf("\nA - B: ");
            difference(bt,btB);
        }else if(i == 12){
            printf("\nB - A: ");
            difference(btB,bt);
        }else if(i == 13){
            exit(0);
        }else{
            continue;
        }

    }
    return 0;
}