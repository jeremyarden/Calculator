#include <stdio.h>
#include "mesinkata.h"
#include "stackt.h"

#define Karakter(i) CKata.TabKata[i]
int main(int argc, const char * argv[]) {
    /*Kamus*/
    Stack S;
    int i;
    boolean Minus, Kali, Bagi;
    /*Algoritma*/
    CreateEmpty(&S);
    InputUser();
    i = 1;
    //Asumsi Sudah di cek dan inputtan benar
    do{
        if(Karakter(i) == '+')
        {
            i++;
        } else if (Karakter(i) == '-')
        {
            i++;
            
        }
    }while(!(IsEmpty(S)) && i<CKata.Length);
}
