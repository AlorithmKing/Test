#pragma once
/*------------------------------------------------------------------*\
Pro/Toolkit includes
\*------------------------------------------------------------------*/
#include <ProToolkit.h>
#include <ProObjects.h>
#include <ProFeature.h>
#include <ProDimension.h>
#include <ProAxis.h>
#include <ProUtil.h>
#include <ProSolid.h>
#include <ProMessage.h>
#include <ProAnnotation.h>
/*------------------------------------------------------------------*\
Application includes
\*------------------------------------------------------------------*/
#include <TestError.h>
#include "MYFMath.h"
using namespace MYF;
ProError UserDimensionsBySelectShow();
ProError UserDimensionsByDirectionShow(ProSolid solid,
    ProFeature* feature);

ProError UserDimensionShow(ProDimension* dim,
    ProError error_status,
    ProAppData appdata);
void MeasureTest();
void DimensionTest();
void UserMatrixPrint(FILE* f,char* s,ProMatrix m);


//void TestAsm();