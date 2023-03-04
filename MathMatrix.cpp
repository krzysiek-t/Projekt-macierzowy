#include "MathMatrix.h"

MathMatrix::MathMatrix() : Matrix() {}

MathMatrix::MathMatrix(int N) : Matrix(N, N)
{
	n = N;
}


int MathMatrix::get_size() const
{
	return n;
}


double MathMatrix::one_norm() const
{
	int i, j;
	double max, sum;

	max = 0;
	for (j = 0; j < nrows; j++) {
		sum = 0;
		for (i = 0; i < ncols; i++)
			sum += fabs((*this)(i, j));
		if (max < sum)
			max = sum;
	}
	return max;
}


double MathMatrix::two_norm() const
{
	int i, j;
	double sum = 0;

	for (i = 0; i < nrows; i++)
	for (j = 0; j < ncols; j++)
		sum += fabs((*this)(i, j)*(*this)(i, j));
	return (sqrt(sum));
}


double MathMatrix::uniform_norm() const
{
	int i, j;
	double sum, max;

	max = 0;
	for (i = 0; i < nrows; i++) {
		sum = 0;
		for (j = 0; j < ncols; j++)
			sum += fabs((*this)(i, j));
		if (max < sum)
			max = sum;
	}
	return max;
}


MathMatrix MathMatrix::operator*(const MathMatrix& a) const
{
	//if the matrix sizes do not match
	if (get_size() != a.get_size()) throw std::invalid_argument("rozmiary macierzy nie sa kompatybilne");

	//return matrix
	MathMatrix matrix = MathMatrix(n);

	//matrix multiplication
	for (int i = 0; i < matrix.n; i++)
	for (int j = 0; j < matrix.n; j++) { matrix(i, j) = 0; }

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < a.n; j++) {
			for (int k = 0; k < n; k++) {
				matrix(i, j) += ((*this)(i, k) * a(k, j));
			}
		}
	}
	return matrix;
}



MathVector MathMatrix::operator*(const MathVector& v) const
{
	//if the matrix sizes do not match
	if (n != v.size()) throw std::invalid_argument("rozmiary macierzy nie sa kompatybilne");

	//return matrix
	MathVector res(n);

	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) res[i] += ((*this)(i, j) * v[j]);

	return res;
}


MathMatrix MathMatrix::compute_lower() const
{
	{
		MathMatrix m;
		m = (*this);

		MathMatrix temp(m.reorder()*m);
		double mult;
		int i, j, k;

		// LU (Doolittle's) decomposition without pivoting
		for (k = 0; k < n - 1; k++) {
			for (i = k + 1; i < n; i++) {
				if (temp(k, k) == 0) throw std::invalid_argument("zero pivot");
				//	{
				//	printf("pivot is zero\n");
				//	exit(1);
				//	}
				mult = temp(i, k) / temp(k, k);
				temp(i, k) = mult;                      // entries of L are saved in temp

				for (j = k + 1; j < n; j++) {
					temp(i, j) -= mult*temp(k, j);      // entries of U are saved in temp	
				}
			}
		}

		MathMatrix l((*this).get_size());
		// create L from temp
		for (i = 0; i < n; i++) l(i, i) = 1.0;
		for (i = 1; i < n; i++)
		for (j = 0; j < i; j++) l(i, j) = temp(i, j);

		return l;
	}

}


MathMatrix MathMatrix::compute_upper() const
{
	MathMatrix m;
	m = (*this);
	
	MathMatrix temp(m.reorder()*m);
	double mult;
	int i, j, k;

	// LU (Doolittle's) decomposition without pivoting
	for (k = 0; k < n - 1; k++) {
		for (i = k + 1; i < n; i++) {
			if (temp(k, k) == 0) throw std::invalid_argument("zero pivot");
			//	{
			//	printf("pivot is zero\n");
			//	exit(1);
			//	}
			mult = temp(i, k) / temp(k, k);
			temp(i, k) = mult;                      // entries of L are saved in temp
			for (j = k + 1; j < n; j++) {
				temp(i, j) -= mult*temp(k, j);      // entries of U are saved in temp
			}
		}
	}
	MathMatrix u((*this).get_size());
	// create U from temp
	for (i = 0; i < n; i++)
	for (j = i; j < n; j++) u(i, j) = temp(i, j);

	return u;
}


MathMatrix MathMatrix::inverse() const
{

	MathMatrix A;
	A = (*this);

	MathMatrix P;
	P = A.reorder();

	MathMatrix PA;
	PA = P * A;

	MathMatrix L;
	MathMatrix U;
	L = PA.compute_lower();
	U = PA.compute_upper();

	for (int i = 0; i < n; i++)
	{
		if (U(i, i) == 0)
		{
			throw std::invalid_argument("Macierz nie jest odwracalna !!\n");
		}
	}

	MathMatrix L_inversed((*this).get_size());
	MathMatrix U_inversed((*this).get_size());

	int i, j;

	MathVector temp((*this).get_size());

	for (int k = 0; k < n; k++)
	{
		for (int e = 0; e < n; e++)
			temp[e] = 0;
		temp[k] = 1;

		// forward substitution for L y = e.
		// temp begins with a copy of e.
		for (int i = 1; i < n; i++){
			for (int j = 0; j < i; j++){
				temp[i] -= L(i, j)*temp[j];
			}
		}
		for (int w = 0; w < n; w++)
			L_inversed(w, k) = temp[w];
	}
	// back substitution for U y = e.
	// temp begins with a copy of e.

	for (int k = 0; k < n; k++)
	{
		for (int e = 0; e < n; e++)
			temp[e] = 0;

		temp[k] = 1;

		for (int i = n - 1; i >= 0; i--) {
			for (int j = i + 1; j < n; j++)
				temp[i] -= U(i, j)*temp[j];
			temp[i] /= U(i, i);
		}
		for (int w = 0; w < n; w++)
			U_inversed(w, k) = temp[w];
	}


	A = U_inversed * L_inversed;
	
	A = A * P;
	return A;
}


MathMatrix MathMatrix::reorder()
{
	MathMatrix a((*this).get_size());
	a = (*this);
	MathMatrix p((*this).get_size());


	int i, j, k;
	int pvtk, pvti;
	double aet, tmp, mult;

	MathVector pvt(n);
	MathMatrix temp(a);

	for (k = 0; k < n; k++) pvt[k] = k;

	MathVector scale(n);

	for (k = 0; k < n; k++) {
		scale[k] = 0;
		for (j = 0; j < n; j++)
		if (fabs(scale[k]) < fabs(temp(k, j))) scale[k] = fabs(temp(k, j));
	}

	for (k = 0; k < n - 1; k++) {            // main elimination loop

		// find the pivot in column k in rows pvt[k], pvt[k+1], ..., pvt[n-1]
		int pc = k;
		aet = fabs(temp((int)pvt[k], k) / scale[k]);
		for (i = k + 1; i < n; i++) {
			tmp = fabs(temp((int)pvt[i], k) / scale[pvt[i]]);
			if (tmp > aet) {
				aet = tmp;
				pc = i;
			}
		}
		if (aet == 0) throw std::invalid_argument("zero pivot, singular matrix");
		//	{
		//		printf("pivot is zero\n");
		//		exit(1);
		//	}
		if (pc != k) {                      // swap pvt[k] and pvt[pc]
			int ii = pvt[k];
			pvt[k] = pvt[pc];
			pvt[pc] = ii;
		}

		// now eliminate the column entries logically below mx[pvt[k]][k]
		pvtk = pvt[k];                           // pivot row
		for (i = k + 1; i < n; i++) {
			pvti = pvt[i];
			if (temp(pvti, k) != 0) {
				mult = temp(pvti, k) / temp(pvtk, k);
				temp(pvti, k) = mult;
				for (j = k + 1; j < n; j++) temp(pvti, j) -= mult*temp(pvtk, j);
			}
		}
	}
	for (i = 0; i < n; i++) p(i, (int)pvt[i]) = 1.0;
	return p;
}

double MathMatrix::condition_num() const
{
	double c, d;

	c = (*this).two_norm();
	d = ((*this).inverse()).two_norm();

	return (c * d);
}


std::istream& operator>>(std::istream& is, MathMatrix& m) {

	int n;
	if (!m.n) {
		std::cout << "Podaj rozmiar macierzy kwadratowej" << std::endl;
		is >> n;
		if (n <= 0) throw std::invalid_argument("read error - negative matrix size");

		// prepare the matrix to hold n elements
		m = MathMatrix(n);
	}
	// input the elements
	std::cout << "Wprowadz " << m.n * m.n << " elementow macierzy" << std::endl;
	for (int i = 0; i < m.n*m.n; i++) is >> m.v[i];
	// return the stream object
	return is;
}


std::ifstream& operator>>(std::ifstream& ifs, MathMatrix& m) {

	int n;

	// read size from the file
	ifs >> n;
	//check input sanity
	if (n < 0) throw std::invalid_argument("blad odczytu - rozmiar macierzy ujemny");

	// prepare the vector to hold n elements
	m = MathMatrix(n);

	// input the elements
	for (int i = 0; i < n*n; i++) ifs >> m.v[i];

	// return the stream object
	return ifs;
}
