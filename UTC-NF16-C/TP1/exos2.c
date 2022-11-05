#include<stdio.h>

void template()
{
    printf("1.1 ===========");


}

int twoone()
{
    printf("2.1 ===========");

    printf("Saisir un caractere\n> ");
    char chr = getchar();

    if ('0' <= chr && chr <= '9')
    {
        printf("\n...est un chiffre");
        return 0;
    }
    if ('a' <= chr && chr <= 'z')
    {
        printf("\n... est un caractere minuscule");
        return 0;
    }
    if ('A' <= chr && chr <= 'Z')
    {
        printf("\n...est caps");
        return 0;
    }
    printf("\n...n'est rien d'interessant");
    return 0;
}

void twotwo()
{
    printf("2.2 ===========");

    int saisie = 0;
    while (saisie > -1)
    {
        printf("%d\n", saisie);
        printf("saisissez un nombre\n> ");
        scanf("%d", &saisie);
    }
}

void twothree()
{
    printf("2.3 ===========");

    char table = 'z';
    while (table != '0')
    {
        printf("Quelle table de multiplication voule-vous? Tapez 0 (zero) pour sortir.\n\n> ");
        char contents[3] = "z";
        scanf("%s", &contents);
        table = contents[0];
        printf("TABLE %d < %d < %d -- %c\n", '1', table, '9', table);
        if (table == '0') {break;}
        if ('1' <= table && table <= '9')
        {
            printf("tous les produits d'entrees de 1 a 9 avec %c...\n\n", table);
            //int tablearray[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            int mdigit = table - '0';
            for (int i=0; i<=9; i++)
            {
                printf("%d x %d = %d\n", mdigit, i+1, (i+1)*mdigit);
                //tablearray[i] = (i+1) * mdigit;
            }
        }
        else
        {
            printf("ce n'est pas dans les possibilites du programme, recommencez !\n\n");
        }
    }


}

void twofour()
{
    printf("2.4 ===========");
    printf("CHARACTER REQUIRED\n> ");
    //while (getchar() != '\n');
    int a = getchar(); // output is int
    char b = a; // casting to char
    printf("%c\n", b);
}

int lenofarray(int arr[], int arraylen)
{
    printf("LEN ARRAY ===========");
    int len = 0;
    printf("\n%d %d %d SIZES\n", arr[2], sizeof(arr), arraylen);
    len = sizeof(arr) / sizeof(int);
    return len;
}

int powr(int a, int b)
{
    if (b == 0) {return 1;}
    int result = a;
    for (int i = 0; i < b-1; i++) {result = result * a;}
    return result;
}

int strtoint(char string[])
{
    printf("STR2INT ===========");
    int result = 0;
    int i = 0;
    while(string[i] != '\0') {
        result += (string[i] - '0') * powr(10, i);
        i++;
    }
    return result;
}

int main()
{
    printf("TESTSTRING ===========");

    //twothree();
    twofour();

    //int arr[5] = {1, 2, 3, 4, 5};
    //printf("SIZEOF %d\n", lenofarray(arr, sizeof(arr))); // SIZE OF PASSED ARRAY IS ALWAYS A POINTER SIZE 
    printf("%d %d\n", powr(3, 3), powr(2, 6));
    printf("%d\n", strtoint("2552")+23);

    return 0;
}