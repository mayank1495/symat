#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Macro for class template. SType is to be passed
// during object creation.
#define SYMAT_TEMPLATE template <typename SType>

// Macro to declare Symat class matrix type.
#define SYMAT_MATRIX_TYPE Symat<SType>

// Macro for dynamic Eigen::Matrix declaration with Scalar argument
// being SType which is passed during Symat object creation.
#define EIGEN_DYNAMIC_MATRIX_TYPE Matrix<SType, Dynamic, Dynamic>

/*
Class for symmetric matrices. Symmetric matrix is 
formed by passing a generic square Eigen::Matrix.
Only the upper diognal is stored since for 
a symmetrix matrix S, S(i,j)=S(j,i).
Class uses template definitions, hence matrix data type
is to passed during object creation.
USAGE:
	Symat<data_type> obj(Eigen::Matrix);
	Eg: Symat<float> S(m);
OPERATIONS:
	Symat +/- Symat
	Symat +/- Eigen::Matrix
	Symat∗Symat
	Symat∗Eigen::Matrix
NOTE:
	*Eigen::Matrix during object creation should be a generic sqaure matrix.
	*Datatype of Eigen::Matrix and the symmetric matrix should be same
	 in any operation and object creation.
*/

SYMAT_TEMPLATE
class Symat
{
  private:
	// Vector of type SType(data_type passed during object creation) to store
	// upper diognal of Eigen::Matrix.
	vector<SType> s_vec;

	// Variable to store dimension of the symmetric matrix.
	// Initialized from Eigen::Matrix passed during Symat object creation.
	int s_dim;

	//Function to check validity
	//??

  public:
	// Default constructor ??
	Symat() {}

	// Parameterized constructor to initialize symmetric matrix from Eigen::Matrix
	Symat(const EIGEN_DYNAMIC_MATRIX_TYPE &);

	// Overloading () operator to return value of symmetric matrix at (i,j).
	SType operator()(int, int) const;

	//Accessor function to get dimension of symmetric matrix.
	int dim() const { return s_dim; }

	// Functions to add matrices
	EIGEN_DYNAMIC_MATRIX_TYPE add(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE add(const SYMAT_MATRIX_TYPE &);

	// Functions to subtract matrices
	EIGEN_DYNAMIC_MATRIX_TYPE sub(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE sub(const SYMAT_MATRIX_TYPE &);

	// Functions to multiply matrices
	EIGEN_DYNAMIC_MATRIX_TYPE mul(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE mul(const SYMAT_MATRIX_TYPE &);

	// overloading ostream << operator to output symmetric matrix using cout.
	friend ostream &operator<<(ostream &out, const SYMAT_MATRIX_TYPE &s_mat)
	{
		for (int i = 0; i < s_mat.s_dim; i++)
		{
			for (int j = 0; j < s_mat.s_dim; j++)
			{
				cout << s_mat(i, j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
};

// Constructor takes Eigen::Matrix as parameter and initializes the Symat class
// object. The dimension is stored in s_dim.
// The upper diognal of the Eigen::Matrix is stored in vector s_vec.
SYMAT_TEMPLATE
SYMAT_MATRIX_TYPE::Symat(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	s_dim = mat.rows();
	for (int i = 0; i < s_dim; i++)
		for (int j = 0; j < s_dim; j++)
		{
			if (i <= j)
			{
				s_vec.push_back(mat(i, j));
			}
		}
}

// From the passed (i,j), index is calculated to return
// the required symmetric matrix value at (i,j) from vector s_vec.
// If i>j then values are swaped and then index is calculated
// since for a Symat matrix S, S(i,j)=S(j,i)
SYMAT_TEMPLATE
SType SYMAT_MATRIX_TYPE::operator()(int i, int j) const
{
	if (i > j)
		swap(i, j);
	int idx = ((i * s_dim) + j) - ((i * (i + 1)) / 2);

	return s_vec[idx];
}

// Eigen::Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within. Function adds the passed matrix to the Symat matrix
// and stores the result in the temp Eigen::Matrix.
// The temp matrix is resized to the dimension of the symmetric matrix.
// NOTE: The dimension of the matrices should be same.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::add(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	temp.resize(s_dim, s_dim);

	if (s_dim == mat.rows() && s_dim == mat.cols())
	{
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = mat(i, j) + this->operator()(i, j);
			}
		}
		return temp;
	}
}

// Symat matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within. Function adds the passed matrix to the Symat matrix
// and stores the result in the temp Eigen::Matrix.
// The temp matrix is resized to the dimension of the symmetric matrix.
// NOTE: The dimension of the matrices should be same.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::add(const SYMAT_MATRIX_TYPE &s_mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	temp.resize(s_dim, s_dim);
	if (s_dim == s_mat.dim())
	{
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = s_mat(i, j) + this->operator()(i, j);
			}
		}
		return temp;
	}
}

// Eigen::Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// NOTE: Function substracts the passed matrix from the Symat matrix.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to the dimension of the symmetric matrix.
// NOTE: The dimension of the matrices should be same.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::sub(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	temp.resize(s_dim, s_dim);

	if (s_dim == mat.rows() && s_dim == mat.cols())
	{
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = this->operator()(i, j) - mat(i, j);
			}
		}
		return temp;
	}
}

// Symat Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// NOTE: Function substracts the passed matrix from the Symat matrix.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to the dimension of the symmetric matrix.
// NOTE: The dimension of the matrices should be same.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::sub(const SYMAT_MATRIX_TYPE &s_mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	temp.resize(s_dim);

	if (s_dim == s_mat.dim())
	{
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = this->operator()(i, j) - s_mat(i, j);
			}
		}
		return temp;
	}
}

// Eigen::Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to rows equal to the dimension of symmetric matrix
// and columns equal to the columns of passed matrix.
// NOTE: The columns of the Symat Matrix should be equal to the rows of the passed Matrix.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::mul(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	if (s_dim == mat.rows())
	{
		EIGEN_DYNAMIC_MATRIX_TYPE temp;
		int t_rows = s_dim, t_cols = mat.cols();
		temp.resize(t_rows, t_cols);

		long long sum = 0;
		for (int i = 0; i < t_rows; i++)
		{
			for (int j = 0; j < t_cols; j++)
			{
				sum = 0;
				for (int mov = 0; mov < s_dim; mov++)
				{
					sum += ((this->operator()(i, mov)) * (mat(mov, j)));
				}
				temp(i, j) = sum;
			}
		}

		return temp;
	}
}

// Symat Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to rows equal to the dimension of symmetric matrix
// and columns equal to the columns of passed matrix.
// NOTE: The columns of the Symat Matrix should be equal to the rows of the passed Matrix.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::mul(const SYMAT_MATRIX_TYPE &s_mat)
{
	if (s_dim == s_mat.dim())
	{
		EIGEN_DYNAMIC_MATRIX_TYPE temp;
		int t_rows = s_dim, t_cols = s_dim;
		temp.resize(t_rows, t_cols);

		long long sum = 0;
		for (int i = 0; i < t_rows; i++)
		{
			for (int j = 0; j < t_cols; j++)
			{
				sum = 0;
				for (int mov = 0; mov < s_dim; mov++)
				{
					sum += ((this->operator()(i, mov)) * (s_mat(mov, j)));
				}
				temp(i, j) = sum;
			}
		}

		return temp;
	}
}

int main()
{
	MatrixXf m(3, 3);
	Matrix<float, Dynamic, Dynamic> z;
	z.resize(3, 3);
	m << 1, 2, 3, 1, 2, 3, 1, 2, 3;
	z << 1, 1, 1, 0, 1, 1, 1, 1, 1;
	cout << m << endl
		 << endl;
	cout << z << endl
		 << endl;
	Symat<float> S(m);
	Symat<float> S2(z);
	cout << "S:\n"
		 << S;
	cout << "S2:\n"
		 << S2;
	Matrix<float, Dynamic, Dynamic> kk = S.mul(z);
	// MatrixXf kk = S.add(S2);
	cout << kk << endl;
	// S2.add(m);
	cout << "in main.." << endl;
}