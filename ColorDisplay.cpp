#include "ColorDisplay.h"
ProError UserAdjustHalftone(char* dummy, int lighter)
{
    ProColormap colors;
    ProError err;
    err = ProColormapGet(PRO_COLOR_HALF_TONE, &colors);
    //ERROR_CHECK("UserAdjustHalftone", "ProColormapGet", err);

    if (lighter)
    {
        colors.red += 20;
        colors.green += 20;
        colors.blue += 20;
    }
    else
    {
        colors.red -= 20;
        colors.green -= 20;
        colors.blue -= 20;
    }

    err = ProColormapSet(PRO_COLOR_HALF_TONE, &colors);
    //ERROR_CHECK("UserAdjustHalftone", "ProColormapSet", err);

    err = ProWindowRefresh(-1);
    //ERROR_CHECK("UserAdjustHalftone", "ProWindowRefresh", err);
    return err;
}

ProError UserDrawYellow()
{
    ProColor yellow;
    ProColor old_g_color, old_t_color;
    ProError status;
    ProFileName msgfil;

    ProStringToWstring(msgfil, (char*)"msg_uggraph.txt");

    yellow.method = PRO_COLOR_METHOD_RGB;
    yellow.value.map.red = 1.0;
    yellow.value.map.green = 1.0;
    yellow.value.map.blue = 0.0;

    status = ProGraphicsColorModify(&yellow, &old_g_color);
    //ERROR_CHECK("UserDrawYellow", "ProGraphicsColorModify", status);

    status = ProTextColorModify(&yellow, &old_t_color);
    //ERROR_CHECK("UserDrawYellow", "ProTextColorModify", status);

    /* In a typical implementation, the application would draw graphics
       here, and then reset the color back to the previous color.

       For this example: users should choose one of the other pt_userguide menu
       buttons to  observe the results of this change. */

    ProMessageDisplay(msgfil, (char*)"USER Color set to yellow");

    return status;
}

ProError UserDrawWithDatumAxisColor()
{
    ProColor dtm_color;
    ProColor old_g_color, old_t_color;
    ProError status;
    ProFileName msgfil;

    ProStringToWstring(msgfil, (char*)"msg_uggraph.txt");

    dtm_color.method = PRO_COLOR_METHOD_TYPE;

    status = ProColorByTypeGet(PRO_DISP_DTM_AXIS, &dtm_color.value.type);
    //ERROR_CHECK("UserDrawWithDatumAxisColor", "ProColorByTypeGet", status);

    status = ProGraphicsColorModify(&dtm_color, &old_g_color);
    //ERROR_CHECK("UserDrawWithDatumAxisColor", "ProGraphicsColorModify", status);

    status = ProTextColorModify(&dtm_color, &old_t_color);
    //ERROR_CHECK("UserDrawWithDatumAxisColor", "ProTextColorModify", status);

    /* In a typical implementation, the application would draw graphics
       here, and then reset the color back to the previous color.

       For this example: users should choose one of the other pt_userguide menu
       buttons to  observe the results of this change. */

    ProMessageDisplay(msgfil, (char*)"USER Color set to datum axis");

    return status;
}

ProError UserDrawDefaults()
{
    ProColor default_color;
    ProColor old_g_color, old_t_color;
    ProError status;
    ProFileName msgfil;

    ProStringToWstring(msgfil, (char*)"msg_uggraph.txt");

    default_color.method = PRO_COLOR_METHOD_DEFAULT;

    status = ProGraphicsColorModify(&default_color, &old_g_color);
    //ERROR_CHECK("UserDrawDefaults", "ProGraphicsColorModify", status);

    status = ProTextColorModify(&default_color, &old_t_color);
    //ERROR_CHECK("UserDrawDefaults", "ProTextColorModify", status);

    /* In a typical implementation, the application would draw graphics
       here, and then reset the color back to the previous color.

       For this example: users should choose one of the other pt_userguide menu
       buttons to  observe the results of this change. */

    ProMessageDisplay(msgfil, (char*)"USER Color set to defaults");

    return status;
}
