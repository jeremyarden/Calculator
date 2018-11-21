#include <stdio.h>
#include <math.h>
#include "mesinkata.h"
#include "stackt.h"
#include "check.h"

#define Karakter(i) CKata.TabKata[i]

double CharToFloat(Kata K);
/*Mengubah kumpulan karakter menjadi float */
boolean IsNumber(char C);
/*Memeriksa jika karakter adalah sebuah nomor atau bukan*/
void Operate(Kata K,char C,int *idx,Stack *S,boolean *mError);
/*Mengoperasikan bilangan-bilangan di taruh dalam stack*/
void Brackets(Kata K,int *idx,Stack *S,boolean *mError);
/*Operasi dalam kurung*/
void Pangkat(Kata K, int *idx, boolean *mError, infotype *Xout);
int i;

int main(int argc, const char * argv[]) {
    /*Kamus*/
    Stack S;
    boolean SynErr,MathErr;
    double num2,sum;
    infotype ngr;
    /*Algoritma*/
    CreateEmpty(&S);
    InputUser();
    //Asumsi Sudah di cek dan inputtan benar
    CekSyntax(CKata, &SynErr);
    CekMathChar(CKata, &MathErr);
    if(!SynErr && !MathErr)
    {
        
        //printf("before:\n");
        i = 1;
        while (i<=CKata.Length)
        {
            //printf("C = %c, idx = %d\n",Karakter(i),i);
            Operate(CKata, Karakter(i), &i, &S, &MathErr);
            //printf("%d ",Top(S));
            //printf("%.2f\n",InfoTop(S).val);
        }
        //printf("%d\n",Top(S));
        sum = 0;
        //printf("after:\n");
        while (!(IsEmpty(S))) {
            //printf("%.2f\n",InfoTop(S).val);
            Pop(&S, &ngr);
            if(ngr.opr == 'N')
            {
                num2 = ngr.val;
                sum += num2;
            }
        }
        printf("Result: %.2f\n",sum);
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
    infotype ngr,Xout;
    Minus = C == '-';
    Kali = C == '*';
    Bagi = C == '/';
    
    if(C == '+')
    {
        *idx+=1;
        //printf("masuk");
        num = CharToFloat(K);
        ngr.opr = 'N';
        ngr.val = num;
        Push(S, ngr);
    }
    else if (Minus)
    {
        Minus = false;
        *idx+=1;
        if(K.TabKata[*idx] == '(')
        {
            ngr.opr = K.TabKata[*idx];
            ngr.val = -999;
            Push(S, ngr);
            Brackets(K, idx, S, mError);
            //printf("%.2f\n",InfoTop(*S).val);
            Pop(S, &ngr);
            //printf("%f",ngr.val);
            num = -1*ngr.val;
            ngr.val = num;
            ngr.opr = 'N';
            
            Push(S, ngr);
        }
        else
        {
            num = CharToFloat(K) * -1;
            ngr.opr = 'N';
            ngr.val = num;
            Push(S, ngr);
        }
    }else if (C == '(')
    {
        ngr.opr = K.TabKata[*idx];
        ngr.val = -999;
        Push(S, ngr);
        Brackets(K, idx, S, mError);
    }
    else if (C == '^')
    {
        Pop(S, &Xout);
        Pangkat(K, idx, mError, &Xout);
        Push(S, Xout);
    }
    else if (Kali)
    {
        Kali = false;
        *idx+=1;
        if(K.TabKata[*idx] == '(')
        {
            ngr.opr = K.TabKata[*idx];
            ngr.val = -999;
            Push(S, ngr);
            Brackets(K, idx, S, mError);
            //printf("%f",InfoTop(*S).val);
            Pop(S, &ngr);
            num = ngr.val;
            Pop(S, &ngr);
            num2 = ngr.val;
            num *= num2;
            ngr.opr = 'N';
            ngr.val = num;
            Push(S, ngr);
        }
        else
        {
            num = CharToFloat(K);
            Pop(S, &ngr);
            num2 = ngr.val;
            num *= num2;
            ngr.opr = 'N';
            ngr.val = num;
            Push(S, ngr);
        }
    }
    else if (Bagi)
    {
        Bagi = false;
        *idx+=1;
        if(K.TabKata[*idx] == '(')
        {
            ngr.opr = K.TabKata[*idx];
            ngr.val = -999;
            Push(S, ngr);
            Brackets(K, idx, S, mError);
            Pop(S, &ngr);
            num = ngr.val;      // setelah tanda bagi
            Pop(S, &ngr);
            num2 = ngr.val;
            num = num2/num;
            ngr.opr = 'N';
            ngr.val = num;
            Push(S, ngr);
        }
        else
        {
            num = CharToFloat(K);
            Pop(S, &ngr);
            num2 = ngr.val;
            num = num2/num;
            ngr.opr = 'N';
            ngr.val = num;
            Push(S, ngr);
        }
    }
    else if(IsNumber(C))
    {
        num = CharToFloat(K);
        ngr.val = num;
        ngr.opr = 'N';
        Push(S, ngr);
    }
    else
    {
        *idx+=1;
    }
}
void Brackets(Kata K,int *idx,Stack *S,boolean *mError)
{
    double sum = 0;
    infotype ngr, X;
    char C;
    *idx+=1;
    C = K.TabKata[*idx];
    while (C != ')' && *idx<=K.Length) {
        Operate(K, C, idx, S, mError);
        C = K.TabKata[*idx];
    }
    if (C == ')')
    {
       // printf("masuk");
        Pop(S, &ngr);
        while (ngr.opr != '(')
        {
            sum += ngr.val;
            Pop(S, &ngr);
        }
        X.val = sum;
        X.opr = 'N';
        Push(S, X);
    }
}
void Pangkat(Kata K, int *idx, boolean *mError, infotype *Xout)
{
    Stack S;
    infotype X, X1;
    
    CreateEmpty(&S);
    *idx -= 1;
    X.val = 0;
    X.opr = '(';
    Push(&S, X);
    while (*idx <= K.Length && K.TabKata[*idx] != ')')
    {
        if (Karakter(*idx) == '^')
        {
            *idx+=1;
        }
        else
        {
            if (Karakter(*idx) == '(')
            {
                Push(&S, X);
                Brackets(K, idx, &S, mError);
            }
            else
            {
                Operate(K, K.TabKata[*idx], idx, &S, mError);
            }
            *idx+=1;
        }
    }
    Pop(&S, &X);
    Pop(&S, &X1);
    while (X1.opr != '(')
    {
        X.val = pow(X1.val,X.val);
        Push(&S, X);
        Pop(&S, &X);
        Pop(&S, &X1);
    }
    
    *Xout = X;
}
boolean IsNumber(char C)
{
    return (int)C>=(int)'0' && (int)C<=(int)'9';
}
