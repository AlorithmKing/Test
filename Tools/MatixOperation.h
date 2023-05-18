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
		

		//����ĵ�ת��
		static void MYFPointTrans(double m[4][4], double p[3], double output[3]);
		//��������
		static int MYFMatrixInvert(double m[4][4], double output[4][4]);
		//������
		static void MYFMatrixCopy(double input[4][4], double output[4][4]);
		//�����һ��
		static void MatrixNormalize(ProMatrix m);
	};
	

}


