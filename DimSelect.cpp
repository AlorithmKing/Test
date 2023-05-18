#include "DimSelect.h"


//typedef struct
//{
//    ProVector vector;        /* The direction that the dimension should
//                    be parallel to */
//    ProBoolean found;        /* Flag signalling if any matching
//                    dimensions were found. */
//    ProDimension dim_found;  /* May be used if visiting in an attempt
//                    to locate a certain dimension */
//} DimByVector;




ProError UserDimensionShow(ProDimension* dim,
	ProError error_status,
	ProAppData appdata)
{
	double nominal_value;
	error_status = ProDimensionNomvalueGet(dim, &nominal_value);
	error_status = ProAnnotationShow((ProAnnotation*)dim, NULL, NULL);
	return error_status;
}


ProError UserDimensionsByDirectionShow(ProSolid solid,
	ProFeature* feature)
{
	ProError status;

	if (feature != NULL)
	{
		/*------------------------------------------------------------------*\
			Visit all feature dimensions.
		\*------------------------------------------------------------------*/
		status = ProFeatureDimensionVisit(feature,
			UserDimensionShow,
			NULL,
			NULL);
	}
	else
	{
		/*------------------------------------------------------------------*\
			Visit all model dimensions.
		\*------------------------------------------------------------------*/
		status = ProSolidDimensionVisit(solid,
			PRO_B_FALSE,
			UserDimensionShow,
			NULL,
			NULL);
	}

	/*------------------------------------------------------------------*\
	   Return based on the success of the visit.
	\*------------------------------------------------------------------*/
	if (status != PRO_TK_NO_ERROR)
		return (PRO_TK_E_NOT_FOUND);
	else
		return(PRO_TK_NO_ERROR);
}

ProError UserDimensionsBySelectShow()
{
	ProError status;
	ProSelection* sels;
	int n_sels = -1;
	ProSolid input_solid_ptr;
	ProFeature* input_feat_ptr;
	ProFeature feature;
	int window_id;
	status = ProSelect((char*)"feature", 1, NULL, NULL, NULL, NULL,
		&sels, &n_sels);
	if (status == PRO_TK_USER_ABORT)
	{
		ProMdlCurrentGet((ProMdl*)&input_solid_ptr);
		input_feat_ptr = NULL;
	}
	else if (status != PRO_TK_NO_ERROR || n_sels < 1)
	{
		return (PRO_TK_USER_ABORT);
	}
	else
	{
		ProSelectionModelitemGet(sels[0], &feature);

		input_solid_ptr = NULL;
		input_feat_ptr = &feature;
	}
	/*------------------------------------------------------------------*\
	  Show the dimensions
	\*------------------------------------------------------------------*/
	UserDimensionsByDirectionShow(input_solid_ptr, input_feat_ptr);
	ProWindowCurrentGet(&window_id);
	ProWindowActivate(window_id);
	return PRO_TK_NO_ERROR;
}

void MeasureTest()
{
	ProError status;
	double distance;
	ProSelection* p_sel;
	int n_sel = 0;
	ProAnnotation ap;
	ProSurface surface;
	ProGeomitem annotation;
	ProGeomitemdata* gdata;
	ProVector normal;
	ProMdl model;
	ProDimension dimension;
	ProMdlCurrentGet(&model);
	ProSelect((char*)"surface", -1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
	status = ProGeomitemDistanceEval(p_sel[0], p_sel[1], &distance);
	status = ProModelitemInit(annotation.owner, annotation.id,
		PRO_SURFACE, &annotation);
	ProGeomitemToSurface(&annotation, &surface);
	status = ProSurfaceDataGet(surface, &gdata);
	memcpy(normal, gdata->data.p_surface_data->srf_shape.plane.e3, sizeof(ProVector));
	ProGeomitemdataFree(&gdata);
	//创建注释平面
	status = ProAnnotationplaneCreate(p_sel[0], normal, &ap);
	status = ProDimensionCreate((ProSolid)model, PRO_DIMENSION, &ap, (ProDimAttachment*)p_sel, NULL, PRO_DIM_ORNT_NORMAL, NULL, &dimension);


}

void DimensionTest()
{
	ProMdl model;               /* current model */
	ProSelection* p_sel_feat;   /* selected feature */
	ProSelection* p_sel_dim;    /* selected dimension */
	ProModelitem dim_mdlitem;   /* dimension Modelitem */
	int n_sel_feat = -1;             /* no. of selected features */
	int n_sel_dim = -1;
	ProError err;
	int window_id;
	ProAnnotation ap;
	ProDimAttachment* attachment_arr=NULL;
	//using ProDimAttachment = ProSelection [2];
	
	ProDimSense* dsense_arr;
	ProDimOrient orient_hint = PRO_DIM_ORNT_NONE;
	ProGeomitemdata* gdata;
	ProName view_name;
	ProMdlName modelName;
	ProMdlExtension modelExtension;
	ProCharLine type;
	ProSolid p_handle=NULL;
	ProMdlCurrentGet(&model);
	err = ProMdlMdlnameGet(model, modelName);
	err = ProMdlExtensionGet(model, modelExtension);
	ProWstringToString(type, modelExtension);
	//Selection and dsense
	int n_sels = 0;
	ProArrayAlloc(2, sizeof(ProDimSense), 1, (ProArray*)&dsense_arr);
	dsense_arr->type = PRO_DIM_SNS_TYP_NONE;
	dsense_arr->orient_hint = PRO_DIM_ORNT_NONE;
	dsense_arr->sense = 0;
	dsense_arr->angle_sense.is_first = PRO_B_FALSE;
	dsense_arr->angle_sense.pic_vec_dir = PRO_B_FALSE;
	dsense_arr->angle_sense.should_flip = PRO_B_FALSE;
	// Attachment 
	ProArrayAlloc(2, sizeof(ProSelection), 2, (ProArray*)attachment_arr);
	ProSelect((char*)"edge,axis", -1, NULL, NULL, NULL, NULL, (ProSelection**)&attachment_arr, &n_sels);
	(*attachment_arr)[1] = NULL;
	//memset(attachment_arr[1], NULL, sizeof(ProSelection));
	ProView p_view;
	ProStringToWstring(view_name, (char*)"FRONT");
	//if (strncmp(type, "PRT", 3) == 0)
	//{
	//	
	//	
	//	

	//}
	if (strncmp(type, "ASM", 3) == 0)
	{
		ProLine Lname;
		ProStringToWstring(Lname, (char*)"TOP");
		err = ProViewStore(model, Lname, &p_view);
		ProStringToWstring(modelName, (char*)"PART1");
		err = ProSolidInit(modelName, PRO_PART, &p_handle);
		if (err != PRO_TK_NO_ERROR)
			return;
	}
	err = ProViewRetrieve(model, view_name, &p_view);
	//获取矩阵
	ProMatrix f_matrix;
	err = ProViewMatrixGet(model, p_view, f_matrix);
	FILE* fp = PTApplsUnicodeFopen("D:/VS2022Project/Test/view.dat", "w");
	if(fp)
	{
		UserMatrixPrint(fp, (char*)"Front_view_matrix", f_matrix);
		fclose(fp);
	}
	err = ProAnnotationplaneFromViewCreate((ProSolid)model, p_view, &ap);
#if 0
	MYFMath::MYFVectorDiff(gdata->data.p_curve_data->line.end2, gdata->data.p_curve_data->line.end1, normal);
	memcpy(normal, gdata->data.p_csys_data->z_vector, sizeof(ProVector));
	ProGeomitemdataFree(&gdata);
	ProView view;
	err = ProSelectionViewGet(attachment_arr[0], &view);
	err = ProDimensionPlaneGet((ProDimension*)&dim_mdlitem, &ap);
	err = ProAnnotationplaneCreate(attachment_arr[2], normal, &ap);
	err = ProAnnotationplaneFromViewCreate((ProSolid)model, view, &ap);
	err = ProDimensionLocationGet((ProDimension*)&dim_mdlitem, NULL, NULL, &data);
	err = ProDimlocationArrowsGet(data, arrow_1, arrow_2);
	err = ProDimlocationWitnesslinesGet(data, witness_line_1, witness_line_2);
	if (ProSelect((char*)"dimension", -1, NULL, NULL, NULL, NULL,
		&p_sel_dim, &n_sel_dim) != PRO_TK_NO_ERROR)
	{
		return;
	}
	err = ProSelectionModelitemGet(p_sel_dim[0], &dim_mdlitem);
	err = ProDimensionAttachmentsGet(&dim_mdlitem, &ap, (ProDimAttachment**)&attachment_arr, &dsense_arr, &orient_hint);
#endif
	ProPoint3d location;
	ProMouseButton buttion_press= PRO_LEFT_BUTTON;
	err = ProMousePickGet(PRO_LEFT_BUTTON, &buttion_press, location);
	ProDimension dimension;
	// PRO_TK_BAD_INPUTS	- One or more of the input arguments are invalid.
	//PRO_TK_BAD_DIM_ATTACH - A dimension could not be created with the attachments and sense specified.

	//创建尺寸对象
	err = ProDimensionCreate((ProSolid)model, PRO_DIMENSION, &ap, attachment_arr, dsense_arr, orient_hint, location, &dimension);
	//设置尺寸值 
	ProWindowCurrentGet(&window_id);
	ProWindowActivate(window_id);
	//显示尺寸
	if (err == PRO_TK_NO_ERROR)
	{
		ProDimensionValueSet(&dimension, 200);
		err = ProAnnotationShow((ProAnnotation*)&dimension, NULL, NULL);
	}
	else
		return;
	//ProSelectionUnhighlight(*p_sel_dim);
	ProArrayFree((ProArray*) & attachment_arr);
	ProSelectionUnhighlight((ProSelection)attachment_arr);
}
void UserMatrixPrint(
	FILE* f,
	char* s,
	ProMatrix m
)
{
	int i, j;

	if (f != NULL)
	{
		ProTKFprintf(f, "%s\n", s);
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				ProTKFprintf(f, "%1d %1d %10.4f\n", i, j, m[i][j]);
	}
}


void TestAsm()
{
	ProMdl model;
	ProError err;
	ProView p_view;
	ProName name;
	ProLine Lname;
	ProSelection* p_sel;
	int n_sel = 0;
	int window_id;
	ProModelitem item;
	ProMdlCurrentGet(&model);
	
	ProStringToWstring(name, (char*)"FRONT");
	ProStringToWstring(Lname, (char*)"FRONT");
	err = ProViewStore(model, Lname, &p_view);
	err = ProViewRetrieve(model, name, &p_view);
	//获取矩阵
	ProMatrix f_matrix;
	err = ProViewMatrixGet(model, p_view, f_matrix);
	FILE* fp = PTApplsUnicodeFopen("D:/VS2022Project/Test/view.dat", "w");
	if (fp)
	{
		UserMatrixPrint(fp, (char*)"Front_view_matrix", f_matrix);
		fclose(fp);
	}
	//err = ProSelect((char*)"prt_or_asm", -1, NULL, NULL, NULL, NULL, &p_sel, &n_sel);
	//ProSelectionModelitemGet(p_sel[0], &item);
	//err = ProViewRetrieve(item.owner, name, &p_view);

	ProWindowCurrentGet(&window_id);
	ProWindowActivate(window_id);
}



