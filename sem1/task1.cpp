#include <stdio.h>
#include <string.h>
#include <conio.h>

const int m = 40;
const int n = 10;

int main(){
    int k, i, j, l;
    char A[m][n], sym='s';
    printf("Введите последовательность: ");
    i = 0;
    while(sym != "."){
        scanf("%[^,.]",&A[i]);
        scanf("%c",&sym);
        i++;
    }
    for(k=i, i = 0;i<k;i++){
        printf("%s", A[i]);
    }

    // for(k=i, i = 0;i<k-2;i++){

    // }
}
