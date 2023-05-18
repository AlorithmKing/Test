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
		//方向向量
		static double* MYFVectorDiff(double start[3], double end[3], double direction[3]);
		//向量的模
		static double MYFVectorLength(double vector[3]);
		//向量的单位化
		static double* MYFVectorScale(double len, double input[3], double output[3]);
		//单位向量
		static double* MYFVectorNormalize(double input[3], double output[3]);
		//向量复制
		static void MYFVectorCopy(double from[3], double to[3]);
		//向量叉积
		static double* MYFVectorCross(double product1[3], double product2[3], double output[3]);
		//向量点积
		static double MYFVectorDot(double product1[3], double product2[3]);
		//点到直线的距离
		static double MYFPointToLineDistance(double point[3], double start[3], double end[3]);
		//line1与line2的夹角
		static double* MYFVectorsLincom(double scalar_a, double vector_a[3], double scalar_b, double vector_b[3], double result[3]);
		//点到点的距离
		static double MYFPointsDist(double p1[3], double p2[3]);
		//点到面的距离
		static double MYFPointPlaneDist(double point[3], double origin[3], double normal[3]);
		//是否是平行向量
		bool MYFVectorParal(ProVector v1, ProVector v2);
	};
}
