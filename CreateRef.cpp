#include "CreateRef.h"
/* =============================================================== *\
	Function:  UserDatumRefs()
	Purpose:   Obtain reference surface and offset for datum
			plane creation
\* =============================================================== */
int UserDatumRefs()
{

	static wchar_t msgfil[80];
	ProError	status;
	ProSelection* ref_surf;
	int sel_num = -1, level_flag;
	double	offset_value;
	wchar_t w_level[PRO_TYPE_SIZE];
	char level[PRO_TYPE_SIZE];
	ProMdl model;
	ProMdlType p_type;
	ProStringToWstring(msgfil, (char*)"msg_ugdatum.txt");

	/* =============================================================== *\
		Prompt user for reference surface ...
	\* =============================================================== */
	status = ProMessageDisplay(msgfil, (char*)"USER Select a reference surface");
	status = ProSelect((char*)"surface", 1, NULL, NULL, NULL, NULL, &ref_surf, &sel_num);

	if (sel_num < 1)
		return status;

	/* =============================================================== *\
		... then, offset distance
	\* =============================================================== */

	status = ProMessageDisplay(msgfil, (char*)"USER Enter the offset value:");
	if ((status = ProMessageDoubleRead(NULL, &offset_value))
		!= PRO_TK_NO_ERROR)
		return(status);

	/* =============================================================== *\
		... finally, level at which datum is to be created (part vs. asm)
	\* =============================================================== */

	status = ProMdlCurrentGet(&model);
	//ERROR_CHECK("ProMdlCurrentGet", "ProDatumPlaneCreate()", status);
	status = ProMdlTypeGet(model, &p_type);
	//ERROR_CHECK("ProMdlTypeGet", "ProDatumPlaneCreate()", status);
	if (p_type == PRO_MDL_PART)
	{
		level_flag = PART;
	}
	else if (p_type == PRO_MDL_ASSEMBLY) {

		status = ProMessageDisplay(msgfil, (char*)"USER Create datum plane at part or assembly level (prt or asm):");
		status = ProMessageStringRead(PRO_TYPE_SIZE, w_level);
		//ERROR_CHECK("ProMessageStringRead()", "UserDatumRefs()", status);

		ProWstringToString(level, w_level);
		if (!strcmp(level, "prt"))
			level_flag = PART;
		else if (!strcmp(level, "asm"))
			level_flag = ASSEMBLY;
		else
			return(status);
	}
	else
		return(status);

	status = (ProError)ProDatumPlaneCreate(*ref_surf, offset_value, level_flag);
	//ERROR_CHECK("ProDatumPlaneCreate()", "UserDatumRefs()", status);

	return(status);
}
/* =============================================================== *\
	Function: ProDatumPlaneCreate()
	Purpose:  Creates a datum plane as an assembly feature at an
		offset distance from a surface on a part
\* =============================================================== */
int ProDatumPlaneCreate(ProSelection offset_surface, double offset_dist, int dtm_level)
{

	ProReference REPDEP_ref1;
	ProError	status;
	ProElement	elem_tree, elem_ftype, elem_consts, elem_offset;
	ProElement	elem_const_type, elem_offset_ref, elem_offset_dist;
	ProModelitem	surf_modelitem, model_modelitem;
	ProSelection	mdl_sel;
	ProFeature	feature;
	ProErrorlist	errors;
	ProAsmcomppath   p_cmp_path;
	ProFeatureCreateOptions* opts = 0;

	/* =============================================================== *\
		Allocate tree root element
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_FEATURE_TREE, &elem_tree);

	/* =============================================================== *\
		Allocate feature type element; add to tree root.
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_FEATURE_TYPE, &elem_ftype);
	ProElementIntegerSet(elem_ftype, PRO_FEAT_DATUM);

	ProElemtreeElementAdd(elem_tree, NULL, elem_ftype);

	/* =============================================================== *\
		Allocate constraints element; add to tree root.
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTRAINTS, &elem_consts);
	ProElemtreeElementAdd(elem_tree, NULL, elem_consts);

	/* =============================================================== *\
		Allocate constraint element; add under constraints element.
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTRAINT, &elem_offset);
	status = ProElemtreeElementAdd(elem_consts, NULL, elem_offset);

	/* =============================================================== *\
		Allocate constraint type element; add under constraint element.
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTR_TYPE, &elem_const_type);
	ProElementIntegerSet(elem_const_type, PRO_DTMPLN_OFFS);

	status = ProElemtreeElementAdd(elem_offset, NULL, elem_const_type);

	/* =============================================================== *\
		Allocate constraint ref element; add under constraint element.
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTR_REF, &elem_offset_ref);
	ProSelectionToReference(offset_surface, &REPDEP_ref1);
	ProElementReferenceSet(elem_offset_ref, REPDEP_ref1);

	status = ProElemtreeElementAdd(elem_offset, NULL, elem_offset_ref);

	/* =============================================================== *\
		Allocate ref offset value element; add under constraint element.
	\* =============================================================== */
	status = ProElementAlloc(PRO_E_DTMPLN_CONSTR_REF_OFFSET, &elem_offset_dist);
	ProElementDecimalsSet(elem_offset_dist, 4);
	ProElementDoubleSet(elem_offset_dist, offset_dist);

	status = ProElemtreeElementAdd(elem_offset, NULL, elem_offset_dist);

	/* =============================================================== *\
		Get assembly component path to part containing offset surface
	\* =============================================================== */

	status = ProSelectionAsmcomppathGet(offset_surface, &p_cmp_path);
	//ERROR_CHECK("ProSelectionAsmcomppathGet", "ProDatumPlaneCreate()", status);

	switch (dtm_level)
	{

	case ASSEMBLY:
		/* =============================================================== *\
			Obtain a ProModelitem handle to the root assembly
		\* =============================================================== */

		status = ProMdlToModelitem(p_cmp_path.owner, &model_modelitem);
		//ERROR_CHECK("ProMdlToModelitem", "ProDatumPlaneCreate()", status);

		/* =============================================================== *\
			Allocate ProSection object for root assembly
		\* =============================================================== */
		status = ProSelectionAlloc(NULL, &model_modelitem, &mdl_sel);
		//ERROR_CHECK("ProSelectionAlloc", "ProDatumPlaneCreate()", status);

		break;

	case PART:
		/* =============================================================== *\
			Obtain a ProModelitem handle to selected surface
		\* =============================================================== */

		status = ProSelectionModelitemGet(offset_surface, &surf_modelitem);
		//ERROR_CHECK("ProSelectionModelitemGet", "ProDatumPlaneCreate()", status);

		/* =============================================================== *\
			Obtain a ProModelitem to the owner of the selected surface
		\* =============================================================== */
		status = ProMdlToModelitem(surf_modelitem.owner, &model_modelitem);
		//ERROR_CHECK("ProMdlToModelitem", "ProDatumPlaneCreate()", status);

		/* =============================================================== *\
			Allocate ProSection object for part to which selected surface
			 belongs
		\* =============================================================== */

		status = ProSelectionAlloc(&p_cmp_path, &model_modelitem, &mdl_sel);
		//ERROR_CHECK("ProSelectionAlloc", "ProDatumPlaneCreate()", status);

		break;

	default:
		return(0);

	}

	/* =============================================================== *\
		Create datum plane
	\* =============================================================== */

	status = ProArrayAlloc(1, sizeof(ProFeatureCreateOptions),
		1, (ProArray*)&opts);

	opts[0] = PRO_FEAT_CR_NO_OPTS;

	status = ProFeatureWithoptionsCreate(mdl_sel, elem_tree,
		opts, PRO_REGEN_NO_FLAGS, &feature, &errors);
	//ERROR_CHECK("ProFeatureWithoptionsCreate", "ProDatumPlaneCreate()", status);

	status = ProArrayFree((ProArray*)&opts);

	status = ProElementFree(&elem_tree);
	//ERROR_CHECK("ProElementFree", "ProDatumPlaneCreate()", status);
	status = ProSelectionFree(&mdl_sel);
	//ERROR_CHECK("ProSelectionFree", "ProDatumPlaneCreate()", status);

	return(status);
}