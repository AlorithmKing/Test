#pragma once
#include"Tools/ProHeader.h"
#include"Tools/MatixOperation.h"
ProError TagDatumLabel();
ProError Annotation();
ProBoolean IsDatum(ProSolid solid,ProSurface surface);


void DimensionVisit();
ProError TestAsm();
static ProMatrix Front_View = {
	{1.0000,0.0000,0.0000,0.0000},
	{ 0.0000, 1.0000, 0.0000, 0.0000},
	{ 0.0000, 0.0000, 1.0000, 0.0000},
	{0.0000,0.0000,0.0000,1.0000}
};