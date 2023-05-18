#include"viewsave.h"
/*---------------------- Function Prototypes -------------------------*/


/*=====================================================================*\
    Function to print a ProMatrix
\*=====================================================================*/
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


/*=====================================================================*\
    Function to normalize a 4 x 4 transformation matrix
\*=====================================================================*/
void UserMatrixNormalize(
    ProMatrix m
)
{
    int row, col;
    double scale;

    /*---------------------------------------------------------------------*\
        Get the scaling factor
    \*---------------------------------------------------------------------*/
    scale = sqrt(m[0][0] * m[0][0] +
        m[0][1] * m[0][1] +
        m[0][2] * m[0][2]);

    /*---------------------------------------------------------------------*\
        Remove the scaling
    \*---------------------------------------------------------------------*/
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            m[row][col] /= scale;

    /*---------------------------------------------------------------------*\
        Remove the shift
    \*---------------------------------------------------------------------*/
    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0; 

  

}


/*=====================================================================*\
    Function to store three orthogonal views called FRONT, SIDE, and TOP
\*=====================================================================*/
ProError UserViews()
{
    ProMatrix vmatrix, matrix;
    ProName name;
    ProMode mode;
    ProView dummy_view;

    int i, j;
    ProError err;
    FILE* fp;

    /*---------------------------------------------------------------------*\
        This test should only be run in part or assembly mode
    \*---------------------------------------------------------------------*/
    err = ProModeCurrentGet(&mode);
    if (mode != PRO_PART && mode != PRO_ASSEMBLY)
        return(0);
    /*---------------------------------------------------------------------*\
        set up to write out results (for verification)
    \*---------------------------------------------------------------------*/

    fp = PTApplsUnicodeFopen("D:/VS2022Project/Test/view.dat", "w");
    if(fp== NULL)
		return(0);
    /*---------------------------------------------------------------------*\
        Remember the current view matrix, and normalize it
    \*---------------------------------------------------------------------*/
    err = ProViewMatrixGet(NULL, NULL, vmatrix);
    UserMatrixPrint(fp, "vmatrix before normalization", vmatrix);

    UserMatrixNormalize(vmatrix);
    UserMatrixPrint(fp, "vmatrix after normalization", vmatrix);


    /*---------------------------------------------------------------------*\
        Store the current view (so we can recover after picking the following)
    \*---------------------------------------------------------------------*/
    ProStringToWstring(name, "ORIGINAL");
    err = ProViewStore(NULL, name, &dummy_view);
  
    /*---------------------------------------------------------------------*\
        Store the FRONT view (x=x,y=y - unitary view matrix)
    \*---------------------------------------------------------------------*/
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            matrix[i][j] = 0;
    matrix[3][3] = 1;
    matrix[0][0] = matrix[1][1] = matrix[2][2] = 1;

    err = ProViewMatrixSet(NULL, NULL, matrix);

    UserMatrixPrint(fp, "FRONT", matrix);
    ProStringToWstring(name, "FRONT");
    err = ProViewStore(NULL, name, &dummy_view);


    /*---------------------------------------------------------------------*\
        Store the SIDE view (x=y,y=z)
    \*---------------------------------------------------------------------*/
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            matrix[i][j] = 0;
    matrix[3][3] = 1;
    matrix[0][2] = matrix[1][0] = matrix[2][1] = 1;

    err = ProViewMatrixSet(NULL, NULL, matrix);

    UserMatrixPrint(fp, "SIDE", matrix);
    ProStringToWstring(name, "SIDE");


    /*---------------------------------------------------------------------*\
        Store the TOP view (x=z,y=x)
    \*---------------------------------------------------------------------*/
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            matrix[i][j] = 0;
    matrix[3][3] = 1;
    matrix[0][1] = matrix[1][2] = matrix[2][0] = 1;

    err = ProViewMatrixSet(NULL, NULL, matrix);

    UserMatrixPrint(fp, "TOP", matrix);
    ProStringToWstring(name, "TOP");
    err = ProViewStore(NULL, name, &dummy_view);

    /*---------------------------------------------------------------------*\
        Reset the view matrix
    \*---------------------------------------------------------------------*/
    ProViewMatrixSet(NULL, NULL, vmatrix);

    if (fp != NULL)
        fclose(fp);
    return err;
}

FILE* PTApplsUnicodeFopen(const char* filename, const char* mode)
{
    FILE* handle;
    wchar_t wFilename[256];
    wchar_t wmode[5];
    // Convert filename to wide character format
    swprintf(wFilename, 256, L"%hs", filename);
    swprintf(wmode, 5, L"%hs", mode);
    // Open file in Unicode mode
    handle = _wfopen(wFilename, wmode);

    return handle;
}

