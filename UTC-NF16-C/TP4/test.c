#include<stdio.h>

int test(char* s) {
    int i = 0;
    while (s[i] != '\0') {
        printf( "%d", (int)(s[i] - '0') );
        i++;
    }
    return 0;
}

int main() {
    test("13456");
    return 0;
}