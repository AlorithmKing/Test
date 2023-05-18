#include "VisitDim.h"

/*
    Copyright (c) 2019 PTC Inc. and/or Its Subsidiary Companies. All Rights Reserved.
*/




typedef struct
{
    ProVector vector;        /* The direction that the dimension should
                    be parallel to */
    ProBoolean found;        /* Flag signalling if any matching
                    dimensions were found. */
    ProDimension dim_found;  /* May be used if visiting in an attempt
                    to locate a certain dimension */
} DimByVector;


/*==================================================================*\
FUNCTION : UserDimensionFilterByVector()
PURPOSE  : Find linear dimensions oriented parallel to vector (a filter
           action)
\*==================================================================*/
ProError UserDimensionFilterByVector(ProDimension* dim,
    ProAppData appdata)
{
    ProDimlocation dimloc;
    ProDimensiontype type;
    ProPoint3d arrow_1, arrow_2;
    int i;
    ProError status;
    ProVector dimvector;
    double dotproduct;
    DimByVector* data = (DimByVector*)appdata;

    /*------------------------------------------------------------------*\
        Continue only for linear dimensions
    \*------------------------------------------------------------------*/
    ProDimensionTypeGet(dim, &type);
    if (type != PRODIMTYPE_LINEAR)
        return (PRO_TK_CONTINUE);

    /*------------------------------------------------------------------*\
        Extract the location of the arrows of the dimension
    \*------------------------------------------------------------------*/
    status = ProDimensionLocationGet(dim, NULL, NULL, &dimloc);
    if (status != PRO_TK_NO_ERROR)
        return (PRO_TK_CONTINUE);

    ProDimlocationArrowsGet(dimloc, arrow_1, arrow_2);
    ProDimlocationFree(dimloc);

    /*------------------------------------------------------------------*\
        Construct, validate, and normalize the dimension direction vector
    \*------------------------------------------------------------------*/
    for (i = 0; i < 3; i++)
        dimvector[i] = arrow_2[i] - arrow_1[i];

    if (MYFMath::MYFVectorLength(dimvector) < EPSM6)
        return (PRO_TK_CONTINUE);

  MYFMath::MYFVectorNormalize(dimvector, dimvector);

    /*------------------------------------------------------------------*\
        Check if the angle between the vectors is 0 or 180 degrees
    \*------------------------------------------------------------------*/
    dotproduct =MYFMath::MYFVectorDot(data->vector, dimvector);

    if (fabs(fabs(dotproduct) - 1.0) < EPSM6)
    {
        data->found = PRO_B_TRUE;
        return (PRO_TK_NO_ERROR);
    }
    else
        return (PRO_TK_CONTINUE);
}

/*==================================================================*\
FUNCTION : UserDimensionShow()
PURPOSE  : Show the given dimension (a visit action)
\*==================================================================*/
ProError UserDimensionShow(ProDimension* dim,
    ProError error_status,
    ProAppData appdata)
{
    double nominal_value;
    ProAnnotation ap;
    ProDimAttachment* attachment_arr;
    ProDimSense* dsense_arr;
    ProDimOrient orient_hint;
    error_status = ProDimensionNomvalueGet(dim, &nominal_value);
    error_status = ProDimensionAttachmentsGet(dim, &ap, &attachment_arr, &dsense_arr, &orient_hint);
    error_status= ProAnnotationShow((ProAnnotation*)dim, NULL, NULL);
    return error_status;
}

/*==================================================================*\
FUNCTION : UserDimensionsByDirectionShow()
PURPOSE  : Highlight linear dimensions in the feature that are
           oriented parallel to a given vector.
\*==================================================================*/
ProError UserDimensionsByDirectionShow(ProSolid solid,
    ProFeature* feature,
    ProVector vector)
{
    DimByVector data;
    ProError status;
    ProFileName msg_file;

    ProStringToWstring(msg_file, (char*)"msg_ugfund.txt");

    memcpy(data.vector, vector, sizeof(ProVector));
    data.found = PRO_B_FALSE;

    if (feature != NULL)
    {
        /*------------------------------------------------------------------*\
            Visit all feature dimensions.
        \*------------------------------------------------------------------*/
        status = ProFeatureDimensionVisit(feature,
            UserDimensionShow,
            UserDimensionFilterByVector,
            (ProAppData)&data);
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
            &data);
    }

    /*------------------------------------------------------------------*\
       Return based on the success of the visit.
    \*------------------------------------------------------------------*/
    if (status != PRO_TK_NO_ERROR || data.found == PRO_B_FALSE)
    {
        ProMessageDisplay(msg_file, (char*)"USER %0s F",
            "No dimensions found parallel to the supplied direction.");
        return (PRO_TK_E_NOT_FOUND);
    }
    else
    {
        ProMessageDisplay(msg_file, (char*)"USER %0s F",
            "Showing dimensions parallel to the supplied direction.");

        return(PRO_TK_NO_ERROR);
    }
}

/*==================================================================*\
FUNCTION : UserDimensionsByAxisDirectionShow()
PURPOSE  : Highlight model or feature dimensions parallel to a
           selected axis.
\*==================================================================*/
ProError UserDimensionsByAxisDirectionShow()
{
    ProError status;
    ProSelection* sels;
    int n_sels = -1;
    ProFileName msg_file;
    ProSolid input_solid_ptr;
    ProFeature* input_feat_ptr;
    ProFeature feature;
    ProModelitem axis_item;
    ProAxis axis;
    ProGeomitemdata* axis_data;
    ProVector dirvector;
    int i;
    int window_id;
    ProStringToWstring(msg_file, (char*)"msg_ugfund.txt");

    /*------------------------------------------------------------------*\
      Prompt to select the context
    \*------------------------------------------------------------------*/
    ProMessageDisplay(msg_file, (char*)"USER %0s F",
        "Select the feature for locating dimensions.  <CANCEL> to locate dimensions in the current model.");

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
      Prompt to select the axis
    \*------------------------------------------------------------------*/
    ProMessageDisplay(msg_file, (char*)"USER %0s F",
        "Select the axis for orientation of the dimensions.");

    status = ProSelect((char*)"axis", 1, NULL, NULL, NULL, NULL, &sels, &n_sels);
    if (status != PRO_TK_NO_ERROR || n_sels < 1)
    {
        return (PRO_TK_USER_ABORT);
    }

    /*------------------------------------------------------------------*\
      Extract the direction vector of the axis
    \*------------------------------------------------------------------*/
    ProSelectionModelitemGet(sels[0], &axis_item);
    ProGeomitemToAxis(&axis_item, &axis);
    ProAxisDataGet(axis, &axis_data);

    for (i = 0; i < 3; i++)
        dirvector[i] = axis_data->data.p_curve_data->line.end2[i] -
        axis_data->data.p_curve_data->line.end1[i];

    MYFMath::MYFVectorNormalize(dirvector, dirvector);

    ProGeomitemdataFree(&axis_data);

    /*------------------------------------------------------------------*\
      Show the dimensions
    \*------------------------------------------------------------------*/
    UserDimensionsByDirectionShow(input_solid_ptr, input_feat_ptr, dirvector);
    ProWindowCurrentGet(&window_id);
    ProWindowActivate(window_id);
    return PRO_TK_NO_ERROR;
}

