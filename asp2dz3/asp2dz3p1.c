#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int num;
    float x;
    float y;
    float z;
    int visited;
    struct node *next;
}Node;
int sizeofArray(int *array){
    int cnt = 0;
    while (array[cnt] != 0){
        cnt++;
    }
    return cnt;
}
Node* addNode(int *indices,Node *head,int name,float x,float y,float z){
    int len = 0;
    len = sizeofArray(indices)-1;
    if(name == 1){
        head->num = name;
        head->x = x;
        head->y = y;
        head->z = z;
        head->visited = 0;
        head->next = NULL;
    }else{
        Node *temp = head,*newnode;
        while(temp->next) {
            temp = temp->next;
        }
        newnode = malloc(sizeof(Node));
        newnode->num = name;
        newnode->x = x;
        newnode->y = y;
        newnode->z = z;
        newnode->visited = 0;
        newnode->next = NULL;
        temp->next = newnode;
    }
    indices[len+1] = indices[len];
    return head;
}
Node* deleteNode(int *indices, int *edges,Node *list,int n){
    int start,p,end,el,t,dif;
    Node *lista = list,*temp = list;
    while(lista != NULL){
        if(lista->next->num == n){
            temp = lista->next;
            lista->next = lista->next->next;
            free(temp);
            break;
        }
        lista = lista->next;
    }
    p = sizeofArray(indices);
    dif = indices[n] - indices[n-1];
    start = indices[n-1]-1;
    end = indices[n]-1;
    t = n;
    while(t < p){
        indices[t] = indices[t+1];
        if(indices[t] == 0){
            break;
        }
        indices[t] = indices[t] - dif;
        t++;
    }

    for(int i = 0;i < dif;i++){
        t = start;
        p = sizeofArray(edges);
        while(t<p){
            edges[t] = edges[t+1];
            t++;
        }
    }
    for (int i = 0;i < sizeofArray(indices);i++){
        p = sizeofArray(edges);
        start = indices[i]-1;
        end = indices[i+1]-1;
        for (int j = start;j < end;j++){
            if(edges[j] == n){
                for (int k = j;k < p;k++){
                    edges[k] = edges[k+1];
                }
                indices[i+1] = indices[i+1] - 1;
                break;
            }
        }
    }
    printf("\n");
    int i = 0;
    while(edges[i]!= 0){
        printf("%d ",edges[i]);
        i++;
    }
    return list;
}

int* addEdges(int *edges,int *indices,int f,int s){
    int org,p;
    p = f+1;
    org = indices[f]-1;
    indices[f] = indices[f] + 1;
    while(indices[p] != 0){
        indices[p] = indices[p] + 1;
        p++;
    }
    p = sizeofArray(edges);
    while(p > org){
        edges[p] = edges[p-1];
        p--;
    }
    edges[org] = s;
    /*int i = 0;
    while(edges[i] != 0){
        printf("%d, ",edges[i]);
        i++;
    }
    printf("\n");
    int j = 0;
    while(indices[j] != 0){
        printf("%d, ",indices[j]);
        j++;
    }*/

    return edges;
}

void deleteEdge(int *indices,int *edges,int f,int s){
    int start,p,end,el;
    p = f+1;
    start = indices[f-1]-1;
    end = indices[f]-1;
    if(start == end){
        return;
    }
    indices[f] = indices[f] - 1;
    while(indices[p] != 0){
        indices[p] = indices[p] - 1;
        p++;
    }
    p = sizeofArray(edges);
    el = sizeofArray(edges);
    for(int i = start;i < end;i++){
        if(edges[i] == s){
            el = i;
            break;
        }
    }
    while(el < p){
        edges[el] = edges[el+1];
        el++;
    }
    edges[p-1] = 0;

}
Node* makeGraph(int *indices,Node *head,int dim) {
    int i = 0;
    head->num = 1;
    head->x = 0;
    head->y = 0;
    head->z = 0;
    head->visited = 0;
    head->next = NULL;
    Node *temp = head, *newnode;
    while (i < dim) {
        indices[++i] = 1;
        if (i > 1) {
            newnode = malloc(sizeof(Node));
            newnode->num = i;
            newnode->x = 0;
            newnode->y = 0;
            newnode->z = 0;
            newnode->visited = 0;
            newnode->next = NULL;
            temp->next = newnode;
            temp = newnode;
            /*while (temp) {
                if (temp->next == NULL) {
                    temp->next = newnode;
                    break;
                } else {
                    temp = temp->next;
                }
        }*/
        }
    }
    return head;
}
void printGraph(int *indices,int *edges,Node *head){
    Node *temp = head;
    int lg;
    for(int i = 0;i < (sizeofArray(indices)-1);i++){
        printf("\nMina %d (%.2f,%.2f,%.2f):",temp->num,temp->x,temp->y,temp->z);
        lg = indices[i+1]-indices[i];
        for(int j = indices[i]-1;j<(lg+indices[i]-1);j++){
            printf(" %d",edges[j]);
            if(j<(lg+indices[i]-2)){
                putchar(',');
            }
        }
        temp = temp->next;
    }
}
void freeList(Node *head){
    Node *prev;
    while(head){
        prev = head;
        head = head->next;
        free(prev);
    }
}
void deleteGraph(int *indices,int *edges,Node *list){
    free(indices);
    free(edges);
    freeList(list);
}
int circle(Node n1,Node n2){
    float x1,x2,y1,y2,r1;
    x1 = n1.x;
    y1 = n1.y;
    r1 = n1.z;
    x2 = n2.x;
    y2 = n2.y;
    if(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))<=(r1*r1)){
        return 1;
    }else{
        return 0;
    }
}
int iterateList(Node *list,int c,int *indices,int *edges,int max);

int iterateEdges(Node *list,int lg,int c,int *indices,int *edges,int max){

    for(int j = indices[c]-1;j<(lg+indices[c]-1);j++){
        Node *curr = list;
        while(curr){
            if(curr->num == edges[j]){
                break;
            }
            curr = curr->next;
        }
        if(curr->visited == 0){
            printf("%d ",edges[j]);
            max = iterateList(list,edges[j],indices,edges,max);
        }else{
            continue;
        }
    }
    return max;
}

int iterateList(Node *list,int c,int *indices,int *edges,int max){
        c = c - 1;
        int lg = indices[c+1]-indices[c];
        if(lg != 0){
            Node* vis = list;
            while(vis){
                if(vis->num == (c+1)){
                    vis->visited = 1;
                    max += 1;
                    break;
                }
                vis = vis->next;
            }
            max = iterateEdges(list,lg,c,indices,edges,max);
            return max;
        }else{
            return max;
        }

}
int Graph_BFS(int *indices,int *edges,Node *list,int c,int n){
    int max = 0;
    Node *save = list;
    Node *temp = list;
    while(temp){
        if(temp->num == c){
            break;
        }
        temp = temp->next;
    }
    int lg;
    printf("\nMina %d (%.2f,%.2f,%.2f): ",temp->num,temp->x,temp->y,temp->z);
    max = iterateList(list,c,indices,edges,max);
    while(save){
        save->visited = 0;
        save = save->next;
    }
    return max;
}

int isEmpty(Node *queue){
    return queue == NULL;
}

void enqueue(Node **queue, int number, float x, float y, float z){

    Node *newnode = malloc(sizeof(Node));
    newnode->num = number;
    newnode->x = x;
    newnode->y = y;
    newnode->z = z;
    newnode->next = NULL;
    if (isEmpty(*queue))
    {
        *queue = newnode;
    }
    else
    {
        Node *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

int dequeue(Node **queue){

    int newnode = (*queue)->num;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return newnode;
}

int GraphBFS(Node *list,int *indices,int *edges,int n)
{
    //for()
    int max = 0,curr,dif,adj,first = 0;
    Node *queue = NULL,*temp = list;
    while(temp){
        if(temp->num == n){
            break;
        }
        temp = temp->next;
    }
    temp->visited = 1;
    enqueue(&queue, n,temp->x,temp->y,temp->z);
    while (!isEmpty(queue)){
        Node *t = list;
        printGraph(indices,edges,queue);
        curr = dequeue(&queue);
        if(first == 0){
            printf("\nMina %d (%.2f,%.2f,%.2f): ",temp->num,temp->x,temp->y,temp->z);
            first++;
        }else{
            printf("%d ",temp->num);
        }

        dif = indices[n] - indices[n-1];
        for (int i = indices[n-1];i<indices[n];i++){
            adj = edges[i];
            t = list;
            while(t){
                if(t->num == adj){
                    break;
                }
                t = t->next;
            }
            if (t->visited == 0)
            {
                t->visited = 1;
                max++;
                enqueue(&queue, adj,t->x,t->y,t->z);
            }
        }
    }
    return max;
}



int main() {
    int *indices,*edges,i;
    Node *list;
    indices = calloc(100,sizeof(int));
    edges = calloc(100,sizeof(int));
    list = malloc(100*sizeof(Node));
    indices[0] = 1;
    while(1){
        printf("\nUnesite broj opcije:\n1. Napravite graf n dimenzija \n2. Dodajte cvor\n3. Dodajte granu\n4. Uklonite cvor\n5. Uklonite granu\n6. Ispisi graf\n7. Obrisi graf\n8. Kreiraj graf iz fajla\n9. Efikasnost proizvoljne mine\n10. Efikasnost max mine\n11. Kraj\n ");
        scanf("%d",&i);
        if(i == 1){
            int dim;
            printf("\nUnesite dimenzije: ");
            scanf("%d",&dim);
            list = makeGraph(indices,list,dim);
        }else if(i == 2){
            int name;
            float x,y,z;
            printf("Unesite naziv (broj) cvora: ");
            scanf("%d",&name);
            printf("Unesite koordinate: ");
            scanf("%f%f%f",&x,&y,&z);
            list = addNode(indices,list,name,x,y,z);
        }else if(i == 3){
            int f,s;
            printf("Unesite cvorove(usmerenost je od prvog ka drugom): ");
            scanf("%d%d",&f,&s);
            edges = addEdges(edges,indices,f,s);
        }else if(i == 4) {
            int n;
            printf("Unesite cvor za brisanje: ");
            scanf("%d",&n);
            list = deleteNode(indices, edges, list,n);
            int i = 0;
            while(indices[i]!= 0){
                printf("%d ",indices[i]);
                i++;
            }
        }else if(i == 5){
            int f,s;
            printf("Unesite cvorove(usmerenost je od prvog ka drugom): ");
            scanf("%d%d",&f,&s);
            deleteEdge(indices, edges,f,s);
        }else if(i == 6){
            printGraph(indices,edges,list);
        }else if(i == 7){
            deleteGraph(indices,edges,list);
        }else if(i == 8){
            FILE *in = fopen("C:\\...\\mine","r"); //! ubaciti putanju do fajla mine
            if(!in){
                printf("sh");
            }
            char line[50];
            int i = -1,n;
            float x,y,z;
            Node *temp = list,*sec = list;
            while(fgets (line, 50, in)){
                i++;
                if (i == 0){
                    n = atoi(line);
                    continue;
                }
                x = atof(strtok(line," "));
                y = atof(strtok(NULL," "));
                z = atof(strtok(NULL," "));
                list = addNode(indices,list,i,x,y,z);
            }
            while(temp){
                sec = list;
                while(sec){
                    if(circle(*temp,*sec) == 1){
                        addEdges(edges,indices,temp->num,sec->num);
                    }
                    sec = sec->next;
                }
                temp = temp->next;
            }
            int max,*num,curr=0;
            num = calloc(100,sizeof(int));
            fclose(in);
        }else if(i == 9){
            int mina,n;
            int max,*num,curr=0;
            num = calloc(100,sizeof(int));
            printf("Unesite minu ciju efikasnist zelite:");
            scanf("%d",&mina);
            max = Graph_BFS(indices,edges,list,mina,n);

        }else if(i == 10){
            int n;
            int max = 0,*num,curr = 0;
            num = calloc(100,sizeof(int));
            for(i = 1;i < sizeofArray(indices);i++){
                if(Graph_BFS(indices,edges,list,i,n) > max){
                    max = Graph_BFS(indices,edges,list,i,n);
                }
            }
            for(i = 1;i < sizeofArray(indices);i++){
                if(Graph_BFS(indices,edges,list,i,n) == max){
                    num[curr++] = i;
                }
            }
            if(max == 0){
                printf("\nSve mine imaju istu efikasnost tj. eksplodiraju jedino one same.");
            }else{
                printf("\nNajvecu efikasnost ima mina/e: ");
                for(int l = 0;l<sizeofArray(num);l++){
                    printf("%d ",num[l]);
                }
            }

        }else if(i == 11){
            exit(0);
        }

    }
    return 0;
}
