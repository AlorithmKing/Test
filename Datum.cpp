#include "Datum.h"

//ProName name,int id
ProError TagDatumLabel()
{
	ProError status;
	ProModelitem annotation;
	ProMdl model;
	ProAnnotationPlane ap;
	int m_sel = 0;
	ProSelection x_sel;
	wchar_t w_symbol[2] = { 'C','\0' };//不能动  否则 stack around the variable 'w_symbol' was corrupted
	int window_id;
	ProView p_view;
	ProName name;
	FILE* fp;
	ProModelitem surf_item;
	ProSurfaceAppearanceProps appearance_properties;
	//ProSurface surface;
	fp = PTApplsUnicodeFopen("text/log/ReportInfo.txt", "w");//一定能打开 或者假如不存在就自动创建
	//获取模型
	ProMdlCurrentGet(&model);
	status = ProModelitemInit(model, 75, PRO_SURFACE, &annotation);
	//选择参考面
	status = ProSelectionAlloc(NULL, &annotation, &x_sel);
	//ProSelect((char*)"surface", -1, NULL, NULL, NULL, NULL, &x_sel, &m_sel);
	//status = ProSelectionModelitemGet(x_sel[0], &annotation);
	//转变为指定类型的参考面：param：PRO_SURFACE
	ProModelitemInit(annotation.owner, annotation.id,
		PRO_SURFACE, &annotation);
	ProModelitemInit(model, 77, PRO_SURFACE, &surf_item);
	//ProSurfaceInit(model, 75, &surface);
	status = ProSurfaceAppearancepropsGet(&surf_item,&appearance_properties);
	//ProGeomitemToSurface(&annotation, &surface);
	//status = ProSurfaceDataGet(surface, &gdata);
	//memcpy(normal, gdata->data.p_surface_data->srf_shape.plane.e3, sizeof(ProVector));//
	//ProGeomitemdataFree(&gdata);
	//创建注释平面
	ProStringToWstring(name, (char*)"FRONT");
	//status = ProViewStore(model,name,&p_view);
	status = ProViewRetrieve(model, name, &p_view);
	if (p_view == NULL || status != PRO_TK_NO_ERROR)
	{
		ProTKFprintf(fp, "View is NULL!");
		return status;
	}
	status = ProAnnotationplaneFromViewCreate((ProSolid)model, p_view, &ap);
	//status = ProAnnotationplaneCreate(x_sel[0], normal, &ap);
	//ProLine view_name;
	//status = ProAnnotationplaneViewnameGet(&ap, &view_name);
	//获取点
	//ProMouseButton button;
	//ProPoint3d annotation_point;
	//ProMousePickGet(PRO_LEFT_BUTTON,&button, annotation_point);
	//ProSelectionPoint3dGet(*x_sel, annotation_point);
	//datum_target
	//ProDtlsyminst p_datum_target;
	//status = ProMdlDatumTargetCreate(model, PRO_DATUM_TARGET_RECTANGLE, &plane,x_sel,annotation_point,&p_datum_target);
	ProSetDatumTag r_dfs;
	if (status != PRO_TK_NO_ERROR || &ap == NULL)
	{
		ProTKFprintf(fp, "Annotation create failed!");
		return status;
	}
	status = ProMdlSetdatumtagCreate(model, x_sel, &ap, &w_symbol[0], &r_dfs);
	//注释平面的参数获取
	ProAnnotationPlaneType type;
	status = ProAnnotationplaneTypeGet(&ap, &type);
	status = ProSelectionHighlight(x_sel, PRO_COLOR_HIGHLITE);
	//status = ProSetdatumtagAttachmentSet(&r_dfs, NULL);
	ProBoolean is_shown;
	status = ProAnnotationShow(&r_dfs, NULL, NULL);//  PRO_TK_INVALID_ITEM	
	ProAnnotationIsShown(&r_dfs, NULL, &is_shown);
	if (is_shown == PRO_B_FALSE)
		ProTKFprintf(fp, "Annotation can't be shown!");

	ProWindowCurrentGet(&window_id);
	ProWindowActivate(window_id);
	ProDisplistInvalidate(model);
	ProWindowRepaint(PRO_VALUE_UNUSED);
	if (fp != NULL)
		fclose(fp);
	ProSelectionFree(&x_sel);
	
	return status;
}

ProError Annotation()
{
	ProError status;
	ProMdl model;
	ProModelitem item;
	ProMdlCurrentGet(&model);
	ProMdlToModelitem(model, &item);
	ProAnnotationPlane gtolitem;
	ProName name;
	int n_sel = 0;
	int window_id;
	ProSelection* p_sel;
	ProView p_view;
	ProMatrix matrix;
	/*ProSelect((char*)"part", -1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
	status = ProSelectionModelitemGet(p_sel[0],&item);*/
	ProStringToWstring(name, (char*)"FRONT");
	//status = ProViewStore(model, name, &p_view);
	status = ProViewRetrieve(model, name, &p_view);
	status = ProViewNameGet(p_view, name);
	//status = ProSelectionViewGet(p_sel[0],&p_view);
	//status = ProAnnotationfeatCreate(p_sel[0], PRO_B_TRUE, &feature);
	//status = ProViewFromModelitemGet(&item, &p_view);
	status = ProViewMatrixGet(model, p_view, matrix);
	status = ProAnnotationplaneFromViewCreate((ProSolid)model, p_view, &gtolitem);
	ProWindowCurrentGet(&window_id);
	ProWindowActivate(window_id);
	return status;
}
ProError TestAsm()
{
	return PRO_TK_NO_ERROR;
}

ProBoolean IsDatum(ProSolid solid, ProSurface surface)
{
	ProError status;
	ProBoolean is_datum_plane;
	status = ProSurfaceIsDatumPlane(solid, surface, &is_datum_plane);
	return is_datum_plane;
}

//void DimensionVisit()
//{
//	ProError status;
//	ProMdl model;
//	ProMdlCurrentGet(&model);
//	status = ProSolidDimensionVisit((ProSolid)model,PRO_B_TRUE,DimensionVisit,NULL,);
//}