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
ProError UserDimensionsByAxisDirectionShow();
ProError UserDimensionsByDirectionShow(ProSolid solid,
    ProFeature* feature,
    ProVector vector);

ProError UserDimensionShow(ProDimension* dim,
    ProError error_status,
    ProAppData appdata);
ProError UserDimensionFilterByVector(ProDimension* dim,
    ProAppData appdata);