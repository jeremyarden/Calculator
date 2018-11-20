/* File: mesinkata.c */
/* Definisi Mesin Kata: Model Akuisisi Versi I */
#include "boolean.h"
#include <stdio.h>
#include "mesinkata.h"
boolean EndKata;
Kata CKata;
boolean EOP;

void InputUser()
/* Mengakuisisi Inputtan user kedalam CKata */
{
    /*Kamus*/
    char c;
    int i;
    /*Algoritma*/
    i = 1;
    do{
        scanf("%c",&c);
        CKata.TabKata[i] = c;
        i++;
    }while( c != '\n' && i<NMax);
    CKata.Length = i-2;
}
