#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    
    long int n,sum=1;
    scanf("%ld",&n);
    if (n == 0 || n== 1)
    {
        printf("%ld",sum);
    }
    else if (n>1){
        for (int i = 2; i <= n; i++)
        {
            sum *= i; 
        }
        printf("%ld",sum);
    }
    return 0;
    }
