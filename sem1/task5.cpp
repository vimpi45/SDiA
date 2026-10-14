#include <stdio.h>

#include <conio.h>

const int maxMetr = 4;
void inputMatrix(int n, float matrix[][maxMetr]){
    for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      scanf_s("%f",&matrix[i][j]);
}
void inputVektor(int n, float vector[]){
    for(int i=0; i<n; i++)
      scanf_s("%f",&vector[i]);

}
// void outputMatrix(int n, float matrix[][maxMetr]){
//     for(int i=0;i<n;i++){

//     for(int j=0;j<n;j++)
//       printf("%f ",matrix[i][j]);
//     printf("\n");}
// }
void umn(int n, float matrix[][maxMetr], float vector[], float *k){
    for(int i=0; i<n; i++){
        k[i]=0;
    for(int j=0; j<n; j++)
        k[i]+=matrix[i][j]*vector[j];
    
    }
}
float scal(float p[ ], float q[ ], int n){
    int i;  
    float s = 0;
    for ( i = 0; i < n; i++)
        s += p[i] * q[i];
    return s;

}
int main(){
    int n;
    float A[maxMetr][maxMetr], B[maxMetr][maxMetr], C[maxMetr][maxMetr], x[maxMetr], y[maxMetr], k1[maxMetr],k2[maxMetr],k3[maxMetr], a,b,c;
    printf("Введите размерность:\n");
    scanf_s("%d", &n);
    printf("Введите матрицу А:\n");
    inputMatrix(n, A);
    printf("Введите матрицу B:\n");
    inputMatrix(n, B);
    printf("Введите матрицу С:\n");
    inputMatrix(n, C);
    printf("Введите вектор х:\n");
    inputVektor(n, x);
    printf("Введите вектор у:\n");
    inputVektor(n, y);

    umn(n, A, x, k1);
    umn(n, C, x, k2);
    umn(n, B, y, k3);

    a = scal(k1,k3,n);
    b = scal(k2,y,n);
    c = scal(x,k3,n);

    float l = b/c;
    printf("%f", a+l);
}
