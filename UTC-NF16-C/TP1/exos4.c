#include<stdio.h>

void permute(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void pointersA()
{
    char a = 'k', b = 't';
    permute(&a, &b);
    printf("a=%c b=%c", a, b);

    int i = 5;
    int* j = &i;

    printf("\n\n%d >> addresse %d (%d)", i, j, *j);

    *j += 1;
    printf("\n\n%d >> addresse %d (%d)", i, j, *j);

    i *= 5;
    printf("\n\n%d >> addresse %d (%d)", i, j, *j);

    j++;
    printf("\n\n%d >> addresse %d (%d)", i, j, *j);
}

void tabfunc()
{
    int tab[3][4];

    tab[0][0] = 0;
    int* jj = tab;
    int* max = jj + 12;
    printf("%d %d \n=====", jj, max);
    while (jj < max)
    {
        *jj = 2;
        jj++;
        printf("\n\n%d, %d", tab[0][6], tab[1][2]);
    }
}

int main()
{
    int tab[3][4];
    tab[0][0] = 0;
    for (int* kk = &tab[0][0]; kk <= kk+3; kk++) {*kk = 0;}

    for (int ii=0; ii<3; ii++) {printf("\n TEST");}

    tab[0][0] = 0;
    int* jj = &tab[0][0];
    *jj = 2;
    jj++;
    *jj = 1;
    printf("\n\n%d, %d, %d, %d", tab[0][1], jj, jj+3, jj+5 < jj+3);


    

    return 0;
}