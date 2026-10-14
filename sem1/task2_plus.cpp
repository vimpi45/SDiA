#include <stdio.h>
#include <cmath>
int main()
{
    float x; 
    float y = 0; 
    printf("input x: "); 
    scanf_s("%f", &x); 
    if(x > 0)
        if (x>2) y = sqrt(x);  
        else y = (x * x);    
    else y = 0;
    printf_s("%f", y);
}
