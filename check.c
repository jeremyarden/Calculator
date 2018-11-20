#include "check.h"
#include <stdio.h>
boolean IsOp(char op)
{
    /* Kamus */
    
    /* Algoritma */
    return (op=='+' || op=='/' || op=='*');
}

boolean IsMin(char op)
{
    /* Kamus */
    
    /* Algoritma */
    return (op=='-');
}

boolean IsPangkat(char op)
{
    /* Kamus */
    
    /* Algoritma */
    return (op=='^');
}

boolean IsKurungAwal(char op)
{
    /* Kamus */
    
    /* Algoritma */
    return (op=='(');
}

boolean IsKurungAkhir(char op)
{
    /* Kamus */
    
    /* Algoritma */
    return (op==')');
}

boolean IsAngka(char num)
{
    /* Kamus */
    
    /* Algoritma */
    return (!(IsOp(num)) && !(IsMin(num)) && !(IsPangkat(num)) && !(IsKurungAwal(num)) && !(IsKurungAkhir(num)));
}

void CekSyntax(Kata Kalk, boolean *sError)
{
    /* Kamus */
    int i;
    
    /* Algoritma */
    i=1;
    *sError=false;
    while (i<=Kalk.Length && !(*sError)) {

        if ((IsOp(Kalk.TabKata[i]) && IsOp(Kalk.TabKata[i+1])) || (IsOp(Kalk.TabKata[i]) && IsPangkat(Kalk.TabKata[i+1])) || (IsOp(Kalk.TabKata[i]) && IsKurungAkhir(Kalk.TabKata[i+1])) || (IsOp(Kalk.TabKata[i]) && IsMin(Kalk.TabKata[i+1]))) {
            *sError=true;
        }
        else if ((IsPangkat(Kalk.TabKata[i]) && IsOp(Kalk.TabKata[i+1])) || (IsPangkat(Kalk.TabKata[i]) && IsPangkat(Kalk.TabKata[i+1])) || (IsPangkat(Kalk.TabKata[i]) && IsKurungAkhir(Kalk.TabKata[i+1])) || (IsPangkat(Kalk.TabKata[i]) && IsMin(Kalk.TabKata[i+1]))) {
            *sError=true;
        }
        else if ((IsKurungAwal(Kalk.TabKata[i]) && IsKurungAkhir(Kalk.TabKata[i+1])) || (IsKurungAwal(Kalk.TabKata[i]) && IsOp(Kalk.TabKata[i+1]))) {
            *sError=true;
        }
        else if (IsKurungAkhir(Kalk.TabKata[i]) && IsKurungAwal(Kalk.TabKata[i+1])) {
            *sError=true;
        }
        else if ((IsMin(Kalk.TabKata[i]) && IsOp(Kalk.TabKata[i+1])) || (IsMin(Kalk.TabKata[i]) && IsMin(Kalk.TabKata[i+1])) || (IsMin(Kalk.TabKata[i]) && IsPangkat(Kalk.TabKata[i+1])) || (IsMin(Kalk.TabKata[i]) && IsKurungAkhir(Kalk.TabKata[i+1]))) {
            *sError=true;
        }
        else {
            *sError=false;
            i++;
        }
    }
}

void CekMathChar(Kata Kalk, boolean *mError)
{
    /* Kamus */
    int i;
    
    /* Algoritma */
    i=1;
    *mError=false;
    while (i<=Kalk.Length && !(*mError)) {

        if (Kalk.TabKata[i]=='/' && Kalk.TabKata[i+1]=='0') {
            *mError=true;
        }
        else if (IsPangkat(Kalk.TabKata[i])) {
            if (IsKurungAkhir(Kalk.TabKata[i-1])) {
                if (IsAngka(Kalk.TabKata[i-2]) && IsMin(Kalk.TabKata[i-3])) {
                    *mError=true;
                }
                else {
                    *mError=false;
                    i++;
                }
            }
            else if (IsAngka(Kalk.TabKata[i-1]) && IsMin(Kalk.TabKata[i-2])) {
                *mError=true;
            }
            else {
                *mError=false;
                i++;
            }
        } else
        {
            *mError=false;
            i++;
        }
        
    }
}
