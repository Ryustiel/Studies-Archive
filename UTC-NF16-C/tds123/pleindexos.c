#include<stdio.h>
// c = getchar();
// while(getchar() != "\n");

void fetch(char query[], char result[])
{
    printf("%s", query);
    printf("\n> ");
    scanf("%s", result);

    for (int i=0; i < sizeof(query); i++) {printf("%c", query[i]);}
    //for (int i=0; i < sizeof(result); i++) {printf("%c", result[i]);}
}

int sum(int matrixA[3][3], int matrixB[3][3], int *output)
{
    int result[3][3];
    for (int i=0; i < 2; i++)
    {
        for (int j=0; j < 3; j++)
        {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
            printf("\n%d -- %d", matrixA[i][j], result[i][j]);
        }
    }
    output = result;
    return 0;
    
}

int main()
{
    //char test[11];
    //fetch("number", test);
    //printf(test);
    
    int matrixA[][3] = {
        {0, 1, 2},
        {3, 4, 5}
    };
    int matrixB[][3] = {
        {0, 1, 2},
        {3, 4, 5}
    };

    int result[3][3];
    sum(matrixA, matrixB, &result);
    for (int i=0; i<3; i++)
    {
        printf("\n%d", result[0][i]);
    }
    
    return 0;
}

