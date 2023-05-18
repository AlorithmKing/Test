#pragma once

/*---------------------- Pro/Toolkit Includes ------------------------*/
#include <ProToolkit.h>
#include <ProGraphic.h>
#include <ProView.h>
#include <ProColor.h>
#include <ProUtil.h>
#include <ProMessage.h>
/*---------------------- Application Includes ------------------------*/
#include <TestError.h>
/*---------------------- Function Prototypes -------------------------*/
ProError UserAdjustHalftone(char* dummy, int lighter);
ProError UserDrawYellow();
//ProError UserDrawWithDatumPlaneColor();
ProError UserDrawWithDatumAxisColor();
ProError UserDrawDefaults();

