#include <stdio.h>
#include <math.h>
#include "mesinkata.h"
#include "stackt.h"
#include "check.h"

#define Karakter(i) CKata.TabKata[i]

double CharToFloat(Kata K);
boolean IsNumber(char C);
int i;

int main(int argc, const char * argv[]) {
    /*Kamus*/
    Stack S;
    boolean Minus, Kali, Bagi,SynErr,MathErr;
    double num,num2,sum;
    /*Algoritma*/
    CreateEmpty(&S);
    InputUser();
    i = 1;
    //Asumsi Sudah di cek dan inputtan benar
    CekSyntax(CKata, &SynErr);
    CekMathChar(CKata, &MathErr);
    if(!SynErr && !MathErr)
    {
        do{
            
            Minus = Karakter(i) == '-';
            Kali = Karakter(i) == '*';
            Bagi = Karakter(i) == '/';
            
            if(Karakter(i) == '+')
            {
                i++;
                num = CharToFloat(CKata);
                Push(&S, num);
            } else if (Minus)
            {
                Minus = false;
                i++;
                num = CharToFloat(CKata) * -1;
                Push(&S, num);
            } else if (Kali)
            {
                Kali = false;
                i++;
                num = CharToFloat(CKata);
                Pop(&S, &num2);
                num *= num2;
                Push(&S, num);
            }else if (Bagi)
            {
                Bagi = false;
                i++;
                num = CharToFloat(CKata);
                Pop(&S, &num2);
                num = num2/num;
                Push(&S, num);
            } else if(IsNumber(Karakter(i)))
            {
                num = CharToFloat(CKata);

                Push(&S, num);
            } else
            {
                i++;
            }
        }while(!(IsEmpty(S)) && i<=CKata.Length);
        sum = 0;

        while (!(IsEmpty(S))) {
            Pop(&S, &num2);

            sum += num2;
        }
        printf("%.2f\n",sum);
    }
    else if(SynErr)
    {
        printf("SYNTAX ERROR\n");
    } else
    {
        printf("MATH ERROR\n");
    }
}

double CharToFloat(Kata K)
{
    boolean Titik;
    double currNum,num;
    int count;
    num = 0;
    count = 0;
    Titik = false;
    
    
    while (IsNumber(K.TabKata[i]) || K.TabKata[i] == '.')
    {
        
        currNum = (double) ((int)K.TabKata[i] - (int) '0');
        if(K.TabKata[i] == '.' || Titik)
        {
            if(K.TabKata[i] != '.')
            {
                count++;
                num = num*10 + currNum;
            } else
            {
                Titik = true;
            }
        } else
        {
            num = num*10 + currNum;
        }
        
        i++;
    }
    num = num * pow(10, -count);
    return num;
}



boolean IsNumber(char C)
{
    return (int)C>=(int)'0' && C<='9';
}
