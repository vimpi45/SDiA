#include <stdio.h>
int main()
{
    unsigned int k; 
    int y = 0; 
    printf("input k: "); 
    scanf_s("%d", &k); 
    if(k%2==0) y=(k/2-1)%10;
    else y = k/20+1;
    printf_s("%d", y);
}
