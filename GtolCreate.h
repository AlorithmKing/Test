#pragma once
#include"ProHeader.h"
#include"MYFMath.h"
#include"UtilMessage.h"
typedef struct planes_data
{
    ProGeomitem reference;
    ProAnnotationPlane ap;
    ProVector normal;
    double tolerance;
} Planesdata_t;

int UsrPlanePositiontolSet(
    ProSelection surface,
    ProVector pos,
    ProGeomitem* reference,
    ProAnnotationPlane* ap,
    double tolerance);

ProError GtolInitOp(
    ProSurface surface,
    ProError filt_status,
    ProAppData data);

//ProError FilterSurAction(ProSurface p_surface,
    //ProAppData app_data);
int UsrPlanesTol();
