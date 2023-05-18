#include "GtolCreate.h"
/*====================================================================*\
FUNCTION: UsrPlanePositiontolSet()
PURPOSE:  To add a position gtol to the specified surface
\*====================================================================*/
int UsrPlanePositiontolSet(
    ProSelection surface, /* The surface */
    ProVector pos, /* The position of the gtol */
    ProGeomitem* reference, /* The datum reference */
    ProAnnotationPlane* ap, /* The annotation plane */
    double tolerance) /* The tolerance value */
{
    ProError status;
    ProGtoldata gdata;
    ProGtoldataStatus gstatus;
    ProGtolleader leader, * leaders;
    ProName wname;    //wchar_t[]
    ProCharName name; //char []
    ProModelitem modelitem;
    ProGtoldatumref datumref;
    ProSelection ref;
    ProGtol gtol;
    wchar_t comment[PRO_NAME_SIZE];
    //申请公差数据空间
    ProGtoldataAlloc(reference->owner, &gdata);
   //设置几何公差类型
    ProGtoldataTypeSet(gdata, PROGTOLTYPE_POSITION, &gstatus);
    //设置公差拥有者
    ProGtoldataModelSet(gdata, reference->owner, &gstatus);
    //设置引用面
    status = ProGtoldataReferenceSet(gdata, PROGTOLRTYPE_SURF, surface, &gstatus);
   //设置引线至表面
    ProGtolleaderAlloc(PROLEADERTYPE_ARROWHEAD, surface, &leader);
    //分配引线数组空间
    ProArrayAlloc(0, sizeof(ProGtolleader), 1, (ProArray*)&leaders);
    ProArrayObjectAdd((ProArray*)&leaders, -1, 1, &leader);
    //设置引线附加位置
    ProGtoldataPlacementSet(gdata, PROGTOLPTYPE_LEADERS, NULL, leaders,
        pos, NULL, &gstatus);
    //设置注释平面
    ProGtoldataPlaneSet(gdata, ap);
   //释放指引线内存
    ProGtolleaderFree(&leader);
    /*--------------------------------------------------------------------*\
        Set up a ProSelection for the datum, and set it as the basic reference
    \*--------------------------------------------------------------------*/
    ProSelectionAlloc(NULL, reference, &ref);
    ProGtoldatumrefAlloc(ref, PROGTOLMATCOND_DEFAULT_RFS, NULL,//OK
        PROGTOLMATCOND_DEFAULT_RFS, &datumref);
    ProGtoldataGtoldatumrefSet(gdata, datumref, NULL, NULL, &gstatus);
    //释放基准内存 选择器内存
    ProGtoldatumrefFree(&datumref);
    ProSelectionFree(&ref);
    /*--------------------------------------------------------------------*\
        Set the tolerance value
    \*--------------------------------------------------------------------*/
    ProSelectionModelitemGet(surface, &modelitem);
    ProTKSprintf(name, "surf%d", modelitem.id); 
    ProStringToWstring(wname, name);
    ProGtoldataValueSet(gdata, PRO_B_TRUE, tolerance, wname, &gstatus);
    ProVector dir = { 0.0,1.0,0.0 };
   //创建几何公差
    status = ProGtolCreate(gdata, &gtol);
    ProStringToWstring(comment, (char*)"M");
    //添加附加信息
    status = ProGtolTopTextSet(&gtol, comment);
    status = ProGtolCompositeSet(&gtol, PRO_VALUE_UNUSED, (wchar_t*)"M", (wchar_t*)"A", (wchar_t*)"B", (wchar_t*)"C");
    status = ProGtolElbowlengthSet(&gtol, 10.0, dir);
    ProAnnotationShow(&gtol, NULL, NULL);
    /*--------------------------------------------------------------------*\
        Free the gtol data
    \*--------------------------------------------------------------------*/
    ProGtoldataFree(&gdata);
    ProArrayFree((ProArray*)&leaders);
    return(status == PRO_TK_NO_ERROR ? 1 : 0);
}

/*====================================================================*\
FUNCTION: UsrSurfAction()
PURPOSE:  Action function called when visiting solid surfaces to
               attach gtol to.
\*====================================================================*/
ProError GtolInitOp (
    ProSurface surface,
    ProError filt_status,
    ProAppData data)
{
    Planesdata_t* pdata = (Planesdata_t*)data;
    ProVector normal, pos;
    ProUvParam uv;
    ProSrftype stype;
    int id;
    ProModelitem modelitem;
    ProSelection sel;

    //获得模型ID
    ProSurfaceIdGet(surface, &id);

    //选择平面作为参考类型
    ProSurfaceTypeGet(surface, &stype);
    bool ret = pdata->reference.id != id;// stype != PRO_SRF_PLANE && ???
    if (ret)
        return(PRO_TK_NO_ERROR);

    uv[0] = uv[1] = 0.0;
    ProSurfaceXyzdataEval(surface, uv, pos, NULL, NULL, normal);

    //
    ///*--------------------------------------------------------------------*\
    //    Set the position of the gtol to be the point for zero UV, offset
    //    by the outward normal.
    //\*--------------------------------------------------------------------*/
    pos[0] += normal[0];
    pos[1] += normal[1];
    pos[2] += normal[2];

    //模型列表初始化
    ProModelitemInit(pdata->reference.owner, id, PRO_SURFACE, &modelitem);

    //分配内存
    ProSelectionAlloc(NULL, &modelitem, &sel);

    UsrPlanePositiontolSet(sel, pos, &pdata->reference, &pdata->ap, pdata->tolerance);

    //释放内存
    ProSelectionFree(&sel);
    return(PRO_TK_NO_ERROR);
}

//ProError FilterSurAction(ProSurface p_surface,
//    ProAppData app_data)
//{
//    int pro_id;
//    Planesdata_t* pdata = (Planesdata_t*)app_data;
//    ProSurfaceIdGet(p_surface, &pro_id);
//    if (pdata->reference.id == pro_id)
//        return PRO_TK_NO_ERROR;
//    else
//        return PRO_TK_BAD_INPUTS;
//}

/*====================================================================*\
FUNCTION: UsrPlanesTol()
PURPOSE:  Command to add a position gtol to all solid planes that are
          parallel to a selected datum. Makes the selected datum
          into a gtol reference if required.
\*====================================================================*/
int UsrPlanesTol()
{
    ProError status;
    ProSelection  sel;
    int n_sel;
    //ProGeomitem datum;
    ProName wname;
    /*  ProBoolean ref_datum, is_in_dim;
      ProDimension dim;*/
    Planesdata_t data;
    ProUvParam uv;
    ProSurface surface;
    ProFileName msgfil;
    //ProAnnotationPlane ap;
    //ProVector normal;
    ProModelitem ap_datum;
    //ProSurface ap_surf;
    ProGeomitemdata* gdata;
    int window_id;
    ProName name;
    ProMdl model;
    ProMdlCurrentGet(&model);
    ProView p_view;
    ProStringToWstring(msgfil, (char*)"msg_uggtol.txt");
    ProModelitemInit(model, 66, PRO_SURFACE, &ap_datum);

    /*--------------------------------------------------------------------*\
        Select the datum
    \*--------------------------------------------------------------------*/
    ProMessageDisplay(msgfil,
        (char*)"USER Select a datum plane for gtol references");

  /*  if (ProSelect((char*)"sldface", 1, NULL, NULL, NULL, NULL, &sel, &n_sel)
        != PRO_TK_NO_ERROR || n_sel < 0)
        return(0);*/
    status = ProSelectionAlloc(NULL, &ap_datum,&sel);
    //ProSelectionModelitemGet(sel[0], &datum);

    //转变为指定类型的参考面：param：PRO_SURFACE
    ProModelitemInit(ap_datum.owner, ap_datum.id,
        PRO_SURFACE, &ap_datum);
    ProModelitemNameGet(&ap_datum, wname);

#if 0
    // 判断是否为参考面
    status = ProGeomitemIsGtolref(&datum, &ref_datum, &is_in_dim, &dim);
    if (ref_datum)
        ProMessageDisplay(msgfil, "USER %0w is already a reference datum",
            wname);
    else
    {
        ProMessageDisplay(msgfil, "USER %0w is not a reference datum."
            "Do you wish to set it (yes/no)?|||yes", wname);
        //ref_datum = (ProBoolean)ProUtilYesnoGet("YES");
        //if (!ref_datum)
        //    return(0);
        ProGeomitemSetdatumSet(&datum, NULL);
    }
#endif
    /*--------------------------------------------------------------------*\
        Remember the reference
    \*--------------------------------------------------------------------*/
    memcpy(&data.reference, &ap_datum, sizeof(ProGeomitem));

    //平面法向量初始化 平面验证
    ProSurfaceInit(ap_datum.owner, ap_datum.id, &surface);
    uv[0] = uv[1] = 0.0;
    ProSurfaceXyzdataEval(surface, uv, NULL, NULL, NULL, data.normal);
    //创建注释平面
    ProStringToWstring(name, (char*)"FRONT");
    //status = ProViewStore(model, name, &p_view);
    status = ProViewRetrieve(model, name, &p_view);
    status = ProViewNameGet(p_view, name);
    status = ProAnnotationplaneFromViewCreate((ProSolid)model,p_view, &data.ap);
    //ProMessageDisplay(msgfil, (char*)"USER Select the annotation plane to use");
    //if (ProSelect((char*)"pntsrf", 1, NULL, NULL, NULL, NULL, &sel, &n_sel))
    //    return (0);

    ////为注释平面创建面法向量----------可修改为鼠标点击的任意一点
    //status = ProSelectionModelitemGet(sel[0], &ap_datum);
    //status = ProGeomitemToSurface(&ap_datum, &ap_surf);
    //status = ProSurfaceDataGet(ap_surf, &gdata);
    //memcpy(normal, gdata->data.p_surface_data->srf_shape.plane.e3, sizeof(ProVector));

    //ProGeomitemdataFree(&gdata);

    //status = ProAnnotationplaneCreate(sel[0], normal, &ap);
    //memcpy(&data.ap, &ap, sizeof(ProAnnotationPlane));

    //输入公差值
    data.tolerance = 0.01;
   // ProMessageDisplay(msgfil, (char*)"USER Enter the tolerance value|||0.1");
   // status = ProMessageDoubleRead(NULL, &data.tolerance);
   // if (status == PRO_TK_MSG_USER_QUIT)
   //     return(0);
   // if (status != PRO_TK_NO_ERROR)
   //     data.tolerance = 0.1;


    GtolInitOp(surface, status, &data);
    ProWindowCurrentGet(&window_id);
    ProWindowActivate(window_id);
    //提高屏幕刷新率
    ProDisplistInvalidate(ap_datum.owner);
    ProSelectionFree(&sel);
    ProWindowRepaint(PRO_VALUE_UNUSED);

    return(1);
}