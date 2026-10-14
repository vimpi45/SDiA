#include <stdio.h>
#include <cmath>

int main(){
    float a,x,y,t,eps,k, b;
    int i,n;
    printf("input a, x, n, eps \n");
    scanf_s("%f %f %d %f", &a, &x, &n, &eps);
    float d1 = 1.0/n;
    y = a;
    t = 0;
    if(n>1){
        do{
            b = y;
            i = 1;
            k = y;
            while(i<(n-1)){
                k = k*b;
                i++;
            }
            float d2sV = x/k;
            y = b + d1*(d2sV - b);
            t = fabs(y*y - b*b);

        }while(t > eps);
    }else y = x;
    
    printf("%lf", y);
 
}





