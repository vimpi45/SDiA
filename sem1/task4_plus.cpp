// #include <stdio.h>
// const int nmax = 3;
// int main()
// {
//     int n,g,i,j,y=1,A[nmax][nmax],sumi=0, sumilast=0,sumj=0,sumjlast=0, sumd = 0, sumb=0;
//     scanf_s("%d", &n);
//     if(n>1){
//     for(i = 0; i < n; i++)
//     for(j = 0; j < n; j++) 
//     scanf("%d", &A[i][j]);

//     for (i = 0, j = 0, g = n-1; i < n && y == 1; g--, i++){
//         sumilast = sumi;
//         sumi = 0;
//         sumb += A[i][i];
//         sumd += A[i][g];
//         sumjlast = sumj;
//         sumj = 0;
//         for (j = 0; j < n && y == 1; j++){
//             sumi += A[i][j];
//             sumj += A[j][i];
//         }
//         if((sumi!=sumilast || sumjlast!=sumj) && i != 0)y = 0;
//         else y = 1;
//         }

//         if (sumb != sumd) y = 0;
//         printf("%d", y);
//     }else{
//         scanf_s("%d",&y);
//         y = 1;
//         printf_s("%d",y);
// }
// }
// // 2 7 6
// // 9 5 1
// // 4 3 8


#include <stdio.h>
#include <string.h>
#include <conio.h>

const int m = 40;
const int n = 10;

int main(){
    int k, i=0, j, l=0, n = 0;
    char A[m][n], sym='s',g, v, x;
    while(sym != '.'){
        scanf("%[^,.]",&A[i]);
        scanf("%c",&sym);
        i++;
    }
    printf("%s",A[0]);
    // strnset(A[0],'0', 3);

    for(k=i, i = 0;i<k;i++){
        // printf("%d \n", i);//
        if(strchr(A[i], 'abc')){
        //    strnset(A[i],'0','abc');
        //     printf("%s \n", A[i]);
        //     while(strchr(A[i], 'abc')
            n = strlen(A[i])-1;
            // printf("%c",A[0][0]);
            // printf("%d \n", n);//
            for(j = 0;j<(n-2); j++){ 
                g = A[i][j];
                printf("%c",g);
                v = A[i][j+1];
                printf("%c",v);
                x= A[i][j+2];
                printf("%c",x);
                if (g == 'a' && v == 'b' && x == 'c') l++; 
                // printf("%c",A[i][j]);     
            }
    }

    }
    printf("%d",l);
    // for(k=i, i = 0;i<k-2;i++){

    // }
}
