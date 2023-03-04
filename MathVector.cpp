#include "MathVector.h"

//	Default constructor.
//	Build empty vector.
MathVector::MathVector() : Vector()  {}

//	Alternate constructor.
//	Build Vector with n elements, each of are zero.
//	@param n - number of elements in the vector.
MathVector::MathVector(int n) : Vector(n) {}

//	Method which returning double value - first norm of vector for which it is called.
double MathVector::one_norm() const
{
	int i;
	double sum = 0;

	for (i = 0; i < num; i++)
		sum += fabs(pdata[i]);
	return sum;
}

//	Method which returning double value - second norm of vector for which it is called.
double MathVector::two_norm() const
{
	int i;
	double sum = 0;

	for (i = 0; i < num; i++)
		sum += fabs(pdata[i] * pdata[i]);

	return (sqrt(sum));
}

//	Method which returning double value - infinity norm of vector for which it is called.
double MathVector::uniform_norm() const
{
	int i;
	double max = 0;

	for (i = 0; i<num; i++)
	if (max < fabs(pdata[i])) max = fabs(pdata[i]);
	return max;
}
