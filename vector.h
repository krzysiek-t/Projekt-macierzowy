#ifndef VECTOR_H 
#define VECTOR_H

#include <iostream> 
#include <fstream>  
#include <stdexcept>

/**
* This is a class which represent vector of setted type ( T could be int, double, complex etc. - it
* can storage informations of this type). Using objects of this class it is possible to
* do some operatins which are listed below.
*/
template <typename T>
class Vector {
protected:
	/**
	* Protected atrribute of class.
	* Number of elements.
	*/
    int num; 
	/**
	* Protected atribute of class.
	* Pointer to the data - the same type as T.
	*/
	T* pdata;
	/**
	* Protected function of class. 
	* Allocate memory for vector's elements and initialize it by zeros. If inputed size
	* of vector is negative - throw exception. User should not call it.
	* @param Num - integer value - number of elements of vector.
	* @see T* pdata
	* @see num
	*/
    void Init(int Num); 
public:
	/**
	* Default constructor.
	* Create empty vector
	*/
    Vector();
	/**
	* Constructor.
	* Uses Init method to create Vector of given size.
	* @param Num - integer value - number of elements of vector.
	* @see Init(int Num)
	*/
    explicit Vector(int Num);
	/**
	* Copy constructor.
	* Alocate memory for an object and copying data from one object to another.
	* @param v - reference to object type Vector.
	* @see Init(int Num)
	*/
    Vector(const Vector<T>& v); 
	/**
	* Virtual destructor.
	* Release dynamic memory and call appropriate dastructors in derived classes.
	*/
    virtual ~Vector(); 
	/**
	* A member of class.
	* @return Integer value - number of elements in the vector.
	* @see num
	*/
    int size() const;
	/**
	* Overloaded assignment operator.
	* It deleting existing data of object of left side of assignment sign and copy data
	* from object from right side of assignment sign to object of left side of assignment sign.
	* @return Reference to object type Vector.
	* @param v - reference to object type Vector and returning reference to object type Vector.
	* @see Init(int Num)
	*/
    Vector<T>& operator= (const Vector<T>& v); 
	/**
	* Overloaded array access operator for writing.
	* @return Reference to the same values as T is setted.
	* @param i - integer value - it refers to addres of array
	*/
    T& operator[] (int i);
	/**
	* Overloaded array acces operator for reading.
	* This overloaded operator allows user to read data. 
	* @return The same as T is setted.
	* @param i - integer value - it refers to addres of array
	*/
    T operator[] (int i) const; 
	/**
	* Overloaded comparison operator.
	* Compares if two vectors have the same value or not.
	* @return Bool value (true or false). 
	* @param v - reference to object type Vector
	*/
	bool operator==(const Vector<T>& v) const; 
	/**
	* Overloaded inputed operator.
	* Allows user to input data from keyboard to the vector. Checks if data is appropriate or not.
	* It uses Vector constructor.
	* @return Data input stream.
	* @param is - stream object.
	* @param v - reference t oobject type Vector.
	* @see Vector(int Num)
	*/
    template <typename T> friend std::istream& operator>>(std::istream& is, Vector<T>& v);
	/**
	* Overloaded outputted operator.
	* Allows user to output data from vector to the screen. 
	* @return Data output stream.
	* @param os - stream object.
	* @param v - reference to objec type Vector.
	*/
    template <typename T> friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v);
	/**
	* Overloaded inputed operator.
	* Allows user to input data from file to vector. Checks if data is appropriate or not.
	* It uses Vector constructor.
	* @return Data input stream.
	* @param ifs - stream object.
	* @param v - reference t oobject type Vector.
	* @see Vector(int Num)
	*/
    template <typename T> friend std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v);
	/**
	* Overloaded outputted operator.
	* Allows user to output data from vector to file.
	* @return Data output stream.
	* @param ofs - stream object.
	* @param v - reference to objec type Vector.
	*/
    template <typename T> friend std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v);
};


// CONSTRUCTORS
// default constructor (empty vector)

template<typename T>
Vector<T>::Vector() : num(0), pdata(0) {}

// initialise data, called by the constructors
template<typename T>
void Vector<T>::Init(int Num)
{
    //check input sanity
    if(Num < 0) throw std::invalid_argument("Rozmiar wektora ujemny ");
    num = Num;
    if (num <= 0)
        pdata = 0;  // empty vector, nothing to allocate
    else {
        pdata = new T[num];  // Allocate memory for vector
		for (int i=0; i<num; i++) pdata[i] = 0.0;
	}
}

// alternate constructor
template<typename T>
Vector<T>::Vector(int Num)
{
    Init(Num);
}

// copy constructor
template<typename T>
Vector<T>::Vector(const Vector<T>& copy)
{
    Init(copy.size()); // allocate the memory 

    // copy the data members (if vector is empty then pdata==0 and num==0)
    for (int i=0; i<num; i++) pdata[i]=copy.pdata[i]; 
}

// DESTRUCTOR
template<typename T>
Vector<T>::~Vector()
{
    delete [] pdata; // free the dynamic memory 
}


// OVERLOADED OPERATORS
// assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& copy)
{
    if (this == &copy) return *this; // Can't copy self to self (that is v = v 
    // in main is dealt with)
    delete [] pdata; // delete existing memory
    Init(copy.size()); // create new memory then copy data
    for (int i=0; i<num; i++) pdata[i] = copy.pdata[i]; 
    return *this;
}


// array access operator for assigning values
template<typename T>
T& Vector<T>::operator[](int i)
{
    //check the range, throw appropriate exception 
    if(i<0 || i>=num) throw std::out_of_range("vector access error");
    return pdata[i];
}

// array access operator for reading values
template<typename T>
T Vector<T>::operator[](int i) const
{
    //check the range, throw appropriate exception 
    if(i<0 || i>=num) throw std::out_of_range("vector access error");
    return pdata[i];
}

// SIZE
// return the size of the vector
template<typename T>
int Vector<T>::size() const
{
    return num;
}

// COMPARISON
template<typename T>
bool Vector<T>::operator==(const Vector& v) const
{	
	if (num != v.num) throw std::invalid_argument("Rozmiary wektora niekompatybilne\n"); 
	for (int i=0; i<num; i++) if ((*this)[i] != v[i]) return false;
	return true;
}


// INPUT AND OUTPUT
// keyboard input - user friendly
template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v)
{
	if (!v.num) {
		int n;

		std::cout << "Podaj rozmiar wektora" << std::endl;
		is >> n;
		//check input sanity
		if(n < 0) throw std::invalid_argument("Blad odczytu - rozmiar wektora ujemny. ");

		// prepare the vector to hold n elements
		v = Vector<T>(n);
	}
	// input the elements
	std::cout << "Wprowadz "<< v.num <<" elementow wektora" << std::endl;
	for (int i=0; i<v.num; i++) is >> v[i];

    // return the stream object
    return is;
}

// file input - raw data, compatible with file writing operator
template<typename T>
std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v) 
{
    int n;

    // read size from the file
    ifs >> n;
    //check input sanity
    if(n < 0) throw std::invalid_argument("Blad odczytu - rozmiar wektora negatywny");

    // prepare the vector to hold n elements
    v = Vector<T>(n);

    // input the elements
    for (int i=0; i<n; i++) ifs >> v[i];

    // return the stream object
    return ifs;
}

// screen output - user friendly
template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    if (v.pdata) {
        for (int i=0; i<v.size(); i++) os << v[i]  << " ";
        os << std::endl;
    }
    else
    {
        os << "Vector is empty." << std::endl;
    }
    return os;
}

// file output - raw data, comaptible with file reading operator
template<typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v)
{
    //put vector size in first line (even if it is zero)
    ofs << v.size() << std::endl;
    //put data in second line (if size==zero nothing will be put)
    for (int i=0; i<v.size(); i++) ofs << v[i]  <<  " ";
    ofs << std::endl;
    return ofs;
}


#endif