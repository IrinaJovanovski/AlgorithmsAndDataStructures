#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long factorial(int x){
    long y=1;
    for(int i = x;i > 1;i--){
        y *= i;
    }
    return y;
}

int bin_coef(int n,int k){
    int res;
    if(n == k){
        return 1;
    }
    if((n == 1 && (k == 1 || k == 0)) || (n == 0 && (k == 0 || k == 1))){
        return 1;
    }
    res = factorial(n)/(factorial(k)*factorial(n-k));
    return res;
}
int* tr_row(int n){
    int T[n][n];
    for (int i = 0;i < n;i++){
        for (int j = 0;j <= i;j++){
            if(j == 0 || j == i){
                T[i][j] = 1;
                continue;
            }
            if((i % 2 == 0) && (j % 2 == 1)){
                T[i][j] = T[i-1][j-1] + T[i-1][j] - bin_coef((i/2 - 1),((j-1)/2));
            }else{
                T[i][j] = T[i-1][j-1] + T[i-1][j];
            }
        }
    }
    /*for (int row=0; row<n; row++)
    {
        for(int columns=0; columns<=row; columns++)
        {
            printf("%d     ", T[row][columns]);
        }
        printf("\n");
    }*/
    int *row  = calloc(n,sizeof(int));
    for (int i = 0;i < n;i++){
        row[i] = T[n-1][i];
    }
    return row;
}
int binary_search(const int *array,int key, int n, int *stepsB,int print){
    *stepsB = 0;
    n = ceil(n/2);
    int low = 0;
    int high = n;
    int mid;
    while(low <= high){
        mid = (low + high) / 2;
        if(print == 1){
            printf("%d -> ",array[mid]);
        }
        if(key == array[mid]){
            *stepsB += 1;
            return mid;
        }else if(key < array[mid]){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
        *stepsB += 2;
    }
    return -1;
}

int ternary_search(const int *array,int key, int n,int* stepsT,int print){
    *stepsT = 0;
    n = ceil(n/2);
    int low = 0;
    int high = n;
    int midA,midB;
    while(low <= high){
        midA = low + (high - low) / 3;
        if(print == 1){
            printf("%d ",array[midA]);
        }
        midB = high - (high - low) / 3;
        if(print == 1){
            printf("i %d -> ",array[midB]);
        }
        if(key == array[midA]){
            *stepsT += 1;
            return midA;
        }else if(key == array[midB]){
            *stepsT += 2;
            return midB;
        }
        *stepsT += 2;
        if(key < array[midA]){
            high = midA - 1;
            *stepsT += 1;
        }else if(key > array[midB]){
            low = midB + 1;
            *stepsT += 2;
        }else{
            low = midA + 1;
            high = midB - 1;
            *stepsT += 2;
        }

    }
    return -1;
}
int main() {
    int *row,stepsB,stepsT;
    int i,n,key;
    while(1){
        printf("\nUnesite broj opcije:\n"
               "1. Unos rednog broja reda trougla\n"
               "2. Ispis koraka i rezultata pretrage - binarna pretraga\n"
               "3. Ispis koraka i rezultata pretrage - ternarna pretraga\n"
               "4. Poredjenje performansi\n"
               "5. Prekid programa\n");
        scanf("%d",&i);
        if(i == 1){
            printf("\nUnesite broj reda: ");
            scanf("%d",&n);
            row = tr_row(n);
            for(int el=0; el < n; el++)
            {
                printf("%d  ", row[el]);
            }

        }else if(i == 2){
            printf("\nUnesite kljuc za pretragu: ");
            scanf("%d",&key);
            int found = binary_search(row,key,n,&stepsB,1);
            if (found == -1){
                printf("\nPretraga je bila neuspesna.\n");
            }else{
                printf("\nPronadjen je kljuc %d.\n",row[found]);
            }

        }else if(i == 3){
            printf("\nUnesite kljuc za pretragu: ");
            scanf("%d",&key);
            int found = ternary_search(row,key,n,&stepsT,1);
            if (found == -1){
                printf("\nPretraga je bila neuspesna.\n");
            }else{
                printf("\nPronadjen je kljuc %d.\n",row[found]);
            }
        }else if(i == 4) {
            double pB = 0, pT = 0;
            for(int k=0;k<n;k++){
                key = row[k];
                int found = binary_search(row,key,n,&stepsB,0);
                if (found != -1){
                    pB += stepsB;
                }
                found = ternary_search(row,key,n,&stepsT,0);
                if (found != -1){
                    pT += stepsT;
                }
            }
            pB = pB/n;
            pT = pT/n;
            if(pT  < pB){
                printf("\nTernarna pretraga je efikasnija za %.2f koraka.\n",pB-pT);
            }else if(pT  > pB){
                printf("\nBinarna pretraga je efikasnija za %.2f koraka.\n",pT-pB);
            }else{
                printf("\nObe pretrage su podjednako efikasne - %.2f koraka.\n",pT);
            }

        }else if(i == 5) {
            exit(0);
        }else{
            continue;
        }

    }
    return 0;
}
