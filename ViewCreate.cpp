#include "ViewCreate.h"

/*
    Copyright (c) 2019 PTC Inc. and/or Its Subsidiary Companies. All Rights Reserved.
*/


/*--------------------------------------------------------------------*\
Pro/TOOLKIT includes
\*--------------------------------------------------------------------*/
#include <ProToolkit.h>
#include <ProMdl.h>
#include <ProMenu.h>
#include <ProMessage.h>
#include <ProView.h>
#include <ProWindows.h>
#include <ProUtil.h>

/*--------------------------------------------------------------------*\
C System includes
\*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*\
Application includes
\*--------------------------------------------------------------------*/
#include "TestError.h"
#include "TestMenu.h"
#include "UtilFiles.h"
#include "UtilMatrix.h"
#include "UtilString.h"
#include "UtilMessage.h"
#include <ProTKRunTime.h>
#include <PTApplsUnicodeUtils.h>

#define EXT_VMTX  ".vwm"


#define PRO_TEST_STORE_VIEW     1
#define PRO_TEST_RETRIEVE_VIEW  2
#define PRO_TEST_SET_VIEW       3
#define PRO_TEST_RESET_VIEW     4
#define PRO_TEST_REFRESH_VIEW   5
#define PRO_TEST_REDISPLAY_VIEW 6
#define PRO_TEST_ROTATE_VIEW_X  7
#define PRO_TEST_ROTATE_VIEW_Y  8
#define PRO_TEST_ROTATE_VIEW_Z  9
#define PRO_TEST_LIST_VIEWNAMES 10
#define PRO_TEST_REFIT_VIEW     11
#define PRO_TEST_REFIT_VINDOW   12

#define FPRINT3E(a,b,c) {                       \
                ProTKFprintf (a, "%s   %14.7e %14.7e %14.7e\n",  \
                        b,  c[0], c[1], c[2]);  \
                        }

static ProMatrix  tmatrix = { {1.0, 0.0, 0.0, 0.0},
                              {0.0, 1.0, 0.0, 0.0},
                              {0.0, 0.0, 1.0, 0.0},
                              {0.0, 0.0, 0.0, 1.0} };

/*====================================================================*\
    FUNCTION :  ProTestViewMenu()
    PURPOSE  :  Set view test menu.
\*====================================================================*/
int ProTestViewMenu()
{
    ProMdl    model;
    ProError  status;
    int       menu_id, action;

    /*  Declare external functions  */
    extern int ProTestViewSet(ProAppData app_data, int option);
    extern int ProTestViewRotate(ProAppData app_data, int option);
    extern int ProTestViewStore(ProAppData app_data, int option);
    extern int ProTestViewList(ProAppData app_data, int option);
#ifndef PROE_JR_BUILD
    extern int ProTestViewMatrxWrite(ProAppData app_data, int option);
#endif


    status = ProMdlCurrentGet(&model);
    TEST_CALL_REPORT("ProMdlCurrentGet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    if (status != PRO_TK_NO_ERROR)
        return(-1);

    /*  Set-up the menu. */
    status = ProMenuFileRegister((char*)"TkView", (char*)"tkview.mnu", &menu_id);
    TEST_CALL_REPORT("ProMenuFileRegister()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);

    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Set View",
        (ProMenubuttonAction)ProTestViewSet, NULL, PRO_TEST_SET_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Reset View",
        (ProMenubuttonAction)ProTestViewSet, NULL, PRO_TEST_RESET_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Refit View",
        (ProMenubuttonAction)ProTestViewSet, NULL, PRO_TEST_REFIT_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Refit Window",
        (ProMenubuttonAction)ProTestViewSet, NULL, PRO_TEST_REFIT_VINDOW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Rot View X",
        (ProMenubuttonAction)ProTestViewRotate, NULL, PRO_TEST_ROTATE_VIEW_X);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Rot View Y",
        (ProMenubuttonAction)ProTestViewRotate, NULL, PRO_TEST_ROTATE_VIEW_Y);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Rot View Z",
        (ProMenubuttonAction)ProTestViewRotate, NULL, PRO_TEST_ROTATE_VIEW_Z);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Store View",
        (ProMenubuttonAction)ProTestViewStore, NULL, PRO_TEST_STORE_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Retrieve View",
        (ProMenubuttonAction)ProTestViewStore, NULL, PRO_TEST_RETRIEVE_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Refresh View",
        (ProMenubuttonAction)ProTestViewSet, NULL, PRO_TEST_REFRESH_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Redisplay View",
        (ProMenubuttonAction)ProTestViewSet, NULL, PRO_TEST_REDISPLAY_VIEW);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-List Views",
        (ProMenubuttonAction)ProTestViewList, NULL, PRO_TEST_LIST_VIEWNAMES);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
#ifndef PROE_JR_BUILD
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-View WinMatrx",
        (ProMenubuttonAction)ProTestViewMatrxWrite, NULL, 0);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
#endif

    status = ProMenubuttonActionSet((char*)"TkView", (char*)"-Done/Return",
        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);

    /* Exit action for the menu. */
    status = ProMenubuttonActionSet((char*)"TkView", (char*)"TkView",
        (ProMenubuttonAction)ProMenuDelete, NULL, 0);
    TEST_CALL_REPORT("ProMenubuttonActionSet()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);

    /* Display Menu and set it into action. */
    status = ProMenuCreate(PROMENUTYPE_MAIN, (char*)"TkView", &menu_id);
    TEST_CALL_REPORT("ProMenuCreate()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR);
    status = ProMenuProcess((char*)"TkView", &action);
    TEST_CALL_REPORT("ProMenuProcess()", "ProTestView()",
        status, status != PRO_TK_NO_ERROR && status != PRO_TK_E_FOUND);

    return(1);
}


/*====================================================================*\
    FUNCTION :  ProTestViewSet()
    PURPOSE  :  Set view matrix test.
\*====================================================================*/
int ProTestViewSet(ProAppData app_data, int option)
{
    ProMatrix   vmatrix, matrix;
    ProError    status;
    double      tvec[4];
    int i, w_id;

    status = ProWindowCurrentGet(&w_id);
    TEST_CALL_REPORT("ProWindowCurrentGet()", "ProTestViewSet()",
        status, status != PRO_TK_NO_ERROR);

    switch (option)
    {

        /* Set the view, using the identity matrix  */
    case PRO_TEST_SET_VIEW:

        status = ProViewMatrixGet(NULL, NULL, vmatrix);
        TEST_CALL_REPORT("ProViewMatrixGet()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);

        ProUtilMatrixCopy(tmatrix, matrix);

        status = ProViewMatrixSet(NULL, NULL, matrix);
        TEST_CALL_REPORT("ProViewMatrixSet()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);

        status = ProWindowRepaint(PRO_VALUE_UNUSED);
        TEST_CALL_REPORT("ProWindowRepaint()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);

        /*  Now shift the matrix  */
        for (i = 0; i < 4; i++) tvec[i] = tmatrix[0][i];
        for (i = 0; i < 4; i++) tmatrix[0][i] = tmatrix[1][i];
        for (i = 0; i < 4; i++) tmatrix[1][i] = tmatrix[2][i];
        for (i = 0; i < 4; i++) tmatrix[2][i] = tvec[i];

        break;

        /*  Reset the view to default orientation  */
    case PRO_TEST_RESET_VIEW:
        status = ProViewReset(NULL, NULL);
        TEST_CALL_REPORT("ProViewReset()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);
        status = ProWindowClear(w_id);
        TEST_CALL_REPORT("ProWindowClear()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);
        status = ProWindowRefresh(PRO_VALUE_UNUSED);
        TEST_CALL_REPORT("ProWindowRefresh()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);
        break;

        /*  Refresh the window  */
    case PRO_TEST_REFRESH_VIEW:
        status = ProWindowRefresh(PRO_VALUE_UNUSED);
        TEST_CALL_REPORT("ProWindowRefresh()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);
        break;

        /*  Re-display the object  */
    case PRO_TEST_REDISPLAY_VIEW:
        status = ProWindowClear(w_id);
        TEST_CALL_REPORT("ProWindowClear()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);
        status = ProWindowRefresh(PRO_VALUE_UNUSED);
        TEST_CALL_REPORT("ProWindowRefresh()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);
        break;
    case PRO_TEST_REFIT_VIEW:
        status = ProViewRefit(NULL, NULL);
        TEST_CALL_REPORT("ProViewRefit()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);

        break;
    case PRO_TEST_REFIT_VINDOW:
        status = ProWindowRefit(w_id);
        TEST_CALL_REPORT("ProWindowRefit()", "ProTestViewSet()",
            status, status != PRO_TK_NO_ERROR);

        break;

    default:
        break;
    }

    return(1);
}



/*====================================================================*\
    FUNCTION :  ProTestViewRotate()
    PURPOSE  :  Set rotated view.
\*====================================================================*/
int ProTestViewRotate(ProAppData app_data, int option)
{
    double       angle = 0.0;
    double       range[2] = { -180.0, 180.0 };
    int		 w_id;
    ProError     status;

    status = ProWindowCurrentGet(&w_id);
    TEST_CALL_REPORT("ProWindowCurrentGet()", "ProTestViewRotate()",
        status, status != PRO_TK_NO_ERROR);

    ProUtilMsgPrint("gen", "TEST %0s", "Enter an angle (-180,180): ");

    status = ProMessageDoubleRead(range, &angle);
    TEST_CALL_REPORT("ProMessageDoubleRead", "ProTestViewRotate()",
        status, status != PRO_TK_NO_ERROR);

    if (status != PRO_TK_NO_ERROR)
        return(-1);

    /*  Perform the requested rotation  */
    switch (option)
    {
    case PRO_TEST_ROTATE_VIEW_X:
        status = ProViewRotate(NULL, NULL, PRO_X_ROTATION, angle);
        TEST_CALL_REPORT("ProViewRotate", "ProTestViewRotate()",
            status, status != PRO_TK_NO_ERROR);
        break;

    case PRO_TEST_ROTATE_VIEW_Y:
        ProViewRotate(NULL, NULL, PRO_Y_ROTATION, angle);
        TEST_CALL_REPORT("ProViewRotate", "ProTestViewRotate()",
            status, status != PRO_TK_NO_ERROR);
        break;

    case PRO_TEST_ROTATE_VIEW_Z:
        ProViewRotate(NULL, NULL, PRO_Z_ROTATION, angle);
        TEST_CALL_REPORT("ProViewRotate", "ProTestViewRotate()",
            status, status != PRO_TK_NO_ERROR);
        break;

    default:
        break;
    }

    status = ProWindowClear(w_id);
    TEST_CALL_REPORT("ProWindowClear()", "ProTestViewRotate()",
        status, status != PRO_TK_NO_ERROR);
    status = ProWindowRefresh(PRO_VALUE_UNUSED);
    TEST_CALL_REPORT("ProWindowRefresh()", "ProTestViewRotate()",
        status, status != PRO_TK_NO_ERROR);

    return(1);
}


/*====================================================================*\
    FUNCTION :  ProTestViewStore()
    PURPOSE  :  Store user's view.
\*====================================================================*/
int ProTestViewStore(ProAppData app_data, int option)
{
    ProMdl    model;
    ProView   p_view;
    ProLine* view_names, * alt_names;
    ProName  menu_title, w_vname;
    wchar_t** strings, ** sel_str;
    int       num_views, i, n_sel;
    ProError  status;

    /*  Either store or retrieve a view  */
    switch (option)
    {
    case PRO_TEST_STORE_VIEW:
        ProUtilMsgPrint("gen", "TEST %0s", "Enter a view name: ");

        status = ProMessageStringRead(PRO_NAME_SIZE, w_vname);
        TEST_CALL_REPORT("ProMessageStringRead", "ProTestViewStore",
            status, status != PRO_TK_NO_ERROR);

        if (status != PRO_TK_NO_ERROR)
            return(0);

        status = ProViewStore(NULL, w_vname, &p_view);
        TEST_CALL_REPORT("ProViewStore", "ProTestViewStore",
            status, status != PRO_TK_NO_ERROR);
        break;


    case PRO_TEST_RETRIEVE_VIEW:

        status = ProMdlCurrentGet(&model);
        TEST_CALL_REPORT("ProMdlCurrentGet()", "ProTestViewStore()",
            status, status != PRO_TK_NO_ERROR);
        if (status != PRO_TK_NO_ERROR)
            return(-1);

        status = ProViewNamesGet(model, &view_names, &alt_names, &num_views);
        TEST_CALL_REPORT("ProViewNamesGet()", "ProTestViewStore()",
            status, status != PRO_TK_NO_ERROR);

        if (status != PRO_TK_NO_ERROR)
        {

            ProUtilMsgPrint("gen", "TEST %0s", "Error in view names get.");
            return(0);
        }
        else if (num_views <= 0)
        {
            ProUtilMsgPrint("gen", "TEST %0s", "No view has been stored!");
            return(0);
        }

        /* Setup select menu for view names */
        strings = (wchar_t**)calloc(num_views + 1, sizeof(wchar_t*));
        for (i = 0; i < num_views; i++) {
            strings[i] = (wchar_t*)calloc(1, sizeof(ProName));
            ProUtilWstrcpy(strings[i], view_names[i]);
        }
        strings[num_views] = (wchar_t*)calloc(1, sizeof(wchar_t));
        ProStringToWstring(strings[num_views], (char*)"");

        ProStringToWstring(menu_title, (char*)"VIEW NAMES");

        status = ProMenuStringsSelect(menu_title, strings, 1, NULL,
            &sel_str, &n_sel);
        TEST_CALL_REPORT("ProMenuStringsSelect", "ProTestViewStore()",
            status, status != PRO_TK_NO_ERROR);

        if (status != PRO_TK_NO_ERROR)
            return(0);
        else if (n_sel <= 0)
            return(0);

        status = ProViewRetrieve(NULL, sel_str[0], &p_view);
        TEST_CALL_REPORT("ProViewRetrieve", "ProTestViewStore()",
            status, status != PRO_TK_NO_ERROR);

        /* Free the memory */
        for (i = 0; i <= num_views; i++)
            free((wchar_t*)strings[i]);
        free((wchar_t**)strings);
        ProArrayFree((ProArray*)&view_names);
        ProArrayFree((ProArray*)&alt_names);

        break;

    default:
        break;
    }


    return(1);
}


/*====================================================================*\
    FUNCTION :  ProTestViewList()
    PURPOSE  :  List all stored views.
\*====================================================================*/
int ProTestViewList(ProAppData app_data, int option)
{
    ProMdl    model;
    ProView   p_view;
    ProLine* view_names, * alt_names;
    ProName   w_fname;
    char      vname[PRO_NAME_SIZE], aname[PRO_NAME_SIZE];
    char      fname[] = "view_names.txt";
    int       num_views, i;
    FILE* fp;
    ProError  status;
    ProMatrix	matrix;

    status = ProMdlCurrentGet(&model);
    TEST_CALL_REPORT("ProMdlCurrentGet()", "ProTestViewList()",
        status, status != PRO_TK_NO_ERROR);
    if (status != PRO_TK_NO_ERROR)
        return(-1);

    status = ProViewNamesGet(model, &view_names, &alt_names, &num_views);
    TEST_CALL_REPORT("ProViewNamesGet()", "ProTestViewList()",
        status, status != PRO_TK_NO_ERROR);

    if (status != PRO_TK_NO_ERROR)
    {
        ProUtilMsgPrint("gen", "TEST %0s", "Error in view names get.");
        return(0);
    }
    else if (num_views <= 0)
    {
        ProUtilMsgPrint("gen", "TEST %0s", "No view has been stored!");
        return(0);
    }


    if ((fp = PTApplsUnicodeFopen(fname, "w")) == NULL) {
        ProTKPrintf("\nThe output file [%s] cannot be opened.\n", fname);
        return(0);
    }

    if (num_views > 0)
    {
        for (i = 0; i < num_views; i++)
        {
            ProTKFprintf(fp, "View Name %d: %s\t\tAlt Name: %s\n", i,
                ProWstringToString(vname, view_names[i]),
                ProWstringToString(aname, alt_names[i]));

            status = ProViewNameToView(model, view_names[i], &p_view);
            TEST_CALL_REPORT("ProViewNameToView()", "ProTestViewList()",
                status, status != PRO_TK_NO_ERROR);

            status = ProViewMatrixGet(model, p_view, matrix);
            TEST_CALL_REPORT("ProViewNameToView()", "ProTestViewList()",
                status, status != PRO_TK_NO_ERROR);
            FPRINT3E(fp, "    matrix[0]", matrix[0]);
            FPRINT3E(fp, "    matrix[1]", matrix[1]);
            FPRINT3E(fp, "    matrix[2]", matrix[2]);
            FPRINT3E(fp, "    matrix[3]", matrix[3]);
        }
        fclose(fp);
        ProStringToWstring(w_fname, fname);
        ProInfoWindowDisplay(w_fname, NULL, NULL);
        TEST_CALL_REPORT("ProInfoWindowDisplay", "ProTestViewList()",
            status, status != PRO_TK_NO_ERROR);
    }
    else
    {
        ProTKFprintf(fp, "No view has been stored!\n");
        fclose(fp);
        ProUtilMsgPrint("gen", "TEST %0s", "No view has been stored!");
    }

    ProArrayFree((ProArray*)&view_names);
    ProArrayFree((ProArray*)&alt_names);

    return(num_views);
}


#ifndef PROE_JR_BUILD

/*====================================================================*\
    FUNCTION :  ProTestViewMatrxWrite()
    PURPOSE  :  Write view matrix to a file.
\*====================================================================*/
int ProTestViewMatrxWrite(ProAppData app_data, int option)
{
    ProMdl       model;
    ProMdlName   model_name;
    ProMdlType   model_type;
    ProCharName  filename, name;
    ProMatrix    view, window, draw;
    int	       w_id;
    double       width, height, x, y;
    FILE* out_file;
    ProError     status;

    status = ProMdlCurrentGet(&model);
    TEST_CALL_REPORT("ProMdlCurrentGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);
    if (status != PRO_TK_NO_ERROR)
        return(-1);

    status = ProMdlMdlnameGet(model, model_name);
    TEST_CALL_REPORT("ProMdlMdlnameGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);

    status = ProMdlTypeGet(model, &model_type);
    TEST_CALL_REPORT("ProMdlTypeGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);

    out_file = ProUtilGenFilePtr(model, (char*)EXT_VMTX, filename, (char*)"w");
    if (out_file == NULL)
    {
        ProTKPrintf("\nThe output file cannot be opened.\n");
        return(0);
    }


    ProTKFprintf(out_file, "\n");
    if (model_type == PRO_MDL_ASSEMBLY)
        ProTKFprintf(out_file, "\n%s%s\n", "Assembly Name: ",
            ProWstringToString(name, model_name));
    else if (model_type == PRO_MDL_PART)
        ProTKFprintf(out_file, "\n%s%s\n", "Part Name: ",
            ProWstringToString(name, model_name));

    /*  For the view matrix  */
    ProTKFprintf(out_file, "\n");
    status = ProViewMatrixGet(NULL, NULL, view);
    TEST_CALL_REPORT("ProViewMatrixGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);
    FPRINT3E(out_file, "view[0]", view[0]);
    FPRINT3E(out_file, "view[1]", view[1]);
    FPRINT3E(out_file, "view[2]", view[2]);
    FPRINT3E(out_file, "view[3]", view[3]);

    /*  For the window matrix  */
    ProTKFprintf(out_file, "\n");

    status = ProWindowCurrentGet(&w_id);
    TEST_CALL_REPORT("ProWindowCurrentGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);

    status = ProWindowSizeGet(w_id, &width, &height);
    TEST_CALL_REPORT("ProWindowSizeGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);

    status = ProWindowPositionGet(w_id, &x, &y);
    TEST_CALL_REPORT("ProWindowPositionGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);

    status = ProWindowCurrentMatrixGet(window);
    TEST_CALL_REPORT("ProWindowCurrentMatrixGet(()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);
    ProTKFprintf(out_file, "Width = %7.3f  Height = %7.3f  X = %7.3f  Y = %7.3f\n",
        width, height, x, y);

    FPRINT3E(out_file, "window[0]", window[0]);
    FPRINT3E(out_file, "window[1]", window[1]);
    FPRINT3E(out_file, "window[2]", window[2]);
    FPRINT3E(out_file, "window[3]", window[3]);

    /*  For the drawing matrix  */
    ProTKFprintf(out_file, "\n");
    status = ProViewMatrixGet(NULL, NULL, draw);
    TEST_CALL_REPORT("ProViewMatrixGet()", "ProTestViewMatrxWrite()",
        status, status != PRO_TK_NO_ERROR);
    FPRINT3E(out_file, "draw[0]", draw[0]);
    FPRINT3E(out_file, "draw[1]", draw[1]);
    FPRINT3E(out_file, "draw[2]", draw[2]);
    FPRINT3E(out_file, "draw[3]", draw[3]);

    fclose(out_file);

    return(0);
}

#endif
