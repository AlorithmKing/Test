#pragma once
/*---------------------- Pro/Toolkit Includes ------------------------*/

#include"ProHeader.h"
/*---------------------- Application Includes ------------------------*/
#include <math.h>
#include "user_tk_error.h"
void UserMatrixPrint(FILE* f, char* s, ProMatrix m);
void UserMatrixNormalize(ProMatrix m);
FILE* PTApplsUnicodeFopen(const char* filename, const char* mode);
ProError UserViews();
