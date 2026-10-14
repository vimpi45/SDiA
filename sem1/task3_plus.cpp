#include <stdio.h>
// #include <math.h>
int main() {   
    float r;
    int i,j,res=0;
    scanf("%f",&r);
    for(i = 0; i <= r; i++)
    for(j = 1; j <= r; j++)
    if(i*i + j*j <= r*r)res++;
    printf("%d\n",res * 4 + 1);

}

// int main() {   
//     float r;
//     int l,y,res=0;
//     scanf("%f",&r);
//     for(y = 0; y <= r; y++){
//         l = sqrt(r*r - y*y);
//         res += l;
//     }
//     res = 4 * res + 1;
    
    
//     printf("%d\n",res);

// }