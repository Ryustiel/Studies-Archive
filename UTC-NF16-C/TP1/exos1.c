#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("TESTSTRING ===========");

    twoone();
    twotwo();
    twothree();
    twofour();

    return 0;
}

void template()
{
    printf("1.1 ===========");


}

int twoone()
{
    printf("2.1 ===========");

    printf("Saisir un caractere\n> ");
    char chr = getchar();

    if ('0' <= chr <= '9')
    {
        printf("\n...est un chiffre");
        return 0;
    }
    if ('a' <= chr <= 'z')
    {
        printf("\n... est un caractere minuscule");
        return 0;
    }
    if ('A' <= chr <= 'Z')
    {
        printf("\n...est caps");
        return 0;
    }
    printf("\n...n'est rien d'interessat");
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

    int table = '-1';
    while (table != '0')
    {
        printf("Quelle table de multiplication voule-vous? Tapez 0 (zero) pour sortir.\n> ");
        scanf("%c", &table);
        if (table == '0')
        {
            break;
        }
        if ('1' < table < '9')
        {
            printf("tous les produits d'entrees de 1 a 9 avec %c...\n", table);
            int tablearray[9];
            int i;
            for (i=0; i<9; i++)
            {
                tablearray[i] = (i+1) * (table - '0');
            }
        }
        else
        {
            printf("ce n'est pas dans les possibilit�s du programme, recommencez !");
        }
    }


}

void twofour()
{
    printf("2.4 ===========");


}


void oneone()
{
    printf("1.1 ===========");

    int a=2, b=3;
    printf("Valeurs : %d | %d");
    printf("\nsomme : %d\n\n", a + b);
}

void onetwo()
{
    printf("1.2 ===========");

    int a, b;
    printf("entrez deux nombres separes par un espace\n> ");
    scanf("%d %d", &a, &b);
    printf("\ndeux trucs but swapped : %d %d\n\n", b, a);
}

void onethree()
{
    printf("1.3 ===========");

    float a, b;
    printf("nombres au format a%%y\n> ");
    scanf("%f%%%f", &a, &b);
    printf("%f %f", a, b);
    float result = (a / 100) * b;
    printf("\ncalcul de pourcentage : %f%%\n\n", result);
}

void onefour(int temperature)
{
    printf("1.4 ===========");

    float result = (5./9) * (temperature - 32.);
    printf("\ntemperature : %f degres celcius\n\n", result);
}

void onefive()
{
    printf("1.5 ===========");

    int a=10;
    printf("decimal : %d\nhex : %x\noctal : %o\n\n", a, a, a);
}

int onesix(int entier)
{
    printf("1.6 ===========");
    printf("entier de reference : %d\n", entier);

    float n = entier;
    if (n / 2 == entier / 2)
    {
        printf("est pair.\n\n");
        return 0;
    }
    printf("est impair.\n\n");
    return 0;
}

int oneseven()
{
    printf("1.7 ===========");

    char test = '5';
    printf("init char : %c (actual value = %d)\n", test, test);
    test = 96;
    printf("same char remapped to 96 : %c\n", test);
}








