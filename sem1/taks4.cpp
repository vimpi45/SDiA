#include <stdio.h>

const int nmax = 4;
int main()
{
    int n,i=0,j=0,mini=0,maxi=0,minj=0,maxj=0; 
    float A[nmax][nmax],max,min,save;
    scanf_s("%d", &n);
    if(n>1){
    for(i = 0; i < n; i++){ // внесение в массив
        for(j = 0; j < n; j++){
            scanf("%f", &A[i][j]);
        }
    }
    
    max = A[0][0]; 
    min = A[0][0];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            if (A[i][j] > max){
                maxi = i;
                maxj = j;
                max = A[i][j];}
            else
                if (A[i][j] < min){
                mini = i;
                minj = j;
                min = A[i][j];}
    }}
   //printf("\n max = %f max i = %d max j = %d", max, maxi, maxj);

    //printf("\n min = %f min i = %d min j = %d \n", min, mini, minj);
    if(mini == maxi){
        for (i = 0; i < n; i++) {
                save = A[i][minj];
                A[i][minj]=A[i][maxj];
                A[i][maxj]=save;
    }
    }else{
        for (j = 0; j < n; j++){
                save = A[mini][j];
                A[mini][j]=A[maxi][j];
                A[maxi][j]=save;
            }
    }
    
    for(i = 0; i < n; i++){ // вывод всего массива
        for(j = 0; j < n; j++){
            printf_s("%f ", A[i][j]);       
        }printf("\n");}
    }else{
        scanf_s("%f",&save);
        printf_s("%f ",save);
}
}