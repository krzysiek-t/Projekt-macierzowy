#ifndef MATH_MATRIX_H //include guard 
#define MATH_MATRIX_H
#include "Matrix.h" 
#include "MathVector.h"
#include<iostream>
#include<fstream>
#include <stdexcept> 


/**
* Class MathMatrix - inherit from template class Matrix<T> with parameter T = double.
* All atributes and method was inherited from public section in the base class to public section in MathMatrix class
* and from protected section in the base class to protectoed section MathMatrix's class. This class represents 
* matrices and some operation using matrices. 
*/
class MathMatrix : public Matrix<double>
{
protected:
	/**
	* Privte atribute of class.
	* Size of square matrix.
	*/
	int n;					
public:
	/**
	* Default constructor.
	* Build empty matrix.
	*/
	MathMatrix(); 
	/**
	* Alternate constructor.
	* Build square matrix.
	* @param N - size of square matrix
	* @see Matrix(int Nrows, int Ncols)
	* @see n
	*/
	MathMatrix(int N); 
	/**
	* A member of class.
	* @return Integer value - size of matrix. 
	* @see n
	*/
	int get_size() const; 
	/**
	* A member of class.
	* Compute first norm of matrix for which it is called.
	* @return Double value - first norm of matrix.
	*/
	double one_norm() const; 
	/**
	* A member of class.
	* Compute socond norm of matrix for which it is called.
	* @return Double value - second norm of matrix.
	*/
	double two_norm() const; 
	/**
	* A member of class.
	* Compute infinity norm of matrix for which it is called.
	* @return Double value - infinity norm of matrix.
	*/
	double uniform_norm() const; 
	/**
	* Overloaded operator.
	* Allows user to multiply matrix by matrix. 
	* @return Object type MathMatrix.
	* @param a - reference to object type MathMatrix
	*/
	MathMatrix operator*(const MathMatrix& a) const;	
	/**
	* Overloaded operator.
	* Allows user to multiply matrix by vector. 
	* @return Object type MathVector.
	* @param v - reference to object type MathVector
	*/
	MathVector operator*(const MathVector& v) const;  
	/**
	* Member of class.
	* Compute lower matrix. 
	* @return Object type MathMatrix - lower matrix.
	* @see reorder()
	* @see MathMatrix(int N)
	*/
	MathMatrix compute_lower() const;
	/**
	* Member of class.
	* Calculate upper matrix. 
	* @return Object type MathMatrix - upper matrix
	* @see reorder()
	* @see MathMatrix(int N)
	*/
	MathMatrix compute_upper() const;
	/**
	* Member of class.
	* Calculate inverse matrix. 
	* @return Object type MathMatrix - inverse matrix.
	* @see compute_lower()
	* @see compute_upper()
	* @see reorder()
	*/
	MathMatrix inverse() const;
	/**
	* Member of class.
	* Calculate condition number. 
	* @return Value type double.
	* @see inverse()
	* @see two_norm()
	*/
	double condition_num() const;
	/**
	* Member of class.
	* Swaps rows - thanks of this it is possible to factorise 
	* any non-singular matrix into the LU form .
	* @return Object type MathMatrix - reodered matrix.
	*/
	MathMatrix reorder();
	/**
	* Overloaded friend operator.
	* Allows user to input data from keyboard. It use MathMatrix constructor.
	* @return Data input stream.
	* @param is - reference to stream object.
	* @param m - reference to MathMatrix object.
	* @see MathMatrix(int N)
	*/
	friend std::istream& operator>>(std::istream& is, MathMatrix& m);
	/**
	* Overloaded friend operator.
	* Allows user to input data from file.
	* It use constructor of MathMatrix class.
	* @return Data input stream.
	* @param ifs - reference to stream object.
	* @param m - reference to MathMatrix object.
	* @see MathMatrix(int N)
	*/
	friend std::ifstream& operator>>(std::ifstream& ifs, MathMatrix& m);
	
	
};
#endif

