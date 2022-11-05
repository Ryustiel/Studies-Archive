#include <stdio.h>

double powa(double x, int n) {
    if (n == 0) return 1;
    return x * powa(x, n - 1);
}

double powb(double x, int n) {
    if (n == 0) return 1;
    else if (n % 2 == 0) return powb(x*x, n/2);
    return (x*powb(x*x, n/2));
}

int main() {

    int i = 20000;

    printf("\n\nblah");

    int val1 = powb(2, i);

    printf("\n\n%d %d %d", val1, val1, val1);

    int val2 = powa(2, i);

    printf("\n\n%d %d %d", val2, val2, val2);
    printf("done");

    return 0;
}