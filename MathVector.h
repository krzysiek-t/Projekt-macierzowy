#ifndef MATH_VECTOR_H //include guard 
#define MATH_VECTOR_H
#include "vector.h"


/**
* Class MathVector - inherit from template class Vector<T> with parameter T = double.
* All atributes and method was inherited from public section in the base class to public section in MathVector class
* and from protected section in the base class to protectoed section MathVector's class. This class represents
* vectors and some operations using matrices.
*/
class MathVector : public Vector<double> {
public:
	/**
	* Default constructor.
	* Build empty vector.
	*/
	MathVector(); 
	/**
	* Alternate constructor.
	* Build Vector with n elements, each are zero.
	* @param n - number of elements in the vector.
	* @see Vector(int Num)
	*/
	MathVector(int n); 
	/**
	* A member of class.
	* @return Double value - first norm of vector for which it is called.
	*/
	double one_norm() const;
	/**
	* A member of class.
	* @return Double value - second norm of vector for which it is called.
	*/
	double two_norm() const;
	/**
	* A member of class.
	* @return Double value - infinity norm of vector for which it is called
	*/
	double uniform_norm() const; 
};
#endif