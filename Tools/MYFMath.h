#pragma once
#include"ProHeader.h"
#ifdef PI
#undef PI
#endif
#define PRO_UTIL_ALMOST_ZERO .000000001
#define PI          3.14159265358979323846
#define PID2        1.57079632679489661923
#define TWOPI                 (PI + PI)
#define EPSM6                 1.0e-6
#define EPSM10                1.0e-10
namespace MYF
{
	class MYFMath
	{
	public:
		MYFMath() = delete;
		~MYFMath() = delete;
		MYFMath(const MYFMath&) = delete;
		MYFMath& operator=(const MYFMath&) = delete;
		//��������
		static double* MYFVectorDiff(double start[3], double end[3], double direction[3]);
		//������ģ
		static double MYFVectorLength(double vector[3]);
		//�����ĵ�λ��
		static double* MYFVectorScale(double len, double input[3], double output[3]);
		//��λ����
		static double* MYFVectorNormalize(double input[3], double output[3]);
		//��������
		static void MYFVectorCopy(double from[3], double to[3]);
		//�������
		static double* MYFVectorCross(double product1[3], double product2[3], double output[3]);
		//�������
		static double MYFVectorDot(double product1[3], double product2[3]);
		//�㵽ֱ�ߵľ���
		static double MYFPointToLineDistance(double point[3], double start[3], double end[3]);
		//line1��line2�ļн�
		static double* MYFVectorsLincom(double scalar_a, double vector_a[3], double scalar_b, double vector_b[3], double result[3]);
		//�㵽��ľ���
		static double MYFPointsDist(double p1[3], double p2[3]);
		//�㵽��ľ���
		static double MYFPointPlaneDist(double point[3], double origin[3], double normal[3]);
		//�Ƿ���ƽ������
		bool MYFVectorParal(ProVector v1, ProVector v2);
	};
}
