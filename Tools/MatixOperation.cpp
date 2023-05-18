#include "ProHeader.h"
#include "MatixOperation.h"

//ProError ProCylinderAxisdirection(ProPoint3d start, ProPoint3d end, ProVector direction)
//{
//	double height;
//	ProCylinderHeight(start, end, &height);
//	direction[0] = (double)((end[0] - start[0]) / height);
//	direction[1] = (double)((end[1] - start[1]) / height);
//	direction[2] = (double)((end[2] - start[2]) / height);
//	return PRO_TK_NO_ERROR;
//}
//
//ProError ProCylinderHeight(ProPoint3d start, ProPoint3d end, double* height)
//{
//	*height = sqrt(
//		(end[0] - start[0]) * (end[0] - start[0]) + (end[1] - start[1]) * (end[1] - start[1]) + (end[2] - start[2]) * (
//			end[2] - start[2]));
//
//	return PRO_TK_NO_ERROR;
//}

void MYFMatrix::MYFPointTrans(double m[4][4], double p[3], double output[3])
{

	if (m == NULL)
	{
		MYFMath::MYFVectorCopy(p, output);

	}
	else
	{
		output[0] = m[3][0]+p[0];
		output[1] = m[3][1]+p[1];
		output[2] = m[3][2]+p[2];
	}

}

void MYF::MYFMatrix::MYFMatrixCopy(double input[4][4], double output[4][4])
{
	int i, j;

	if (input == NULL)
	{
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				output[i][j] = identity_matrix[i][j];
	}
	else
	{
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				output[i][j] = input[i][j];
	}
}

void MYF::MYFMatrix::MatrixNormalize(ProMatrix m)
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

int MYF::MYFMatrix::MYFMatrixInvert(double m[4][4], double output[4][4])
{
	double vec[3], scale_sq, inv_sq_scale;
	int i, j;

	if (m == NULL)
	{
		MYFMatrixCopy(NULL, output);
		return(1);
	}
	/*--------------------------------------------------------------------*\
	Obtain the matrix scale
\*--------------------------------------------------------------------*/
	vec[0] = m[0][0];
	vec[1] = m[0][1];
	vec[2] = m[0][2];
	scale_sq = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];

	/*--------------------------------------------------------------------*\
		Check whether there is an inverse, and if not, return 0
	\*--------------------------------------------------------------------*/
	if (scale_sq < (.000000001 * .000000001))
		return(0);

	/*--------------------------------------------------------------------*\
		Need the inverse scale squared
	\*--------------------------------------------------------------------*/
	inv_sq_scale = 1.0 / scale_sq;

	/*--------------------------------------------------------------------*\
		The orientation vectors
	\*--------------------------------------------------------------------*/
	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 3; i++)
			output[j][i] = m[i][j] * inv_sq_scale;
		output[j][3] = 0.0;
	}

	/*--------------------------------------------------------------------*\
		The shift vectors
	\*--------------------------------------------------------------------*/
	for (i = 0; i < 3; i++)
	{
		output[3][i] = 0.0;
		for (j = 0; j < 3; j++)
			output[3][i] -= m[i][j] * m[3][j] * inv_sq_scale;
	}
	output[3][3] = 1.0;

	return(1);
}


