#include<stdio.h>

#define STRSIZE 60

// void my_function(int list[]);
// condition?1:2

int find(int* pos, char query[], char string[])
{  
    int len=0;
    for (int i=0; query[i] != '\0'; i++) {len += 1;}

    if (len > 0) {
        char found;
        for (int i=0; string[i] != '\0'; i++) {
            found = 1;
            for (int j=0; j < len; j++) {
                if (query[j] != string[j+i]) {
                    found = 0;
                    break;
                }
            }
            if (found == 1) {
                *pos = i;
                break;
            }
        }
    }
    return len;
}

int findt(int pos[], char query[], char string[])
{  
    int count=0;
    int* topos = pos;

    if (query[0] != '\0') {
        char found;
        for (int i=0; string[i] != '\0'; i++) {
            found = 1;
            for (int j=0; query[j] != '\0'; j++) {
                if (query[j] != string[j+i]) {
                    found = 0;
                    break;
                }
            }
            if (found == 1) {
                *topos = i;
                topos++;
                count++;
            }
        }
    }
    return count;
}

void allcaps(char* string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if ('a' <= string[i] && string[i] <= 'z') {
            string[i] = string[i] - 'a' + 'A';
        }
    }        
}

void testingbasics()
{
    int pos[20];
    int count = findt(pos, "blah", "testiiblahblouhblah");
    for (int* j=pos, max=pos+count; j<max; j++)
    {printf("\n%d %d", *j, count);}

    printf("%d, %d", 'a', 'A');
    char str[] = "surPRIse3";
    printf("\n%s", str);
    allcaps(&str);
    printf("\n%s", str);
}

int jeutruc()
{
    char result[] = "                   "; // getting the final word
    printf("Entrez un mot : ");
    scanf(" %s", &result); // bonjour

    int len = 0;
    while (result[len] != '\0') {len++;}

    char display[len+1];
    for (int i = 0; i < len; i++) {display[i] = '*';} // for (int *j, top=j+len; j<top; j++) {*j = '*';}
    display[len] = '\0';

    int coups = 10;
    int pos[len];
    for (int* j=pos, top=j+len; j<top; j++) {*j = 0;}
    int count = 0;
    int wordcomplete;
    char selected[2] = {'0', '\0'};
    do {
        printf("\ncaractere ? ");
        scanf(" %c", &selected);
        //printf("\nselected : %s, finding in %s", selected, result); 
        count = findt(&pos, selected, result);
        //printf("\nfound %d and posses are %d %d %d %d", count, pos[0], pos[1], pos[2], pos[3]);
        for (int* j=pos, top=pos+count; j<top; j++) {display[*j] = selected[0];}
        printf("%s", display);

        // victory conditions
        wordcomplete=1;
        for (int k=0; k<len; k++) {if (display[k] == '*') {wordcomplete=0; break;}} 
        if (wordcomplete) {printf("\n\nVOUS AVEZ GAGNE"); return 1;}

        coups--;
    } while (coups > 0);
    printf("VOUS AVEZ PERDU");
    return 0;
}

void test() {
    char result[STRSIZE];
    printf("Entrez un mot : ");
    scanf(" %s", &result); // bonjour

    int len = 0;
    while (result[len] != '\0') {len++;}

    char list[len+1];
    for (int i = 0; i < len; i++) {list[i] = '*';}
    list[len] = '\0';
    printf("%s", list);
}

int main()
{
    jeutruc();

    

    return 0;
}