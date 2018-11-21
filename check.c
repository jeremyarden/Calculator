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
    return (num=='0' || num=='1' || num=='2' || num=='3' || num=='4' || num=='5' || num=='6' || num =='7' || num=='8' || num=='9');
}

boolean IsTitik(char op)
{
    /* Kamus */

    /* Algoritma */
    return (op=='.');
}

void CekSyntax(Kata Kalk, boolean *sError)
{
    /* Kamus */
    int i;
    int counttitik,countbuka,counttutup;

    /* Algoritma */
    i=1;
    counttitik=0; countbuka=0; counttutup=0;
    *sError=false;
    if (Kalk.Length<1) {
        *sError=true;
    }
    if (Kalk.Length==1) {
        if (IsAngka(Kalk.TabKata[Kalk.Length])) {
            i++;
        }
        else {
            *sError=true;
        }
    }
    if (!(IsAngka(Kalk.TabKata[1]) && IsKurungAwal(Kalk.TabKata[1]))) {
        *sError=true;
    }
    else {
        while (i<=Kalk.Length && !(*sError)) {
            if (IsKurungAwal(Kalk.TabKata[i]) && (IsAngka(Kalk.TabKata[i+1]) || IsMin(Kalk.TabKata[i+1]))) {
                i++;
                countbuka++;
            }
            else if (IsAngka(Kalk.TabKata[i]) && (IsKurungAkhir(Kalk.TabKata[i+1]) || IsOp(Kalk.TabKata[i+1]) || IsAngka(Kalk.TabKata[i+1]) || IsMin(Kalk.TabKata[i+1]) || IsPangkat(Kalk.TabKata[i+1]) || IsTitik(Kalk.TabKata[i+1]))) {
                i++;
            }
            else if (IsPangkat(Kalk.TabKata[i]) && (IsKurungAwal(Kalk.TabKata[i+1]) || IsAngka(Kalk.TabKata[i+1]))) {
                i++;
            }
            else if (IsOp(Kalk.TabKata[i]) && (IsKurungAwal(Kalk.TabKata[i+1]) || IsAngka(Kalk.TabKata[i+1]))) {
                i++;
            }
            else if (IsMin(Kalk.TabKata[i]) && (IsKurungAwal(Kalk.TabKata[i+1]) || IsAngka(Kalk.TabKata[i+1]))) {
                i++;
            }
            else if (IsKurungAkhir(Kalk.TabKata[i]) && (IsOp(Kalk.TabKata[i+1]) || IsMin(Kalk.TabKata[i+1]) || IsPangkat(Kalk.TabKata[i+1])) || IsKurungAkhir(Kalk.TabKata[i+1])) {
                i++;
                counttutup++;
            }
            else if (IsTitik(Kalk.TabKata[i])) {
                counttitik++;
                if (counttitik>1) {
                    *sError=true;
                }
                else if (IsAngka(Kalk.TabKata[i+1])) {
                    i++;
                }
                else {
                    *sError=true;
                }
            }
            else if (i==Kalk.Length) {
                if (IsAngka(Kalk.TabKata[Kalk.Length])) {
                    i++;
                }
                else if (IsKurungAkhir(Kalk.TabKata[Kalk.Length])) {
                    i++;
                    counttutup++;
                    if (countbuka!=counttutup) {
                        *sError=true;
                    }
                }
                else {
                    *sError=true;
                }
            }
            else {
                *sError=true;
            }
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
                if (IsAngka(Kalk.TabKata[i-2]) && IsMin(Kalk.TabKata[i-3]) && Kalk.TabKata[i+1]%2!=0) {
                    *mError=true;
                }
                else {
                    *mError=false;
                    i++;
                }
            }
            else {
                *mError=false;
                i++;
            }
        }
        else if (Kalk.TabKata[i]=='0' && IsPangkat(Kalk.TabKata[i+1]) && Kalk.TabKata[i+2]=='0') {
            *mError=true;
        }
        else {
            *mError=false;
            i++;
        }

    }
}
