#include <stdio.h>
#include <math.h>
#include "mesinkata.h"
#include "stackt.h"
#include "check.h"

#define Karakter(i) CKata.TabKata[i]

double CharToFloat(Kata K);
boolean IsNumber(char C);
void Operate(Kata K,char C,int *idx,Stack *S,boolean *mError);
int i;

int main(int argc, const char * argv[]) {
    /*Kamus*/
    Stack S;
    boolean SynErr,MathErr;
    double num2,sum;
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
            Operate(CKata,Karakter(i),&i, &S, &MathErr);
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

void Operate(Kata K,char C,int *idx,Stack *S,boolean *mError)
/*Akan mengisi stack dengan double yang nanti dapat di tambahkan*/
{
    boolean Minus,Kali,Bagi;
    double num,num2;
    Minus = C == '-';
    Kali = C == '*';
    Bagi = C == '/';
    
    if(C == '+')
    {
        *idx+=1;
        num = CharToFloat(K);
        Push(S, num);
    } else if (Minus)
    {
        Minus = false;
        *idx+=1;
        num = CharToFloat(K) * -1;
        Push(S, num);
    } else if (Kali)
    {
        Kali = false;
        *idx+=1;
        num = CharToFloat(K);
        Pop(S, &num2);
        num *= num2;
        Push(S, num);
    }else if (Bagi)
    {
        Bagi = false;
        *idx+=1;
        num = CharToFloat(K);
        Pop(S, &num2);
        num = num2/num;
        Push(S, num);
    } else if(IsNumber(Karakter(i)))
    {
        num = CharToFloat(CKata);
        
        Push(S, num);
    } else
    {
        *idx+=1;
    }
}

boolean IsNumber(char C)
{
    return (int)C>=(int)'0' && C<='9';
}
