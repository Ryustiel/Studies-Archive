#include<stdio.h>

int fact1(int n) {
    if (n <= 0) {n = 1;}
    int i = n-1;
    while (i > 1) {
        n *= i;
        i--;
    }
    return n;
}

int fact2(int n) {
    if (n <= 1) {return 1;}
    return (n * fact2(n - 1));
}

int fib1(int n) {
    int k = 1;
    int kprev = 1;
    int temp;
    for (int i=1; i<n; i++) {
        temp = k;
        k = k + kprev;
        kprev = temp;
    }
    return k;
}

int fib2(int n) {
    if (n <= 1) {return 1;}
    return fib2(n - 1) + fib2(n - 2);
}

int fib3(int n) { // fib rapide
    if (n <= 3) {printf("\nappel avec %d ret %d", n, fib2(n)); return fib2(n);} // pour hn <= 1
    int hn;
    if (n%2 == 0) {
        hn = n/2; 
        printf("\nappel avec %d hn %d", n, hn);
        return (fib3(hn)^2) + (2*fib3(hn)*fib3(hn - 1));
    }
    else {
        hn = (n-1)/2; 
        printf("\nappel avec %d hn %d", n, hn);
        return (fib3(hn)^2) + (fib3(hn + 1)^2);
    }
}

int main()
{
    printf("\n== %d numbers numbers %d et numbers %d ==\n", fib1(5), fib2(5), fib3(5));
    return 0;
}