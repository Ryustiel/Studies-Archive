#include<stdio.h>

void dekalator(int Nb, int* list[Nb])
{
    int temp = list[Nb-1];
    for (int i = Nb; i > 0; i--) {list[i] = list[i-1];}
    list[0] = temp;
}

int main()
{
    int num=0;
    int tab[12];
    for (int* cell=tab, max=tab+(sizeof(tab)/sizeof(int)); cell < max; cell++) 
    {*cell = num; num++;}

    dekalator(12, tab);
    for (int i = 0; i < 12; i++) {printf("\n%d[%d]", tab[i], i);}

    return 0;
}