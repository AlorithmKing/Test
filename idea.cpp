//
///*
//    Copyright (c) 2019 PTC Inc. and/or Its Subsidiary Companies. All Rights Reserved.
//*/
//
//
///*--------------------------------------------------------------------*\
//Pro/TOOLKIT includes
//\*--------------------------------------------------------------------*/
//#include <ProToolkit.h>
//#include <ProDimension.h>
//#include <ProMenu.h>
//#include <ProArray.h>
//#include <ProDrawing.h>
//#include <ProGraphic.h>
//#include <ProModelitem.h>
//#include <ProPoint.h>
//#include <ProAnnotation.h>
//
///*--------------------------------------------------------------------*\
//Application includes
//\*--------------------------------------------------------------------*/
//#include "UtilMenu.h"
//#include "UtilFiles.h"
//#include <UtilMessage.h>
//#include <ProMessage.h>
//#include <UtilTypes.h>
//#include <UtilCollect.h>
//#include <TestDimension.h>
//
///*--------------------------------------------------------------------*\
//Application macros
//\*--------------------------------------------------------------------*/
//
//#define LINEAR_TO_ORDINATE 0
//#define ORDINATE_TO_LINEAR 1
//
//#define DIM_MOD_TEXT        0
//#define DIM_MOD_SYMBOL      1
//#define DIM_MOD_VALUE       2
//#define DIM_MOD_TOL         3
//#define DIM_MOD_TOL_TYPE    4
//#define DIM_MOD_DECIMALS    5
//#define DIM_MOD_DENOM       6
//
//#define DIM_FEATURE         0  
//#define DIM_PART            1
//#define DIM_FEATURE_VIEW    2
//#define DIM_PART_VIEW       3
//#define DIM_VIEW            4
//#define DIM_SELECTED        5
//
///*--------------------------------------------------------------------*\
//Application data types
//\*--------------------------------------------------------------------*/
//
//typedef struct user_dim_data {
//    ProMdl parent;
//    ProBoolean    flag;
//}UserDimData;
//
//int    ProTestDimType(ProDrawing*);
//int    ProTestDimOrdinateCreate(ProDrawing*);
//int    ProTestOrdinateToLinear(ProDrawing*);
//int    ProTestDimMove(ProDrawing*);
//int    ProTestDimensionModify(ProMdl*, int);
//int    ProTestDimensionEdit(ProDimension* dim, int);
//int    ProTestDimensionInfo(ProMdl*, int);
//int    ProTestToleranceSet(ProMdl*, int);
//int    ProTestDimSwitch();
//int    ProTestDimensionReset(ProDimension*);
//int    ProTestDimStandardCreate(ProDrawing*);
//int    ProTestDimDisplayMenu(ProMdl*, int);
//int    ProTestDimDisplayAct(UserDimData*, int);
//
//void   ProTestSenseSet(ProDimSense*);
//void   ProTestDimensionAttachPrint(ProDimAttachment*, ProDimSense*, FILE*);
//void   ProTestDimensionParamPrint(ProDimension, FILE*);
//void   ProTestDimensionInfoPrint(ProMdl, ProDimension, ProMode, ProView, FILE*);
//
//char* ProDimOrientToStr(ProDimOrient);
//char* ProDimAocToStr(ProDimLinAocTgtSense);
//char* ProDimPointToStr(ProPointType);
//char* ProDimTypeToStr(ProDimensiontype);
//
//ProError ProTestSolidDimensionsCollect(ProSolid, ProBoolean, ProDimension**);
//
//
///*============================================================================*\
// Function:	ProTestDimensionMenu
// Purpose:       Shows main level dimension related menu
//\*============================================================================*/
//int ProTestDimensionMenu(ProMdl* p_mdl)
//{
//    int menu_id;
//    ProError err;
//    ProMode mode;
//
//    err = ProModeCurrentGet(&mode);
//
//    err = ProMenuFileRegister((char*)"TkDimension", (char*)"tkdimension.mnu", &menu_id);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"TkDimension",
//        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Create",
//        (ProMenubuttonAction)ProTestDimType, p_mdl, 0);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Move",
//        (ProMenubuttonAction)ProTestDimMove, p_mdl, 0);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"OrdinateToLinear",
//        (ProMenubuttonAction)ProTestOrdinateToLinear, p_mdl, 0);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Info",
//        (ProMenubuttonAction)ProTestDimensionInfo, p_mdl, (int)mode);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Modify",
//        (ProMenubuttonAction)ProTestDimensionModify, p_mdl, (int)mode);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Switch",
//        (ProMenubuttonAction)ProTestDimSwitch, p_mdl, 0);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Show",
//        (ProMenubuttonAction)ProTestDimDisplayMenu, p_mdl, (int)PRO_B_TRUE);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"Erase",
//        (ProMenubuttonAction)ProTestDimDisplayMenu, p_mdl, (int)PRO_B_FALSE);
//    err = ProMenubuttonActionSet((char*)"TkDimension", (char*)"ModifyTolerance",
//        (ProMenubuttonAction)ProTestToleranceSet, p_mdl, (int)PRO_B_FALSE);
//
//
//    if (mode == PRO_MODE_ASSEMBLY || mode == PRO_MODE_PART)
//    {
//        err = ProMenubuttonVisibilitySet((char*)"TkDimension", (char*)"Create", PRO_B_FALSE);
//        err = ProMenubuttonVisibilitySet((char*)"TkDimension", (char*)"OrdinateToLinear",
//            PRO_B_FALSE);
//        err = ProMenubuttonVisibilitySet((char*)"TkDimension", (char*)"Move", PRO_B_FALSE);
//    }
//
//    err = ProMenuCreate(PROMENUTYPE_MAIN, (char*)"TkDimension", &menu_id);
//    err = ProMenuProcess((char*)"TkDimension", &menu_id);
//
//    return (0);
//}
//
///*============================================================================*\
// Function:	ProTestDimType
// Purpose:       Choise dimension type for creating
//\*============================================================================*/
//int  ProTestDimType(ProDrawing* p_drw)
//{
//    int menu_id;
//
//    ProMenuFileRegister((char*)"TkDrawdimtype", (char*)"tkdrawdimtype.mnu", &menu_id);
//    ProMenubuttonActionSet((char*)"TkDrawdimtype", (char*)"Standard",
//        (ProMenubuttonAction)ProTestDimStandardCreate, p_drw, 0);
//    ProMenubuttonActionSet((char*)"TkDrawdimtype", (char*)"Ordinate",
//        (ProMenubuttonAction)ProTestDimOrdinateCreate, p_drw, 0);
//    ProMenubuttonActionSet((char*)"TkDrawdimtype", (char*)"TkDrawdimtype",
//        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
//    ProMenuCreate(PROMENUTYPE_MAIN, (char*)"TkDrawdimtype", &menu_id);
//    ProMenuProcess((char*)"TkDrawdimtype", &menu_id);
//
//    return (0);
//}
//
///*============================================================================*\
// Function:	ProTestDimensionModify
// Purpose:       Setup menu for testing modify dimension functionality
//\*============================================================================*/
//int ProTestDimensionModify(ProMdl* p_mdl, int mode)
//{
//    ProError err;
//    int menu_id, n_sel;
//    ProSelection* sel;
//    ProDimension dim;
//    ProBoolean flag;
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select dimension: ");
//    err = ProSelect((char*)"dimension,ref_dim", 1, NULL, NULL, NULL, NULL,
//        &sel, &n_sel);
//    if ((err != PRO_TK_NO_ERROR) || (n_sel < 1))
//        return -1;
//
//    err = ProSelectionModelitemGet(sel[0], &dim);
//
//    err = ProAnnotationUndisplay((ProAnnotation*)&dim, NULL, NULL);
//
//    err = ProDimensionIsFractional(&dim, &flag);
//    TEST_CALL_REPORT("ProDimensionIsFractional()",
//        "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//    ProMenuFileRegister((char*)"TkDimesionmodif", (char*)"tkdimesionmodif.mnu", &menu_id);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"TkDimesionmodif",
//        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Text",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_TEXT);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Symbol",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_SYMBOL);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Value",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_VALUE);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Tolerance",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_TOL);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Tolerance type",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_TOL_TYPE);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Decimals",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_DECIMALS);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Denominator",
//        (ProMenubuttonAction)ProTestDimensionEdit, &dim, DIM_MOD_DENOM);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Commit",
//        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
//    ProMenubuttonActionSet((char*)"TkDimesionmodif", (char*)"Cancel",
//        (ProMenubuttonAction)ProTestDimensionReset, &dim, 0);
//
//    if (mode == (int)PRO_MODE_DRAWING)
//    {
//        ProMenubuttonVisibilitySet((char*)"TkDimesionmodif", (char*)"Value", PRO_B_FALSE);
//    }
//    ProMenuCreate(PROMENUTYPE_MAIN, (char*)"TkDimesionmodif", &menu_id);
//
//    if (flag)
//        err = ProMenubuttonDeactivate((char*)"TkDimesionmodif", (char*)"Decimals");
//    else
//        err = ProMenubuttonDeactivate((char*)"TkDimesionmodif", (char*)"Denominator");
//    ProMenuProcess((char*)"TkDimesionmodif", &menu_id);
//
//    err = ProAnnotationDisplay((ProAnnotation*)&dim, NULL, NULL, NULL);
//
//    return (0);
//}
//
///*============================================================================*\
// Function:	ProTestDimensionReset
// Purpose:       Resets the dimensions of the object
//\*============================================================================*/
//int ProTestDimensionReset(ProDimension* dim)
//{
//    ProError err;
//
//    err = ProDimensionDimensionReset(dim);
//    TEST_CALL_REPORT("ProDimensionDimensionReset()",
//        "ProTestDimensionReset()", err, err != PRO_TK_NO_ERROR);
//    err = ProMenuDelete();
//
//    return (0);
//}
//
//
//
///*============================================================================*\
// Function:	ProTestDimensionEdit
// Purpose:       Modify the dimension parameters
//\*============================================================================*/
//int ProTestDimensionEdit(ProDimension* dim, int action)
//{
//    ProError err;
//    wchar_t** p_texts = NULL;
//    wchar_t buffer[127];
//    ProName symbol;
//    ProCharLine string, temp;
//    double value = 0.0, low_limit, up_limit, val_range[2] = { 1e-9, 1e+5 };
//    int decimals = 1;
//    int arrIndex = 0, wstrLen = 0, ii = 0;
//    static ProUtilMenuButtons tol_type[] = {
//      {"Tolerance Type", 0, TEST_CALL_PRO_MENU_DELETE},
//      {"Nominal", PRO_TOL_DEFAULT, 0},
//      {"Limits", PRO_TOL_LIMITS, 0},
//      {"Symmetric", PRO_TOL_PLUS_MINUS_SYM, 0},
//      {"Plus/Minus", PRO_TOL_PLUS_MINUS, 0},
//      {"PM_Sym_Superscript", PRO_DIM_TOL_SYM_SUPERSCRIPT, 0},
//      {"",0,0}
//    };
//    ProDimToleranceType type;
//
//
//    switch (action)
//    {
//    case DIM_MOD_TEXT:
//        ProUtilMsgPrint("gen", "TEST %0s", "Enter the dimension text: ");
//        err = ProArrayAlloc(0, sizeof(wchar_t*), 1, (ProArray*)&p_texts);
//        while (1)
//        {
//            err = ProMessageStringRead(127, buffer);
//            if (err != PRO_TK_NO_ERROR)
//                break;
//
//            err = ProArrayObjectAdd((ProArray*)&p_texts, PRO_VALUE_UNUSED, 1, &buffer);
//            err = ProWstringLengthGet(buffer, &wstrLen);
//            err = ProArrayAlloc(wstrLen + 1, sizeof(wchar_t), 1, (ProArray*)&p_texts[arrIndex]);
//            ProWstringCopy(buffer, p_texts[arrIndex], PRO_VALUE_UNUSED);
//            arrIndex++;
//        }
//        err = ProDimensionTextWstringsSet(dim, p_texts);
//        TEST_CALL_REPORT("ProDimensionTextWstringsSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        for (ii = 0; ii < arrIndex; ii++)
//            err = ProArrayFree((ProArray*)&p_texts[ii]);
//
//        err = ProArrayFree((ProArray*)&p_texts);
//
//        break;
//    case DIM_MOD_SYMBOL:
//        err = ProDimensionSymbolGet(dim, symbol);
//        TEST_CALL_REPORT("ProDimensionSymbolGet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//        sprintf(string, "Enter the dimension symbol [%s]: ",
//            ProWstringToString(temp, symbol));
//        ProUtilMsgPrint("gen", "TEST %0s", string);
//        ProUtilStringGet(symbol, symbol, PRO_LINE_SIZE);
//        err = ProDimensionSymbolSet(dim, symbol);
//        TEST_CALL_REPORT("ProDimensionSymbolSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        break;
//    case DIM_MOD_TOL:
//        err = ProDimensionToleranceGet(dim, &up_limit, &low_limit);
//        TEST_CALL_REPORT("ProDimensionToleranceGet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//        sprintf(string, "Enter upper limit [%6.3f]: ", up_limit);
//        ProUtilMsgPrint("gen", "TEST %0s", string);
//        ProUtilDoubleGet(val_range, &up_limit, &up_limit);
//        sprintf(string, "Enter lower limit [%6.3f]: ", low_limit);
//        ProUtilMsgPrint("gen", "TEST %0s", string);
//        ProUtilDoubleGet(val_range, &low_limit, &low_limit);
//        err = ProDimensionToleranceSet(dim, up_limit, low_limit);
//        TEST_CALL_REPORT("ProDimensionToleranceSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        break;
//    case DIM_MOD_VALUE:
//        err = ProDimensionValueGet(dim, &value);
//        TEST_CALL_REPORT("ProDimensionValueGet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//        sprintf(string, "Enter the dimension value [%6.3f]: ", value);
//        ProUtilMsgPrint("gen", "TEST %0s", string);
//        ProUtilDoubleGet(NULL, &value, &value);
//        err = ProDimensionValueSet(dim, value);
//        TEST_CALL_REPORT("ProDimensionValueSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        break;
//    case DIM_MOD_TOL_TYPE:
//        err = ProUtilMenuIntValueSelect(tol_type, (int*)&type);
//
//        err = ProDimensionToltypeSet(dim, type);
//        TEST_CALL_REPORT("ProDimensionToltypeSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        break;
//    case DIM_MOD_DECIMALS:
//        err = ProDimensionDecimalsGet(dim, &decimals);
//        TEST_CALL_REPORT("ProDimensionDecimalsGet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//        sprintf(string, "Enter the dimension decimals [%d:] ", decimals);
//        ProUtilMsgPrint("gen", "TEST %0s", string);
//        ProUtilIntGet(NULL, &decimals, &decimals);
//        err = ProDimensionDecimalsSet(dim, decimals);
//        TEST_CALL_REPORT("ProDimensionDecimalsSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        break;
//    case DIM_MOD_DENOM:
//        err = ProDimensionDenominatorGet(dim, &decimals);
//        TEST_CALL_REPORT("ProDimensionDenominatorGet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//        sprintf(string, "Enter the dimension denominator [%d:] ", decimals);
//        ProUtilIntGet(NULL, &decimals, &decimals);
//        err = ProDimensionDenominatorSet(dim, decimals);
//        TEST_CALL_REPORT("ProDimensionDenominatorSet()",
//            "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//        break;
//    default:
//        break;
//    }
//
//    return (0);
//}
//
///*============================================================================*\
//  Function : ProTestDimSwitch()
//  Purpose  : Switch display mode
//\*============================================================================*/
//int ProTestDimSwitch()
//{
//    ProError err;
//    ProDisplayMode mode;
//
//    err = ProDisplaymodeGet(&mode);
//    TEST_CALL_REPORT("ProDisplaymodeGet()",
//        "ProTestDimSwitch()", err, err != PRO_TK_NO_ERROR);
//    if (mode == PRODISPMODE_NUMERIC)
//        mode = PRODISPMODE_SYMBOLIC;
//    else
//        mode = PRODISPMODE_NUMERIC;
//    err = ProDisplaymodeSet(mode);
//    TEST_CALL_REPORT("ProDisplaymodeSet()",
//        "ProTestDimSwitch()", err, err != PRO_TK_NO_ERROR);
//    return (0);
//}
//
///*============================================================================*\
// Function: ProTestSenseSet
// Purpose:  Coise dimension sense
//\*============================================================================*/
//void ProTestSenseSet(ProDimSense* p_sense)
//{
//    static ProUtilMenuButtons sense_type[] = {
//        {"SenseType", 0, TEST_CALL_PRO_MENU_DELETE},
//        {"Point", PRO_DIM_SNS_TYP_PNT, 0},
//        {"SplinePnt", PRO_DIM_SNS_TYP_SPLN_PNT, 0},
//        {"TgtIdx", PRO_DIM_SNS_TYP_TGT_IDX, 0},
//        {"AocTgt", PRO_DIM_SNS_TYP_LIN_AOC_TGT, 0},
//        {"Angle", PRO_DIM_SNS_TYP_ANGLE, 0},
//        {"PntAngle", PRO_DIM_SNS_TYP_PNT_ANGLE, 0},
//        {"None", PRO_DIM_SNS_TYP_NONE, 0},
//        {"",0,0}
//    };
//    static ProUtilMenuButtons point_type[] = {
//        {"PointType", 0, TEST_CALL_PRO_MENU_DELETE},
//        {"End1", PRO_POINT_TYP_END1, 0},
//        {"End2", PRO_POINT_TYP_END2, 0},
//        {"Center", PRO_POINT_TYP_CENTER, 0},
//        {"MidPnt", PRO_POINT_TYP_MIDPT, 0},
//        {"None", PRO_POINT_TYP_NONE, 0},
//        {"",0,0}
//    };
//    static ProUtilMenuButtons aoc_tgt[] = {
//        {"AocTgtSense", 0, TEST_CALL_PRO_MENU_DELETE},
//        {"Left0", PRO_DIM_LIN_AOC_TGT_LEFT0, 0},
//        {"Right0", PRO_DIM_LIN_AOC_TGT_RIGHT0, 0},
//        {"Left1", PRO_DIM_LIN_AOC_TGT_LEFT1, 0},
//        {"Right1", PRO_DIM_LIN_AOC_TGT_RIGHT1, 0},
//        {"",0,0}
//    };
//    static ProUtilMenuButtons dim_orient[] = {
//        {"DimOrient", 0, TEST_CALL_PRO_MENU_DELETE},
//        {"Horiz", PRO_DIM_ORNT_HORIZ, 0},
//        {"Vert", PRO_DIM_ORNT_VERT, 0},
//        {"Slanted", PRO_DIM_ORNT_SLANTED, 0},
//        {"ElpsRad1", PRO_DIM_ORNT_ELPS_RAD1, 0},
//        {"ElpsRad2", PRO_DIM_ORNT_ELPS_RAD2, 0},
//        {"ArcAng", PRO_DIM_ORNT_ARC_ANG, 0},
//        {"Length", PRO_DIM_ORNT_ARC_LENGTH, 0},
//        {"TancrvAng", PRO_DIM_ORNT_LIN_TANCRV_ANG, 0},
//        {"None", PRO_DIM_ORNT_NONE, 0},
//        {"",0,0}
//    };
//
//    ProUtilMenuIntValueSelect(sense_type, (int*)&p_sense->type);
//    switch (p_sense->type)
//    {
//    case PRO_DIM_SNS_TYP_PNT:
//        ProUtilMenuIntValueSelect(point_type, (int*)&p_sense->sense);
//
//        break;
//    case PRO_DIM_SNS_TYP_TGT_IDX:
//    case PRO_DIM_SNS_TYP_SPLN_PNT:
//        ProUtilMsgPrint("gen", "TEST %0s", "Enter index: ");
//        ProUtilIntGet(NULL, NULL, &p_sense->sense);
//
//        break;
//    case PRO_DIM_SNS_TYP_LIN_AOC_TGT:
//        ProUtilMenuIntValueSelect(aoc_tgt, (int*)&p_sense->sense);
//
//        break;
//    case PRO_DIM_SNS_TYP_ANGLE:
//        ProUtilMsgPrint("gen", "TEST %0s", "Measured starting"
//            " from this entity");
//        p_sense->angle_sense.is_first = (ProBoolean)ProUtilYesnoGet((char*)"No");
//        ProUtilMsgPrint("gen", "TEST %0s", "Flip entity direction");
//        p_sense->angle_sense.should_flip = (ProBoolean)ProUtilYesnoGet((char*)"No");
//
//        break;
//    case PRO_DIM_SNS_TYP_PNT_ANGLE:
//        ProUtilMenuIntValueSelect(point_type, (int*)&p_sense->sense);
//        ProUtilMsgPrint("gen", "TEST %0s", "Measured starting"
//            " from this entity");
//        p_sense->angle_sense.is_first = (ProBoolean)ProUtilYesnoGet((char*)"No");
//        ProUtilMsgPrint("gen", "TEST %0s", "Flip entity direction");
//        p_sense->angle_sense.should_flip = (ProBoolean)ProUtilYesnoGet((char*)"No");
//
//        break;
//    default:
//        break;
//    }
//    ProUtilMenuIntValueSelect(dim_orient, (int*)&p_sense->orient_hint);
//}
//
//
//
///*============================================================================*\
// Function:	ProTestDimensionCreate
// Purpose:       Create standard dimension
//\*============================================================================*/
//int ProTestDimStandardCreate(
//    ProDrawing* p_mdl)
//{
//    ProError err;
//    ProVector loc;
//    int n_sel, i;
//    ProDimension dim;
//    ProMouseButton btn;
//    ProDimSense* sense_arr;
//    ProSelection* p_sel, * sel_arr;
//    ProView view;
//    ProBoolean dim_type = PRO_B_FALSE, is_sense;
//    static ProUtilMenuButtons dim_opt[] = {
//        {"DimType", 0, TEST_CALL_PRO_MENU_DELETE},
//        {"Dimension", PRO_B_FALSE, 0},
//        {"Ref Dim", PRO_B_TRUE, 0},
//        {"",0,0}
//    };
//    static ProUtilMenuButtons sense_act[] = {
//        {"SenseAct", 0, TEST_CALL_PRO_MENU_DELETE},
//        {"Default", PRO_B_FALSE, 0},
//        {"Sense", PRO_B_TRUE, 0},
//        {"",0,0}
//    };
//    err = ProUtilMenuIntValueSelect(dim_opt, (int*)&dim_type);
//    err = ProUtilMenuIntValueSelect(sense_act, (int*)&is_sense);
//
//    ProArrayAlloc(2, sizeof(ProDimSense), 1, (ProArray*)&sense_arr);
//    ProArrayAlloc(2, sizeof(ProSelection), 1, (ProArray*)&sel_arr);
//
//    for (i = 0; i < 2; i++)
//    {
//        if (is_sense)
//            ProTestSenseSet(&sense_arr[i]);
//        ProUtilMsgPrint("gen", "TEST %0s", "Select geometry entityes: ");
//        err = ProSelect((char*)"point,dtl_axis,datum,csys,edge,curve,surface", 1, NULL,
//            NULL, NULL, NULL, &p_sel, &n_sel);
//        if (n_sel < 1 && i < 1)
//            return (-1);
//        else if (err != PRO_TK_NO_ERROR || n_sel < 1)
//            break;
//        err = ProSelectionCopy(p_sel[0], &sel_arr[i]);
//    }
//
//    err = ProSelectionViewGet(sel_arr[0], &view);
//    TEST_CALL_REPORT("ProSelectionViewGet()",
//        "ProTestDimensionCreate()", err, err != PRO_TK_NO_ERROR);
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select dimension location");
//    if (ProMousePickGet(PRO_ANY_BUTTON, &btn, loc) != PRO_TK_NO_ERROR)
//        return (-1);
//
//    err = ProDrawingDimCreate(*p_mdl, sel_arr, sense_arr,
//        loc, dim_type, &dim);
//    TEST_CALL_REPORT("ProDrawingDimCreate()",
//        "ProTestDimensionCreate()", err, err != PRO_TK_NO_ERROR);
//    if (err == PRO_TK_NO_ERROR)
//    {
//        err = ProAnnotationShow((ProAnnotation*)&dim, NULL, view);
//        TEST_CALL_REPORT("ProAnnotationShow()",
//            "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    }
//    ProArrayFree((ProArray*)&sense_arr);
//    ProArrayFree((ProArray*)&sel_arr);
//
//    return (0);
//}
//
///*============================================================================*\
// Function:	ProTestToleranceSet
// Purpose:       Modify tolerance decimals of model dimensions
//\*============================================================================*/
//int ProTestToleranceSet(ProMdl* p_mdl, int mode)
//{
//    ProCharLine string;
//    ProError err;
//    ProToleranceType type;
//    int  decimals = 1, dec_range[2] = { 1, 3 };
//    static ProUtilMenuButtons tol_type[] = {
//      {"Tolerance Type", 0, TEST_CALL_PRO_MENU_DELETE},
//      {"Linear", PROTOLERANCE_LINEAR, 0},
//      {"Angular", PROTOLERANCE_ANGULAR, 0},
//      {"",0,0}
//    };
//    double value, val_range[2] = { 1e-9, 1e+5 };
//
//    err = ProUtilMenuIntValueSelect(tol_type, (int*)&type);
//    if (type != PROTOLERANCE_ANGULAR)
//    {
//        ProUtilMsgPrint("gen", "TEST %0s", "Enter number of decimals place[1-3]:");
//        ProUtilIntGet(dec_range, &decimals, &decimals);
//    }
//    else
//        decimals = 1;
//    err = ProToleranceDefaultGet(type, decimals, &value);
//    TEST_CALL_REPORT("ProToleranceDefaultGet()",
//        "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//    sprintf(string, "Enter default tolerance [%6.3f]: ", value);
//    ProUtilDoubleGet(val_range, &value, &value);
//    err = ProSolidToleranceSet((ProSolid)*p_mdl, type, decimals, value);
//    TEST_CALL_REPORT("ProSolidToleranceSet()",
//        "ProTestDimensionEdit()", err, err != PRO_TK_NO_ERROR);
//
//    return PRO_TK_NO_ERROR;
//}
//
///*============================================================================*\
// Function:  ProTestDimensionInfo
// Purpose:   Get dimension info
//\*============================================================================*/
//int ProTestDimensionInfo(ProMdl* p_mdl, int mode)
//{
//    ProError err;
//    ProSelection* p_sel;
//    int n_sel, i, j, n_decimals, n_dims;
//    ProModelitem sel_item;
//    char fname[PRO_PATH_SIZE];
//    ProPath name;
//    FILE* fp;
//    double solid_tol, default_tol;
//    ProDimension* p_dims = NULL;
//    ProView view;
//
//
//    ProTestQcrName((ProMdl*)p_mdl, (char*)".inf", fname);
//    fp = fopen(fname, "w");
//    if (fp == NULL)
//        return (-1);
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select feature or part");
//    err = ProSelect((char*)"feature,part", 1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
//    if ((err != PRO_TK_NO_ERROR) || (n_sel < 1))
//        return (-1);
//
//    err = ProSelectionViewGet(p_sel[0], &view);
//    TEST_CALL_REPORT("ProSelectionViewGet()",
//        "ProTestDimensionInfo()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProSelectionModelitemGet(p_sel[0], &sel_item);
//    TEST_CALL_REPORT("ProSelectionModelitemGet()",
//        "ProTestDimensionInfo()", err, err != PRO_TK_NO_ERROR);
//
//    if (sel_item.type == PRO_FEATURE)
//    {
//        fprintf(fp, "Feature dimensions:\n");
//        err = ProTestFeatureDimensionsCollect(&sel_item, &p_dims);
//        if (err == PRO_TK_NO_ERROR)
//        {
//            err = ProArraySizeGet((ProArray)p_dims, &n_dims);
//            for (i = 0; i < n_dims; i++)
//            {
//                ProTestDimensionInfoPrint(*p_mdl, p_dims[i], (ProMode)mode, view, fp);
//            }
//            err = ProArrayFree((ProArray*)&p_dims);
//        }
//    }
//    else if (sel_item.type == PRO_PART)
//    {
//        fprintf(fp, "Solid dimensions:\n");
//
//        for (i = 0; i < 2; i++)
//        {
//            err = ProTestSolidDimensionsCollect((ProSolid)sel_item.owner, (ProBoolean)i, &p_dims);
//            if (err == PRO_TK_NO_ERROR)
//            {
//                err = ProArraySizeGet((ProArray)p_dims, &n_dims);
//                for (j = 0; j < n_dims; j++)
//                {
//                    ProTestDimensionInfoPrint(*p_mdl, p_dims[j], (ProMode)mode, view, fp);
//                }
//                err = ProArrayFree((ProArray*)&p_dims);
//            }
//        }
//    }
//    else
//        return (0);
//    fprintf(fp, "        Default Tolerance:\n");
//    for (n_decimals = 1; n_decimals < 4; n_decimals++)
//    {
//        err = ProToleranceDefaultGet(PROTOLERANCE_LINEAR, n_decimals,
//            &default_tol);
//        TEST_CALL_REPORT("ProToleranceDefaultGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//        if (err == PRO_TK_NO_ERROR)
//        {
//            fprintf(fp, "    x.");
//            for (j = 0; j < n_decimals; j++)
//            {
//                fprintf(fp, "x");
//            }
//            fprintf(fp, "    +- %6.3f\n", default_tol);
//        }
//    }
//    err = ProToleranceDefaultGet(PROTOLERANCE_ANGULAR, 1, &default_tol);
//    TEST_CALL_REPORT("ProToleranceDefaultGet()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "    ANG    +- %6.3f\n", default_tol);
//
//    fprintf(fp, "        Solid Tolerance:\n");
//    for (n_decimals = 1; n_decimals < 4; n_decimals++)
//    {
//        err = ProSolidToleranceGet((ProSolid)*p_mdl, PROTOLERANCE_LINEAR,
//            n_decimals, &solid_tol);
//        TEST_CALL_REPORT("ProSolidToleranceGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//        if (err == PRO_TK_NO_ERROR)
//        {
//            fprintf(fp, "    x.");
//            for (j = 0; j < n_decimals; j++)
//            {
//                fprintf(fp, "x");
//            }
//            fprintf(fp, "    +- %6.3f\n", solid_tol);
//        }
//    }
//    err = ProSolidToleranceGet((ProSolid)*p_mdl, PROTOLERANCE_ANGULAR, 1,
//        &solid_tol);
//    TEST_CALL_REPORT("ProSolidToleranceGet()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "    ANG    +- %6.3f\n", solid_tol);
//
//    fclose(fp);
//
//    ProStringToWstring(name, fname);
//    ProInfoWindowDisplay(name, NULL, NULL);
//
//    return (0);
//
//}
//
///*============================================================================*\
// Function:	ProTestDimensionInfoPrint
// Purpose:       Print the dimension info
//\*============================================================================*/
//void ProTestDimensionInfoPrint(
//    ProMdl p_mdl,
//    ProDimension dim,
//    ProMode mode,
//    ProView view,
//    FILE* fp
//)
//{
//    ProError err;
//    ProMdlName mdl_name;
//    ProCharLine line;
//    ProPoint3d pos;
//    ProDimSense* sense_arr;
//    ProDimAttachment* sel_arr;
//    int n_attach;
//    ProMdlType type;
//
//    fprintf(fp, "%s dimension  id = %d \n",
//        dim.type == PRO_DIMENSION ? "Regular" : "Reference", dim.id);
//    if (mode == PRO_MODE_DRAWING)
//    {
//        err = ProMdlTypeGet(dim.owner, &type);
//        TEST_CALL_REPORT("ProMdlTypeGet()", "ProTestDimensionMenu()",
//            err, err != PRO_TK_NO_ERROR && err != PRO_TK_BAD_INPUTS);
//
//        err = ProDrawingDimensionPosGet((ProDrawing)p_mdl, &dim, pos);
//        TEST_CALL_REPORT("ProDrawingDimensionPosGet()", "ProTestDimensionMenu()",
//            err, err != PRO_TK_NO_ERROR && err != PRO_TK_BAD_INPUTS);
//        /*
//        if(type == PRO_MDL_DRAWING)
//            err = ProDimensionLocationGet(&dim, NULL, (ProDrawing)p_mdl, &data );
//        else
//            err = ProDimensionLocationGet(&dim, view, NULL, &data );
//
//        TEST_CALL_REPORT("ProDimensionLocationGet()", "ProTestDimensionMenu()",
//                         err, err != PRO_TK_NO_ERROR && err != PRO_TK_BAD_INPUTS);
//
//        err = ProDimlocationTextGet(data, &has_elbow, pos, &elbow_length);
//        TEST_CALL_REPORT("ProDimlocationTextGet()", "ProTestDimensionMenu()",
//                         err, err != PRO_TK_NO_ERROR && err != PRO_TK_BAD_INPUTS);
//        */
//
//        if (err == PRO_TK_NO_ERROR)
//            fprintf(fp, "        position: pos[0] = %6.3f, pos[1] = %6.3f, "
//                "pos[2] = %6.3f\n", pos[0], pos[1], pos[2]);
//        /* If function will be implemeted, uncomment this code */
//#if 0
//        err = ProDrawingDimensionViewGet((ProDrawing)p_mdl, &dim, &view);
//        TEST_CALL_REPORT("ProDrawingDimensionViewGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR); */
//            err = ProDrawingViewSolidGet((ProDrawing)p_mdl, view, &solid);
//        TEST_CALL_REPORT("ProDrawingViewSolidGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//#endif   
//        err = ProMdlMdlnameGet((ProMdl)dim.owner, mdl_name);
//        TEST_CALL_REPORT("ProMdlMdlnameGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//        fprintf(fp, "        Associated model:%s\n",
//            ProWstringToString(line, mdl_name));
//
//        err = ProDrawingDimAttachpointsGet((ProDrawing)p_mdl, &dim, &sel_arr,
//            &sense_arr);
//        TEST_CALL_REPORT("ProDrawingDimAttachpointsGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR &&
//            err != PRO_TK_INVALID_ITEM);
//        if (err == PRO_TK_NO_ERROR)
//        {
//            /* Bug in the func ProDrawingDimAttachpointsGet (pipe mode) */
//            err = ProArraySizeGet((ProArray)sel_arr, &n_attach);
//            if (err == PRO_TK_NO_ERROR && n_attach > 1)
//                ProTestDimensionAttachPrint(sel_arr, sense_arr, fp);
//
//            ProArrayFree((ProArray*)&sense_arr);
//            ProDimattachmentarrayFree(sel_arr);
//        }
//    }
//    ProTestDimensionParamPrint(dim, fp);
//}
//
///*============================================================================*\
// Function:	ProTestDimensionAttachPrint
// Purpose:       Print the dimension attachments data info
//\*============================================================================*/
//void ProTestDimensionAttachPrint(
//    ProDimAttachment* p_dimattach,
//    ProDimSense* p_sense,
//    FILE* fp
//)
//{
//    ProError err;
//    int i, j, n_attachs;
//    ProModelitem  item;
//    ProCharName c_name;
//    ProSelection* p_attach;
//
//    err = ProArraySizeGet((ProArray)p_dimattach, &n_attachs);
//    TEST_CALL_REPORT("ProArraySizeGet()",
//        "ProTestDimensionAttachPrint()", err, err != PRO_TK_NO_ERROR);
//    if (err == PRO_TK_NO_ERROR && n_attachs > 1)
//
//        for (j = 0; j < n_attachs; j++)
//        {
//            fprintf(fp, "        %d)Dimension attachment\n", (j + 1));
//            p_attach = p_dimattach[j];
//
//            for (i = 0; i < 2; i++)
//            {
//                if (p_attach[i] != NULL)
//                {
//                    err = ProSelectionModelitemGet(p_attach[i], &item);
//                    TEST_CALL_REPORT("ProSelectionModelitemGet()",
//                        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//
//                    ProUtilObjtypeStr(item.type, c_name);
//                    fprintf(fp, "        attachment %d Selection %d: %s\n", (j + 1), (i + 1), c_name);
//
//                    switch (p_sense[j + i].type)
//                    {
//                    case PRO_DIM_SNS_TYP_NONE:
//                        fprintf(fp, "        Type = NONE\n");
//
//                        break;
//                    case PRO_DIM_SNS_TYP_PNT:
//                        fprintf(fp, "        Type = POINT\n");
//                        fprintf(fp, "        Point type = %s\n",
//                            ProDimPointToStr((ProPointType)p_sense[j + i].sense));
//                        fprintf(fp, "        Orient type = %s\n",
//                            ProDimOrientToStr(p_sense[j + i].orient_hint));
//                        break;
//                    case PRO_DIM_SNS_TYP_SPLN_PNT:
//                        fprintf(fp, "        Type = SPLINE POINT\n");
//                        fprintf(fp, "        Index = %x\n", p_sense[j + i].sense);
//                        fprintf(fp, "        Orient type = %s\n",
//                            ProDimOrientToStr(p_sense[j + i].orient_hint));
//
//                        break;
//                    case PRO_DIM_SNS_TYP_TGT_IDX:
//                        fprintf(fp, "        Type = TANGENT INDEX\n");
//                        fprintf(fp, "        Index = %d\n", p_sense[j + i].sense);
//                        fprintf(fp, "        Orient type = %s\n",
//                            ProDimOrientToStr(p_sense[j + i].orient_hint));
//
//                        break;
//                    case PRO_DIM_SNS_TYP_LIN_AOC_TGT:
//                        fprintf(fp, "        Type = LINE_AOC_TANGENT\n");
//                        fprintf(fp, "        AOC type = %s\n",
//                            ProDimAocToStr((ProDimLinAocTgtSense)p_sense[j + i].sense));
//                        fprintf(fp, "        Orient type = %s\n",
//                            ProDimOrientToStr(p_sense[j + i].orient_hint));
//
//                        break;
//                    case PRO_DIM_SNS_TYP_ANGLE:
//                        fprintf(fp, "        Type = ANGLE\n");
//                        fprintf(fp, "        is_first    = %s\n",
//                            p_sense[j + i].angle_sense.is_first == PRO_B_FALSE ?
//                            "FALSE" : "TRUE");
//                        fprintf(fp, "        should_flip = %s\n",
//                            p_sense[i].angle_sense.should_flip == PRO_B_FALSE ?
//                            "FALSE" : "TRUE");
//                        fprintf(fp, "        Orient type = %s\n",
//                            ProDimOrientToStr(p_sense[j + i].orient_hint));
//
//                        break;
//                    case PRO_DIM_SNS_TYP_PNT_ANGLE:
//                        fprintf(fp, "        Type = POINT ANGLE\n");
//                        fprintf(fp, "        Point type = %s\n",
//                            ProDimPointToStr((ProPointType)p_sense[j + i].sense));
//                        fprintf(fp, "        is_first    = %s\n",
//                            p_sense[j + i].angle_sense.is_first == PRO_B_FALSE ?
//                            "FALSE" : "TRUE");
//                        fprintf(fp, "        should_flip = %s\n",
//                            p_sense[j + i].angle_sense.should_flip == PRO_B_FALSE ?
//                            "FALSE" : "TRUE");
//                        fprintf(fp, "        Orient type = %s\n",
//                            ProDimOrientToStr(p_sense[j + i].orient_hint));
//
//                        break;
//                    }
//                }
//            }
//        }
//}
//
///*============================================================================*\
// Function:	ProTestDimensionParamPrint
// Purpose:       Print the dimension parameter info
//\*============================================================================*/
//void ProTestDimensionParamPrint(
//    ProDimension dim,
//    FILE* fp
//)
//{
//    ProName      symbol;
//    ProDimToleranceType tol_type;
//    char* tol_string;
//    double       value, upper_limit, lower_limit;
//    ProDimensiontype type;
//    ProBoolean fractional, rel_driven, regened_negative, can_regen;
//    ProBoolean tolerance_displayed;
//    int decimals, denominator;
//    ProDisplayMode disp_mode;
//    ProLine* p_text = NULL;
//    ProError err;
//    ProCharLine line;
//
//    err = ProDimensionSymbolGet(&dim, symbol);
//    TEST_CALL_REPORT("ProDimensionSymbolGet()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, (char*)"        Symbol: %s\n", ProWstringToString(line, symbol));
//
//    err = ProDimensionValueGet(&dim, &value);
//    TEST_CALL_REPORT("ProDimensionValueGet()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "        Value: %6.3f\n", value);
//
//    err = ProDimensionToltypeGet(&dim, &tol_type);
//    TEST_CALL_REPORT("ProDimensionToltypeGet()",
//        "ProTestDimensionMenu()", err, (err != PRO_TK_NO_ERROR) && (err != PRO_TK_BAD_CONTEXT));
//    switch (tol_type)
//    {
//    case PRO_TOL_DEFAULT:
//        tol_string = (char*)"default";
//        break;
//    case PRO_TOL_LIMITS:
//        tol_string = (char*)"limits";
//        break;
//    case PRO_TOL_PLUS_MINUS:
//        tol_string = (char*)"plus/minus";
//        break;
//    case PRO_TOL_PLUS_MINUS_SYM:
//        tol_string = (char*)"symmetric";
//        break;
//    case PRO_DIM_TOL_SYM_SUPERSCRIPT:
//        tol_string = (char*)"pm_sym_superscript";
//        break;
//    default:
//        tol_string = (char*)"error";
//        break;
//    }
//    fprintf(fp, "        Tolerance type:  %s\n", tol_string);
//
//    if (dim.type != PRO_REF_DIMENSION)
//    {
//
//        err = ProDimensionToleranceGet(&dim, &upper_limit, &lower_limit);
//        TEST_CALL_REPORT("ProDimensionToleranceGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//        fprintf(fp, "        Tolerance:   upper limit: %6.3f, lower limit: %6.3f\n",
//            upper_limit, lower_limit);
//    }
//
//    err = ProDimensionTypeGet(&dim, &type);
//    TEST_CALL_REPORT("ProDimensionTypeGet()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, (char*)"        Type: %s\n", ProDimTypeToStr(type));
//
//    err = ProDimensionIsFractional(&dim, &fractional);
//    TEST_CALL_REPORT("ProDimensionIsFractional()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "        Fractional: %s\n", (fractional ? "Yes" : "No"));
//
//
//    if (fractional)
//    {
//        err = ProDimensionDenominatorGet(&dim, &denominator);
//        TEST_CALL_REPORT("ProDimensionDenominatorGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//        fprintf(fp, "        Denominator: %d\n", denominator);
//    }
//    else
//    {
//        err = ProDimensionDecimalsGet(&dim, &decimals);
//        TEST_CALL_REPORT("ProDimensionDecimalsGet()",
//            "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//        fprintf(fp, "        Decimals: %d\n", decimals);
//
//    }
//    err = ProDimensionIsReldriven(&dim, &rel_driven);
//    TEST_CALL_REPORT("ProDimensionIsReldriven()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "        Reldriven: %s\n", (rel_driven ? "Yes" : "No"));
//
//    err = ProDimensionIsRegenednegative(&dim, &regened_negative);
//    TEST_CALL_REPORT("ProDimensionIsRegenednegative()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "        Regenednegative: %s\n", (regened_negative ? "Yes" : "No"));
//
//    err = ProDisplaymodeGet(&disp_mode);
//    TEST_CALL_REPORT("ProDisplaymodeGet()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "        Displaymode: %s\n",
//        (disp_mode ? "SYMBOLIC" : "NUMERIC"));
//
//    err = ProDimensionCanRegen(&dim, &can_regen);
//    TEST_CALL_REPORT("ProDimensionCanRegen()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR &&
//        err != PRO_TK_BAD_CONTEXT);
//    fprintf(fp, "        CanRegen: %s\n", (can_regen ? "Yes" : "No"));
//
//    err = ProDimensionIsToleranceDisplayed(&dim, &tolerance_displayed);
//    TEST_CALL_REPORT("ProDimensionIsToleranceDisplayed()",
//        "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR);
//    fprintf(fp, "        ToleranceDisplayed: %s\n",
//        (tolerance_displayed ? "Yes" : "No"));
//    /*
//    err = ProDimensionTextGet (&dim, &p_text);
//    TEST_CALL_REPORT("ProDimensionTextGet()",
//                         "ProTestDimensionMenu()", err, err != PRO_TK_NO_ERROR
//                         && err != PRO_TK_E_NOT_FOUND);
//
//    if (err == PRO_TK_NO_ERROR && p_text != NULL)
//    {
//        err = ProArraySizeGet ((ProArray)p_text, &n_text);
//        if (err == PRO_TK_NO_ERROR && n_text)
//        {
//            fprintf(fp, "        Dimension text:\n");
//            for (i = 0; i < n_text; i++)
//                fprintf (fp, (char*)"       %s", ProWstringToString (line, p_text[i]));
//        }
//    }
//    */
//}
//
///*============================================================================*\
// Function:	ProTestSelectionDimFilter
// Purpose:       Filter function for dimension select
//\*============================================================================*/
//ProError ProTestSelectionDimFilter(
//    ProSelection sel,
//    ProAppData data)
//{
//    ProError err;
//    ProDimension dim, base_dim;
//    UserDimData* sel_data = (UserDimData*)data;
//    ProBoolean is_ordinate, type = sel_data->flag;
//    ProDrawing drw = (ProDrawing)sel_data->parent;
//
//    err = ProSelectionModelitemGet(sel, &dim);
//    TEST_CALL_REPORT("ProSelectionModelitemGet()",
//        "ProTestSelectionDimFilter()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProDrawingDimIsOrdinate(drw, &dim, &is_ordinate, &base_dim);
//    TEST_CALL_REPORT("ProDrawingDimIsOrdinate()",
//        "ProTestSelectionDimFilter()", err, err != PRO_TK_NO_ERROR);
//
//    return (is_ordinate == type ? PRO_TK_NO_ERROR : PRO_TK_CONTINUE);
//}
//
///*============================================================================*\
// Function:	ProTestDimType
// Purpose:       Create ordinate dimension
//\*============================================================================*/
//int ProTestDimOrdinateCreate(ProDrawing* p_drw)
//{
//    ProError err;
//    int n_sel;
//    ProSelection* p_sel;
//    ProDimension dim, base_dim;
//    ProVector loc, loc_out;
//    ProMouseButton btn;
//    UserDimData sel_data;
//    ProSelFunctions filter;
//    ProView        view;
//    ProMatrix  transform_from_draw_to_model;
//
//    sel_data.parent = (ProMdl)*p_drw;
//    sel_data.flag = PRO_B_FALSE;
//
//    memset(&filter, '\0', sizeof(ProSelFunctions));
//    filter.post_filter = (ProSelectionPostFilter)ProTestSelectionDimFilter;
//    filter.app_data = (ProAppData)&sel_data;
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select linear dimension");
//    err = ProSelect((char*)"dimension", 1, NULL, &filter, NULL, NULL,
//        &p_sel, &n_sel);
//    if (err != PRO_TK_NO_ERROR || n_sel < 1)
//        return 0;
//
//    err = ProSelectionModelitemGet(p_sel[0], &dim);
//    TEST_CALL_REPORT("ProSelectionModelitemGet()",
//        "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProDrawingDimensionViewGet(*p_drw, &dim, &view);
//    TEST_CALL_REPORT("ProDrawingDimensionViewGet()",
//        "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProDrawingViewTransformGet(*p_drw, view, PRO_B_FALSE, transform_from_draw_to_model);
//    TEST_CALL_REPORT("ProDrawingViewTransformGet()",
//        "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select a location");
//    if (ProMousePickGet(PRO_ANY_BUTTON, &btn, loc) != PRO_TK_NO_ERROR)
//        return (-1);
//
//    err = ProPntTrfEval(loc, transform_from_draw_to_model, loc_out);
//    TEST_CALL_REPORT("ProPntTrfEval()",
//        "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProDrawingOrdbaselineCreate(*p_drw, &dim, loc_out, &base_dim);
//    TEST_CALL_REPORT("ProDrawingOrdbaselineCreate()",
//        "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    if (err == PRO_TK_NO_ERROR)
//    {
//        err = ProAnnotationShow((ProAnnotation*)&dim, NULL, view);
//        TEST_CALL_REPORT("ProAnnotationShow()",
//            "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//    }
//
//    return(0);
//
//}
//
///*============================================================================*\
// Function:	ProTestDimType
// Purpose:       Move drawing dimension
//\*============================================================================*/
//int ProTestDimMove(ProDrawing* p_drw)
//{
//    ProError err;
//    ProSelection* p_sel;
//    int n_sel;
//    ProVector loc;
//    ProView view;
//    ProDimension dim;
//    ProMouseButton btn;
//    ProAsmcomppath comp_path;
//    ProAsmcomppath* compathPtr = NULL;
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select linear dimension");
//    err = ProSelect((char*)"dimension,ref_dim", 1, NULL, NULL, NULL, NULL,
//        &p_sel, &n_sel);
//    if (err != PRO_TK_NO_ERROR || n_sel < 1)
//        return 0;
//
//    err = ProSelectionViewGet(p_sel[0], &view);
//
//    err = ProSelectionModelitemGet(p_sel[0], &dim);
//    TEST_CALL_REPORT("ProSelectionModelitemGet()",
//        "ProTestDimMove()", err, err != PRO_TK_NO_ERROR);
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Select new position");
//    if (ProMousePickGet(PRO_ANY_BUTTON, &btn, loc) != PRO_TK_NO_ERROR)
//        return (-1);
//
//    err = ProSelectionAsmcomppathGet(p_sel[0], &comp_path);
//
//    if (err == PRO_TK_NO_ERROR)
//        compathPtr = &comp_path;
//
//    err = ProAnnotationUndisplay((ProAnnotation*)&dim, compathPtr, *p_drw);
//    TEST_CALL_REPORT("ProAnnotationUndisplay()", "ProTestDimMove()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProDrawingDimensionMove(*p_drw, &dim, loc);
//    TEST_CALL_REPORT("ProDrawingDimensionMove()",
//        "ProTestDimOrdinateCreate()", err, err != PRO_TK_NO_ERROR);
//
//    ProAnnotationDisplay((ProAnnotation*)&dim, compathPtr, *p_drw, view);
//    TEST_CALL_REPORT("ProAnnotationDisplay()", "ProTestDimMove()", err, err != PRO_TK_NO_ERROR);
//
//    return (0);
//
//}
//
///*============================================================================*\
// Function:	ProTestDimType
// Purpose:       Convert ordinate dimension to linear
//\*============================================================================*/
//int ProTestOrdinateToLinear(ProDrawing* p_drw)
//{
//    ProSelection* p_sel;
//    int n_sel;
//    UserDimData sel_data;
//    ProSelFunctions filter;
//    ProDimension dim;
//    ProError err;
//
//    sel_data.flag = PRO_B_TRUE;
//    sel_data.parent = *p_drw;
//
//    memset(&filter, '\0', sizeof(ProSelFunctions));
//    filter.post_filter = (ProSelectionPostFilter)ProTestSelectionDimFilter;
//    filter.app_data = (ProAppData)&sel_data;
//
//    ProUtilMsgPrint("gen", "TEST %0s", "Ordinate dimension: ");
//    err = ProSelect((char*)"dimension", 1, NULL, &filter, NULL, NULL,
//        &p_sel, &n_sel);
//    if (err != PRO_TK_NO_ERROR || n_sel < 1)
//        return 0;
//
//    err = ProSelectionModelitemGet(p_sel[0], &dim);
//    TEST_CALL_REPORT("ProSelectionModelitemGet()",
//        "ProTestOrdinateToLinear()", err, err != PRO_TK_NO_ERROR);
//
//    err = ProDrawingDimToLinear(*p_drw, &dim);
//    TEST_CALL_REPORT("ProDrawingDimToLinear()",
//        "ProTestOrdinateToLinear()", err, err != PRO_TK_NO_ERROR);
//
//    return (0);
//
//}
//
///*============================================================================*\
// Function:	ProTestDimDisplayAct
// Purpose:
//\*============================================================================*/
//int ProTestDimDisplayAct(
//    UserDimData* data,
//    int opt)
//{
//    ProError err;
//    ProSelection* p_sel;
//    int n_sel, n_dims, i, n_ref_dims;
//    ProView view = NULL;
//    ProAsmcomppath* p_path = NULL, path;
//    ProFeature feature;
//    ProModelitem sel_item;
//    ProSolid solid;
//    ProDimension* p_dims = NULL, dim, * p_ref_dims = NULL;
//    ProMdlType type, drw_type;
//    ProDrawing drawing = NULL;
//
//    err = ProMdlTypeGet(data->parent, &type);
//    TEST_CALL_REPORT("ProMdlTypeGet()",
//        "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//
//    if (opt == DIM_FEATURE || opt == DIM_FEATURE_VIEW)
//    {
//        ProUtilMsgPrint("gen", "TEST %0s", "Select feature: ");
//        err = ProSelect((char*)"feature", 1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
//        TEST_CALL_REPORT("ProSelect()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        if (err != PRO_TK_NO_ERROR || n_sel < 1)
//            return (0);
//        err = ProSelectionModelitemGet(p_sel[0], &feature);
//        TEST_CALL_REPORT("ProSelectionModelitemGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        err = ProTestFeatureDimensionsCollect(&feature, &p_dims);
//        if (err != PRO_TK_NO_ERROR)
//            return (0);
//
//    }
//    else if (opt == DIM_PART || opt == DIM_PART_VIEW)
//    {
//        ProUtilMsgPrint("gen", "TEST %0s", "Select part: ");
//        err = ProSelect((char*)"part", 1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
//        TEST_CALL_REPORT("ProSelect()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        if (err != PRO_TK_NO_ERROR || n_sel < 1)
//            return (0);
//        err = ProSelectionModelitemGet(p_sel[0], &sel_item);
//        TEST_CALL_REPORT("ProSelectionModelitemGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        err = ProModelitemMdlGet(&sel_item, (ProMdl*)&solid);
//        TEST_CALL_REPORT("ProModelitemMdlGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        err = ProTestSolidDimensionsCollect(solid, PRO_B_FALSE, &p_dims);
//        err = ProTestSolidDimensionsCollect(solid, PRO_B_TRUE, &p_ref_dims);ProUtilMenuIntValueSelect
//        if (p_dims == NULL && p_ref_dims == NULL)
//            return (0);
//        if (p_ref_dims != NULL)
//        {
//            err = ProArraySizeGet((ProArray)p_ref_dims, &n_ref_dims);
//            err = ProArrayObjectAdd((ProArray*)&p_dims, PRO_VALUE_UNUSED, n_ref_dims,
//                p_ref_dims);
//            TEST_CALL_REPORT("ProArrayObjectAdd()",
//                "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        }
//    }
//    else if (opt == DIM_VIEW)
//    {
//        ProUtilMsgPrint("gen", "TEST %0s", "Select view: ");
//        err = ProSelect((char*)"dwg_view", 1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
//        TEST_CALL_REPORT("ProSelect()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        if (err != PRO_TK_NO_ERROR || n_sel < 1)
//            return (0);
//        err = ProSelectionViewGet(p_sel[0], &view);
//        TEST_CALL_REPORT("ProSelectionViewGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        err = ProDrawingViewSolidGet((ProDrawing)data->parent, view, &solid);
//        TEST_CALL_REPORT("ProDrawingViewSolidGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        err = ProTestSolidDimensionsCollect(solid, PRO_B_FALSE, &p_dims);
//        err = ProTestSolidDimensionsCollect(solid, PRO_B_TRUE, &p_ref_dims);
//        if (p_dims == NULL && p_ref_dims == NULL)
//            return (0);
//        if (p_ref_dims != NULL)
//        {
//            err = ProArraySizeGet((ProArray)p_ref_dims, &n_ref_dims);
//            err = ProArrayObjectAdd((ProArray*)&p_dims, PRO_VALUE_UNUSED, n_ref_dims,
//                p_ref_dims);
//            TEST_CALL_REPORT("ProArrayObjectAdd()",
//                "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        }
//    }
//    else if (opt == DIM_SELECTED)
//    {
//        ProUtilMsgPrint("gen", "TEST %0s", "Select dimensions: ");
//        err = ProSelect((char*)"dimension,ref_dim", -1, NULL, NULL, NULL, NULL, &p_sel,
//            &n_sel);
//        TEST_CALL_REPORT("ProSelect()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        if (n_sel < 1)
//            return (0);
//        err = ProArrayAlloc(n_sel, sizeof(ProDimension), 1, (ProArray*)&p_dims);
//        for (i = 0; i < n_sel; i++)
//        {
//            err = ProSelectionModelitemGet(p_sel[i], &dim);
//            TEST_CALL_REPORT("ProSelectionModelitemGet()",
//                "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//            p_dims[i] = dim;
//        }
//    }
//    else
//        return (0);
//
//    if (type == PRO_MDL_ASSEMBLY)
//    {
//        err = ProSelectionAsmcomppathGet(p_sel[0], &path);
//        TEST_CALL_REPORT("ProSelectionAsmcomppathGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//        if (path.table_num == 0)
//            p_path = NULL;
//        else
//            p_path = &path;
//    }
//    else if (type == PRO_MDL_DRAWING)
//    {
//        drawing = (ProDrawing)data->parent;
//        err = ProSelectionViewGet(p_sel[0], &view);
//        TEST_CALL_REPORT("ProSelectionViewGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//
//        err = ProDrawingViewSolidGet(drawing, view, &solid);
//        TEST_CALL_REPORT("ProDrawingViewSolidGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//
//        err = ProMdlTypeGet(solid, &drw_type);
//        TEST_CALL_REPORT("ProMdlTypeGet()",
//            "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//
//        if (PRO_MDL_ASSEMBLY == drw_type)
//        {
//            err = ProSelectionAsmcomppathGet(p_sel[0], &path);
//            TEST_CALL_REPORT("ProSelectionAsmcomppathGet()",
//                "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//            if (path.table_num == 0)
//                p_path = NULL;
//            else
//                p_path = &path;
//        }
//    }
//
//    err = ProArraySizeGet((ProArray)p_dims, &n_dims);
//    TEST_CALL_REPORT("ProArraySizeGet()",
//        "ProTestDimDisplayAct()", err, err != PRO_TK_NO_ERROR);
//
//    for (i = 0; i < n_dims; i++)
//    {
//        if (data->flag)
//        {
//            /*
//            If component path is non-null then we are trying to display the annotations
//            of some part in the assembly and we cannot permanently display part's annotation
//            in assembly context so temporary display it and modify
//            */
//            if (p_path != NULL)
//                err = ProAnnotationDisplay((ProAnnotation*)&p_dims[i], p_path, NULL, view);
//            /*
//            Permanent display of annotation belongs to top solid which is current object too.
//            Component path must be NULL for NULL view
//            */
//            else
//                err = ProAnnotationShow((ProAnnotation*)&p_dims[i], p_path, view);
//        }
//        else
//            err = ProAnnotationErase((ProAnnotation*)&p_dims[i], drawing);
//    }
//    if (p_dims != NULL)
//        err = ProArrayFree((ProArray*)&p_dims);
//    if (p_ref_dims != NULL)
//        err = ProArrayFree((ProArray*)&p_ref_dims);
//
//    return (0);
//}
//
///*============================================================================*\
// Function:	ProTestDimDisplayMenu
// Purpose:
//\*============================================================================*/
//int ProTestDimDisplayMenu(ProMdl* p_mdl, int disp_opt)
//{
//    ProError err;
//    int menu_id;
//    ProMode mode;
//    UserDimData disp_data;
//
//    disp_data.parent = *p_mdl;
//    disp_data.flag = (ProBoolean)disp_opt;
//
//    err = ProModeCurrentGet(&mode);
//
//
//    ProMenuFileRegister((char*)"TkDimDisp", (char*)"tkdimdisp.mnu", &menu_id);
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"TkDimDisp",
//        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
//
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"Feature",
//        (ProMenubuttonAction)ProTestDimDisplayAct, &disp_data, DIM_FEATURE);
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"Part",
//        (ProMenubuttonAction)ProTestDimDisplayAct, &disp_data, DIM_PART);
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"Feature&View",
//        (ProMenubuttonAction)ProTestDimDisplayAct, &disp_data, DIM_FEATURE_VIEW);
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"Part&View",
//        (ProMenubuttonAction)ProTestDimDisplayAct, &disp_data, DIM_PART_VIEW);
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"View",
//        (ProMenubuttonAction)ProTestDimDisplayAct, &disp_data, DIM_VIEW);
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"Selected items",
//        (ProMenubuttonAction)ProTestDimDisplayAct, &disp_data, DIM_SELECTED);
//
//    ProMenubuttonActionSet((char*)"TkDimDisp", (char*)"Done",
//        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
//    if (disp_opt)
//        err = ProMenubuttonVisibilitySet((char*)"TkDimDisp", (char*)"Selected items", PRO_B_FALSE);
//
//    if (mode == PRO_MODE_ASSEMBLY || mode == PRO_MODE_PART)
//    {
//        err = ProMenubuttonVisibilitySet((char*)"TkDimDisp", (char*)"Feature&View", PRO_B_FALSE);
//        err = ProMenubuttonVisibilitySet((char*)"TkDimDisp", (char*)"Part&View", PRO_B_FALSE);
//        err = ProMenubuttonVisibilitySet((char*)"TkDimDisp", (char*)"View", PRO_B_FALSE);
//    }
//    else
//    {
//        err = ProMenubuttonVisibilitySet((char*)"TkDimDisp", (char*)"Feature", PRO_B_FALSE);
//        err = ProMenubuttonVisibilitySet((char*)"TkDimDisp", (char*)"Part", PRO_B_FALSE);
//    }
//    ProMenuCreate(PROMENUTYPE_MAIN, (char*)"TkDimDisp", &menu_id);
//    ProMenuProcess((char*)"TkDimDisp", &menu_id);
//
//    return (0);
//}
//
///*============================================================================*\
// Function:	ProDimPointToStr
// Purpose:
//\*============================================================================*/
//char* ProDimPointToStr(
//    ProPointType type
//)
//{
//    switch (type)
//    {
//    case PRO_POINT_TYP_END1: return (char*)"END1";
//    case PRO_POINT_TYP_END2: return (char*)"END2";
//    case PRO_POINT_TYP_CENTER: return (char*)"CENTER";
//    case PRO_POINT_TYP_NONE: return (char*)"NONE";
//    case PRO_POINT_TYP_MIDPT: return (char*)"MIDPNT";
//    default: return (char*)"INVALID";
//    }
//}
//
///*============================================================================*\
// Function:	ProDimAocToStr
// Purpose:
//\*============================================================================*/
//char* ProDimAocToStr(
//    ProDimLinAocTgtSense sense
//)
//{
//    switch (sense)
//    {
//    case PRO_DIM_LIN_AOC_TGT_LEFT0: return (char*)"LEFT0";
//    case PRO_DIM_LIN_AOC_TGT_RIGHT0: return (char*)"RIGHT0";
//    case PRO_DIM_LIN_AOC_TGT_LEFT1: return (char*)"LEFT1";
//    case PRO_DIM_LIN_AOC_TGT_RIGHT1: return (char*)"RIGHT1";
//    default: return (char*)"INVALID";
//    }
//}
//
///*============================================================================*\
// Function:	ProDimOrientToStr
// Purpose:
//\*============================================================================*/
//char* ProDimOrientToStr(
//    ProDimOrient orient
//)
//{
//    switch (orient)
//    {
//    case PRO_DIM_ORNT_NONE: return (char*)"NONE";
//    case PRO_DIM_ORNT_HORIZ: return (char*)"HORIZ";
//    case PRO_DIM_ORNT_VERT: return (char*)"VERT";
//    case PRO_DIM_ORNT_SLANTED: return (char*)"SLANTED";
//    case PRO_DIM_ORNT_ELPS_RAD1: return (char*)"ELPS_RAD1";
//    case PRO_DIM_ORNT_ELPS_RAD2: return (char*)"ELPS_RAD2";
//    case PRO_DIM_ORNT_ARC_ANG: return (char*)"ARC_ANG";
//    case PRO_DIM_ORNT_ARC_LENGTH: return (char*)"ARC_LENGTH";
//    case PRO_DIM_ORNT_LIN_TANCRV_ANG: return (char*)"LIN_TANCRV_ANG";
//    default: return (char*)"INVALID";
//    }
//}
//
///*============================================================================*\
// Function:	ProDimOrientToStr
// Purpose:
//\*============================================================================*/
//char* ProDimTypeToStr(
//    ProDimensiontype type
//)
//{
//    switch (type)
//    {
//    case PRODIMTYPE_UNKNOWN: return (char*)"UNKNOWN";
//    case PRODIMTYPE_LINEAR: return (char*)"LINEAR";
//    case PRODIMTYPE_RADIUS: return (char*)"RADIUS";
//    case PRODIMTYPE_DIAMETER: return (char*)"DIAMETER";
//    case PRODIMTYPE_ANGLE: return (char*)"ANGLE";
//    default: return (char*)"INVALID";
//    }
//}
///*============================================================================*\
// Function:	ProTestSolidDimensionsCollect ()
// Purpose:       Tis function temporary used, while ProSolidDimension visit
//                not implemented.
//\*============================================================================*/
//ProError ProTestSolidDimensionsCollect(
//    ProSolid        solid,              /* In */
//    ProBoolean      is_refdim,          /* In */
//    ProDimension** pp_dims             /* Out (ProArray)*/
//)
//{
//    ProError err;
//    int n_dims;
//    int* dim_array = NULL, i;
//
//    if (pp_dims != NULL && solid != NULL)
//        *pp_dims = (ProDimension*)NULL;
//    else
//        return (PRO_TK_BAD_INPUTS);
//
//    err = ProUtilCollectDimension((ProMdl)solid, is_refdim, pp_dims);
//
//    err = ProArraySizeGet(*pp_dims, &n_dims);
//
//    if (n_dims == -1)
//        return (PRO_TK_GENERAL_ERROR);
//    if (n_dims == 0)
//        return (PRO_TK_E_NOT_FOUND);
//
//    return (PRO_TK_NO_ERROR);
//}
///*============================================================================*\
// Function:	ProTestFeatureDimensionsCollect ()
// Purpose:       Collects all dimensions in the feature.
//\*============================================================================*/
//ProError ProTestFeatureDimensionsCollect(
//    ProFeature* feature,
//    ProDimension** pp_dims
//)
//{
//    ProError err;
//    ProDimension* p_dims;
//    int n_dims;
//    int* dim_array = NULL, i;
//
//    if (pp_dims != NULL && feature != NULL)
//        *pp_dims = (ProDimension*)NULL;
//    else
//        return (PRO_TK_BAD_INPUTS);
//
//
//    err = ProArrayAlloc(0, sizeof(ProDimension), 1, (ProArray*)pp_dims);
//    err = ProFeatureDimensionVisit(feature, (ProDimensionVisitAction)ProUtilCollectDimVisitAction,
//        (ProDimensionFilterAction)NULL, (ProAppData)pp_dims);
//
//    ProArraySizeGet((ProArray*)*pp_dims, &n_dims);
//
//    if (n_dims == -1)
//        return (PRO_TK_GENERAL_ERROR);
//    if (n_dims == 0)
//        return (PRO_TK_E_NOT_FOUND);
//    return (PRO_TK_NO_ERROR);
//}