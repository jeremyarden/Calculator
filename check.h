//
//  check.h
//  Kalkulator
//
//  Created by Abiyyu Ismunandar on 11/19/18.
//  Copyright © 2018 Abiyyu Ismunandar. All rights reserved.
//

#ifndef check_h
#define check_h

#include "boolean.h"
#include "mesinkata.h"
#include <stdio.h>
#include "stackt.h"

boolean IsOp(char op);
/* Mengecek apakah karakter tersebut berupa operator +, *, / */

boolean IsMin(char op);
/* Mengecek apakah karakter tersebut berupa operator - */

boolean IsPangkat(char op);
/* Mengecek apakah karakter tersebut berupa operator ^ */

boolean IsKurungAwal(char op);
/* Mengecek apakah karakter tersebut berupa operator ( */

boolean IsKurungAkhir(char op);
/* Mengecek apakah karakter tersebut berupa operator ) */

boolean IsTitik(char op);

boolean IsAngka(char num);
/* Mengecek apakah karakter tersebut berupa angka */

void CekSyntax(Kata Kalk, boolean *sError);
/* Mengecek kebenaran syntax */

void CekMathChar(Kata Kalk, boolean *mError);
/* Mengecek operasi yang ada, apakah bisa dihitung atau tidak */

#endif /* check_h */
