#include<stdio.h>
#include<stdbool.h>

int fac(int n)
{
    if (n <= 0)
    {
        return 1;
    }
    return n * fac(n - 1);
}

void main()
{
    int number = 0;
    do
    {
        printf("================\nInput for Factorial f\n(0 shuts down the who thing)\n> ");
        scanf("%d", &number);
        int result = fac(number);
        printf("\nResult is %d\n\n", result);
    } while (number > 0); 
}