#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define IDEN 256
#define NUMB 257


FILE* PF;         
FILE* padres;     
FILE* out;        
char nch;         
int lex;         
int lval;         


char TNM[1000];   
char* ptn = TNM;  

void get();               
void number();            
void word();              
char* add(char* nm);      


void get() {
    nch = fgetc(PF);
}


void number() {
    lval = 0;
    while (isdigit(nch)) {
        lval = 10 * lval + (nch - '0');
        get();
    }
    lex = NUMB;
}


char* add(char* nm) {
    char* p = TNM;
    while (p < ptn) {
        if (strcmp(p, nm) == 0)
            return p;
        p += strlen(p) + 1;
    }
    strcpy(ptn, nm);
    p = ptn;
    ptn += strlen(ptn) + 1;
    return p;
}


void word() {
    char nm[80];
    char* p = nm;
    while (isalpha(nch) || isdigit(nch)) {
        *p++ = nch;
        get();
    }
    *p = '\0';
    add(nm);
    lex = IDEN;
}

int main() {
    PF = fopen("prog.txt", "r");
    if (!PF) {
        printf("Ôàéë prog.txt íå â³äêðèâñÿ!\n");
        return 1;
    }

    out = fopen("out.txt", "w");
    padres = fopen("adres.txt", "w");

    get();
    while (nch != EOF) {
        while (isspace(nch)) get();

        if (isalpha(nch)) {
            word();
            fprintf(out, "IDEN %d\n", lex);
        }
        else if (isdigit(nch)) {
            number();
            fprintf(out, "NUMB %d\n", lval);
        }
        else {
            fprintf(out, "'%c'\n", nch);
            get();
        }
    }

    fclose(PF);
    fclose(out);
    fclose(padres);

    return 0;
}
