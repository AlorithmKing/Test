#pragma once
#include"MYFMath.h"
using namespace MYF;
namespace MYF
{
	static double identity_matrix[4][4] = { {1.0, 0.0, 0.0, 0.0},
					{0.0, 1.0, 0.0, 0.0},
					{0.0, 0.0, 1.0, 0.0},
					{0.0, 0.0, 0.0, 1.0} };
	class MYFMatrix
	{
	public:
		

		//矩阵的点转换
		static void MYFPointTrans(double m[4][4], double p[3], double output[3]);
		//矩阵求逆
		static int MYFMatrixInvert(double m[4][4], double output[4][4]);
		//矩阵复制
		static void MYFMatrixCopy(double input[4][4], double output[4][4]);
		//矩阵归一化
		static void MatrixNormalize(ProMatrix m);
	};
	

}


