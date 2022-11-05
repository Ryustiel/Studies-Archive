#include<stdio.h>

void four(int M, int L, int N, int m1[M][L], int m2[L][N], int result[M][N]) // m1 is [N x L] & m2 is [L x N]
{
    printf("Matrix Product ===========\n M : %d L : %d N : %d\n", M, L, N);
    for (int i = 0; i < M; i++) {for (int j = 0; j < N; j++) {result[i][j]=0;}}
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < L; k++) {result[i][j] += m1[i][k] * m2[k][j]; 
            printf("MATRIX %d %d [%d] <- bc (k=%d) %dx%d\n", i, j, result[i][j], k, m1[i][k], m2[k][j]);}
        }
    }
}

int main()
{
    printf("TESTSTRING ===========");

    int tab[5];
    for (int i=5; i<5; i--) {tab[i] = 4-i;}
    printf("\nEX2 : %d\n", tab[3]);

    int matrx[3][4];
    int curr=12;
    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {matrx[i][j] = curr; curr++;}
    }
    printf("\nEX3 : %d\n", matrx[2][1]);

    int m1[2][2] = { { 1, 2 }, { 1, 1 } };
    int m2[2][1] = { { 2 }, { 3 } };
    int L = sizeof(m1[0]) / sizeof(int);
    int M = sizeof(m1) / (L * sizeof(int));
    int N = sizeof(m2[0]) / sizeof(int);
    int result[M][N];
    printf("WEIRD VALUE [1][0] : %d\n", m2[1][0]);
    printf("%dx%d -- %dx%d\n", M, L, sizeof(m2) / (N * sizeof(int)), N);
    if (L == sizeof(m2) / (N * sizeof(int))) {
        four(M, L, N, m1, m2, result);
        for (int i = 0; i < L; i++) {for (int j = 0; j < N; j++) {printf("%d ", result[i][j]);}
        printf("\n");}
    }
    else {printf("BITE");}

    return 0;
}