#include "MYFMath.h"
#include <stdlib.h>
using namespace MYF;
double* MYFMath::MYFVectorDiff(double start[3], double end[3], double direction[3])
{
    direction[0] = end[0] - start[0];
    direction[1] = end[1] - start[1];
    direction[2] = end[2] - start[2];
    return direction;
}

double MYFMath::MYFVectorLength(double vector[3])
{
    return(sqrt(vector[0] * vector[0] +
        vector[1] * vector[1] +
        vector[2] * vector[2]));
}

void MYFMath::MYFVectorCopy(double from[3],double to[3])
{
    if (from == NULL)
        to[0] = to[1] = to[2] = 0.0;
    else
    {
        to[0] = from[0];
        to[1] = from[1];
        to[2] = from[2];
    }
   
}

double* MYFMath::MYFVectorCross(double product1[3], double product2[3], double output[3])
{
    output[0] = product1[1] *product2[2] - product1[2] * product2[1];
    output[1] = product1[2] *product2[0] - product1[0] * product2[2];
    output[2] = product1[0] *product2[1] - product1[1] * product2[0];

    return(output);
}

double  MYFMath::MYFVectorDot(double product1[3], double product2[3])
{
    double output;
    output = product1[0] * product2[0] + product1[1] * product2[1] + product1[2] * product2[2];
    return output;
}

double  MYFMath::MYFPointToLineDistance(double point[3], double start[3], double end[3])
{
    double v1[3], v2[3], dt, p1[3], dist;
    MYFVectorDiff(start, end, v1);
    MYFVectorNormalize(v1, v1);
    MYFVectorDiff(start, end, v2);
    dt = MYFVectorDot(v1, v2);
    MYFVectorsLincom(1.0, end, dt, v1, p1);
    dist = MYFPointsDist(point, p1);
    return dist;
}

double* MYFMath::MYFVectorScale(double len, double input[3], double output[3])
{
    output[0] = input[0] / len;
    output[1] = input[1] / len;
    output[2] = input[2]/ len;
    return output;
}

double* MYFMath::MYFVectorNormalize(double input[3], double output[3])
{
    
    double len;
    len = MYFVectorLength(input);
    if (len < PRO_UTIL_ALMOST_ZERO)
    {
        output[0] = input[0];
        output[1] = input[1];
        output[2] = input[2];
        return output;
    }
    else
        return(MYFVectorScale(1.0 / len, input, output));
}

double* MYFMath::MYFVectorsLincom(
    double scalar_a,
    double vector_a[3],
    double scalar_b,
    double vector_b[3],
    double result[3])
{
    result[0] = scalar_a * vector_a[0] + scalar_b * vector_b[0];
    result[1] = scalar_a * vector_a[1] + scalar_b * vector_b[1];
    result[2] = scalar_a * vector_a[2] + scalar_b * vector_b[2];

    return(result);
}


double  MYFMath::MYFPointsDist(
    double p1[3],
    double p2[3])
{
    double aux, diff[3];

    MYFVectorDiff(p1, p2, diff);
    aux = MYFVectorDot(diff, diff);
    aux = sqrt(aux);
    return(aux);
}
double MYFMath::MYFPointPlaneDist(
    double point[3],	/* The point			*/
    double origin[3],	/* A point on the plane		*/
    double normal[3])	/* The normal to the plane	*/
{
    double v[3], dist;

    MYFVectorDiff(point, origin, v);
    dist = MYFVectorDot(v, normal);
    return(dist);
}

bool  MYFMath::MYFVectorParal(ProVector v1,ProVector v2)
{
    if (MYFVectorDot(v1, v2) == MYFPointsDist(v1, v2))
        return true;
    else
        return false;
}