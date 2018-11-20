#include "operation.h"
#include <stdio.h>
#include <math.h>

extern Kata inp;
extern int i;

double SalinAngka()
{
    double num = 0;
    int count

    while ((int)inp.TabKata[i] >= 1 && (int)inp.TabKata[i] <= 9 && i <= inp.Length)
    { 
        num = num*10 + (int)inp.TabKata[i];
        i++;
    }
    if (inp.TabKata[i] == '.')
    {
        i++;
        count = 1;
        while ((int)inp.TabKata[i] >= 1 && (int)inp.TabKata[i] <= 9 && i <= inp.Length)
        {
            num = num + (double)((int)inp.TabKata[j] * pow(10, -count))
            count++;
            i++;
        }
    }  

    return num;
}

double Operation()
{
    double num;


}