#ifndef MATRIX_H  
#define MATRIX_H

#include <iostream>  
#include <fstream>   
#include <stdexcept> 
#include "vector.h"  
#include "Complex.h"

/**
* This is a template class which represents mathematical matrix of setted type ( thank of that this class is 
* template it is possible that T could be int, double, complex etc. - it can storage informations of this type).
* Using objects of this class it is possible to do some operatins which are listed below.
*/
template<typename Y>
class Matrix {
protected:
	/**
	* Protected atribute of class.
	* Vector used to store the matrix elements.
	*/
	Vector<Y> v;
	/**
	* Protected atribute of class.
	* Number of rows of the matrix.
	*/
    int nrows;    
	/**
	* Protected atribute of class.
	* Number of columns of the matrix.
	*/
    int ncols;    

public:
	/**
	* Default constructor.
	* Create empty vector.
	*/
    Matrix();
	/**
	* Alternate constructor.
	* Creates a matrix of given size.
	* @param Nrows - integer value - number of rows of matrix.
	* @param Ncols - integer value - number of columns of matrix.
	* @see Vector(int Num)
	*/
    Matrix(int Nrows, int Ncols);  
	/**
	* Constructor.
	* Build a matrix from a vector.
	* @param v - reference to object type Vector.
	* @see Vector()
	*/
	Matrix(const Vector<Y>& v); 
	/**
	* Copy constructor.
	* Allocate the same amount of memory for an object as the base one
	* and copy data from the base object to another.
	* @param m - reference to object type Matrix.
	* @see getNrows()
	* @see getNcols()
	*/
	Matrix(const Matrix<Y>& m); 
	/**
	* A member of class.
	* @return Integer value - number of rows.
	* @see nrows
	*/
	int getNrows() const; 
	/**
	* A member of class.
	* @return Integer value - number of columns.
	* @see ncols
	*/
	int getNcols() const; 
	/**
	* Overloaded operator for assignment matrix values.
	* @return Reference to Y value.
	* @param i - integer value - it refers to addres of appropriate row of array.
	* @param j - integer value - it refers to addres of appropriate column of array.
	*/
    Y& operator() (int i, int j); 
	/**
	* Overloaded operator for reading matrix values.
	* @return Type Y.
	* @param i - integer value - it refers to addres of appropriate row of array.
	* @param j - integer value - it refers to addres of appropriate column of array.
	* @see v
	*/
    Y operator() (int i, int j) const; 
	/**
	* Overloaded assignment operator.
	* Copies data from object from right side of sign to object
	* from left side of sign. Sets size of matrix from left side of sign the same as matrix
	* from right side of matrix.
	* @return Refernece to object type MathMatrix.
	* @param m - reference to Matrix object.
	* @see v
	*/
	Matrix<Y>& operator=(const Matrix<Y>& m); 
	/**
	* Overloaded comparison operator.
	* Compares if two matrices have the same values or not.
	* @return Bool value (true or false).
	* @param m - reference to object type Matrix.
	*/
	bool operator==(const Matrix<Y>& m) const;

	/**
	* Overloaded inputting operator.
	* Allows user to input data from keyboard to the matrix. Checks if data is appropriate or not.
	* It uses matrix constructor.
	* @return Data input stream.
	* @param is - stream object.
	* @param m - reference to object type Matrix.
	* @see Matrix(int Nrows, int Ncols)
	*/
	template <typename Y> friend std::istream& operator>>(std::istream& is, Matrix<Y>& m);
	/**
	* Overloaded outputting operator.
	* Allows user to output data from matrix to the screen. 
	* @return Data output stream.
	* @param os - stream object.
	* @param m - reference to objec type Matrix.
	*/
	template <typename Y> friend std::ostream& operator<<(std::ostream& os, const Matrix<Y>& m);
	/**
	* Overloaded inputed operator.
	* Allows user to input data from file to matrix. It is checked if data is appropriate or not.
	* It uses matrix constructor.
	* @return Data input stream.
	* @param ifs - stream object.
	* @param m - reference t oobject type Matrix.
	* @see Matrix (int Nrows, int Ncols)
	*/
	template <typename Y> friend std::ifstream& operator>>(std::ifstream& ifs, Matrix<Y>& m);
	/**
	* Overloaded outputting operator.
	* Allows user to output data from matrix to file.
	* @return Data output stream.
	* @param ofs - stream object.
	* @param m - reference to objec type Matrix.
	*/
	template <typename Y> friend std::ofstream& operator<<(std::ofstream& ofs, const Matrix<Y>& m);

};





// CONSTRUCTORS
/*=
*Default constructor (empty matrix)
*/
template<typename Y>
Matrix<Y>::Matrix() : nrows(0), ncols(0), v(0) {}

/*
* Alternate constructor - creates a matrix with the given values
*/
template<typename Y>
Matrix<Y>::Matrix(int Nrows, int Ncols)
{
	//check input
	if (Nrows < 0 || Ncols < 0) throw std::invalid_argument("Rozmiar macierzy ujmeny");
	nrows = Nrows;
	ncols = Ncols;
	//if rownumber <= 0 or colnumber <= 0 then the program creates a 0-sized vector
	if (nrows <= 0 || ncols <= 0)
		v = Vector<Y>(0);  // empty matrix, nothing to allocate
	else
		v = Vector<Y>(nrows*ncols);
}


/*
* Alternate constructor - creates a matrix from a vector
*/
template<typename Y>
Matrix<Y>::Matrix(const Vector<Y>& x) : v(x), nrows(x.size()), ncols(1)
{
}

/*
* Copy constructor
*/
template<typename Y>
Matrix<Y>::Matrix(const Matrix<Y>& m) : v(m.v), nrows(m.getNrows()), ncols(m.getNcols())
{
}


// ACCESSOR METHODS
/*
* Get back matrix rows
*/
template<typename Y>
int Matrix<Y>::getNrows() const { return nrows; }

/*
* Get back matrix cols
*/
template<typename Y>
int Matrix<Y>::getNcols() const { return ncols; }

// OVERLOADED FUNCTION CALL OPERATORS
/*
* Operator() - returns with a specified value of matrix for write
*/
template<typename Y>
Y& Matrix<Y>::operator() (int i, int j) {

	if (i>nrows - 1 || j>ncols - 1 || i<0 || j<0) throw std::out_of_range("matrix access error");
	return v[i*ncols + j];
}

/*
* Operator() - returns with a specified value of matrix for read
*/
template<typename Y>
Y Matrix<Y>::operator() (int i, int j) const {
	//if the given parameters (coordinates) are out of range
	if (i>nrows - 1 || j>ncols - 1 || i<0 || j<0) throw std::out_of_range("matrix access error");
	return v[i*ncols + j];
}

/*
* Operator= - assignment
*/
template<typename Y>
Matrix<Y>& Matrix<Y>::operator=(const Matrix<Y>& m)
{
	nrows = m.nrows;
	ncols = m.ncols;

	v = m.v;

	return *this;
}


/*
* equiv - comparison function, returns true if the given matrices are the same
*/
template<typename Y>
bool Matrix<Y>::operator==(const Matrix<Y>& a) const {

	//if the sizes do not match return false
	if ((nrows != a.nrows) || (ncols != a.ncols)) return false;

	//compare all of the elements
	for (int i = 0; i<nrows; i++) {
		for (int j = 0; j<ncols; j++) {
			if ((*this)(i, j) != a(i, j)) return false;
		}
	}

	return true;
}


// INPUT AND OUTPUT
/*
* keyboard input , user friendly
*/


template<typename Y>
std::istream& operator>>(std::istream& is, Matrix<Y>& m) {
	
	int nrows, ncols;
	if (!m.nrows) {
		std::cout << "Wprowadz liczbe wierszy macierzy: " << std::endl;
		is >> nrows;
		std::cout << "Wprowadz liczbe kolumn macierzy: " << std::endl;
		is >> ncols;
		//check input 
		if (nrows < 0 || ncols < 0) throw std::invalid_argument("Blad odczytu: rozmiar macierzy ujemny");
		
		// prepare the matrix to hold n elements
		m = Matrix<Y>(nrows, ncols);
		
	}
	// input the elements
	std::cout << "Wprowadz " << m.nrows * m.ncols << " elementow macierzy" << std::endl;
	for (int i = 0; i<m.nrows*m.ncols; i++) is >> m.v[i];
	// return the stream object
	return is;
}


/*
* screen output, user friendly
*/
template<typename Y>
std::ostream& operator<<(std::ostream& os, const Matrix<Y>& m) {

	if (&m.v) {
		os << "Elementy macierzy to: " << std::endl;
		for (int i = 0; i<m.nrows; i++) {
			for (int j = 0; j<m.ncols; j++) {
				os << m(i, j) << " ";
			}
			os << "\n";
		}
		os << std::endl;
	}
	else
	{
		os << "Macierz pusta." << std::endl;
	}
	return os;
}

/*
* file input - raw data, compatible with file writing operator
*/


template<typename Y>
std::ifstream& operator>>(std::ifstream& ifs, Matrix<Y>& m) {

	int nrows, ncols;

	// read size from the file
	ifs >> nrows; ifs >> ncols;
	//check input sanity
	if (nrows < 0 || ncols < 0) throw std::invalid_argument("Blad odczytu pliku - rozmiar macierzy ujemny");

	// prepare the vector to hold n elements
	m = Matrix<Y>(nrows, ncols);

	// input the elements
	for (int i = 0; i<nrows*ncols; i++) ifs >> m.v[i];

	// return the stream object
	return ifs;
}


/*
* file output - raw data, comaptible with file reading operator
*/
template<typename Y>
std::ofstream& operator<<(std::ofstream& ofs, const Matrix<Y>& m) {
	//put matrix rownumber in first line (even if it is zero)
	ofs << m.nrows << std::endl;
	//put matrix columnnumber in second line (even if it is zero)
	ofs << m.ncols << std::endl;
	//put data in third line (if size==zero nothing will be put)
	for (int i = 0; i<m.nrows; i++) {
		for (int j = 0; j<m.ncols; j++) ofs << m(i, j) << " ";
		ofs << std::endl;
	}
	return ofs;
}



#endif