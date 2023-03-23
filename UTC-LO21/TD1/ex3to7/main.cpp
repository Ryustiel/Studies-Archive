#include "exercices.cpp"
#include <stdio.h>
#include <iostream>
#include <string>

int main() 
{
    const double x = 3.14;
    printf("x : %f", x);

    double y;
    printf("\ny undefined : %f", y);

    y = 3.14;
    printf("\ny defined : %f", y);
    
    return 0;
}