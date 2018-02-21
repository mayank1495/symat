#include <iostream>
#include <algorithm>
#include <vector>
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
Only the upper diognal is stored in a 1-D array since for 
a symmetrix matrix S, S(i,j)=S(j,i).
Class uses template definitions, hence matrix data type
is to passed during object creation.
USAGE:
	Symat<data_type> obj(Eigen::Matrix);
	Symat<data_type> obj;
	Eg: Symat<float> S(m);
		Symat<float> S2;
		S2=S;
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

  public:
	// Default constructor if no parameter is passed
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

	// Overloading ostream << operator to output symmetric matrix using cout.
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
// If the Eigen::Matrix passed is not a sqaure matrix, exception is thrown.
SYMAT_TEMPLATE
SYMAT_MATRIX_TYPE::Symat(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{

	try
	{
		if (!(mat.rows() == mat.cols()))
			throw - 1;
	}
	catch (...)
	{
		cout << "\nError: Passed Eigen::Matrix should be a generic square matrix.\n";
		return;
	}

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
// if i or j is less then 0, they are set to 0.
// if i or j is greater than equal to dimension of the Symat Matrix,
// they are set to dimension-1
SYMAT_TEMPLATE
SType SYMAT_MATRIX_TYPE::operator()(int i, int j) const
{
	i = (i < 0 ? 0 : (i >= s_dim ? (s_dim - 1) : i));
	j = (j < 0 ? 0 : (j >= s_dim ? (s_dim - 1) : j));

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
// If the dimensions are different , error message is shown.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::add(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{

	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	try
	{
		if (!(s_dim == mat.rows() && s_dim == mat.cols()))
			throw - 1;

		temp.resize(s_dim, s_dim);
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = mat(i, j) + this->operator()(i, j);
			}
		}
	}
	catch (...)
	{
		cout << "\nError: Dimension of matrices are different.\n";
	}
	return temp;
}

// Symat matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within. Function adds the passed matrix to the Symat matrix
// and stores the result in the temp Eigen::Matrix.
// The temp matrix is resized to the dimension of the symmetric matrix.
// NOTE: The dimension of the matrices should be same.
// If the dimensions are different , error message is shown.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::add(const SYMAT_MATRIX_TYPE &s_mat)
{

	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	try
	{
		if (!(s_dim == s_mat.dim()))
			throw - 1;

		temp.resize(s_dim, s_dim);
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = s_mat(i, j) + this->operator()(i, j);
			}
		}
	}
	catch (...)
	{
		cout << "\nError: Dimension of matrices are different.\n";
	}
	return temp;
}

// Eigen::Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// NOTE: Function substracts the passed matrix from the Symat matrix.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to the dimension of the symmetric matrix.
// NOTE: The dimension of the matrices should be same.
// If the dimensions are different , error message is shown.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::sub(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	try
	{
		if (!(s_dim == mat.rows() && s_dim == mat.cols()))
			throw - 1;

		temp.resize(s_dim, s_dim);
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = this->operator()(i, j) - mat(i, j);
			}
		}
	}
	catch (...)
	{
		cout << "\nError: Dimension of matrices are different.\n";
	}

	return temp;
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
	try
	{
		if (!(s_dim == s_mat.dim()))
			throw - 1;

		temp.resize(s_dim, s_dim);
		for (int i = 0; i < s_dim; i++)
		{
			for (int j = 0; j < s_dim; j++)
			{
				temp(i, j) = this->operator()(i, j) - s_mat(i, j);
			}
		}
	}
	catch (...)
	{
		cout << "\nError: Dimension of matrices are different.\n";
	}

	return temp;
}

// Eigen::Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to rows equal to the dimension of symmetric matrix
// and columns equal to the columns of passed matrix.
// NOTE: The column size of the Symat Matrix should be equal to the row size of the passed Matrix.
// If not, exception is thrown.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::mul(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	try
	{
		if (!(s_dim == mat.rows()))
			throw - 1;

		int t_rows = s_dim, t_cols = mat.cols();
		temp.resize(t_rows, t_cols);
		SType sum = 0;
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
	}
	catch (...)
	{
		cout << "\nError: Matrices do not qualify for Matrix multiplication. \n";
		cout << "The number of columns of the Symat Matrix should be equal to\n"
			 << "the number of rows of the passed Matrix.\n";
	}
	return temp;
}

// Symat Matrix is passed as parameter and a temporary Eigen::Matrix
// is declared within.
// The result is stored in the temp Eigen::Matrix.
// The temp matrix is resized to rows equal to the dimension of symmetric matrix
// and columns equal to the columns of passed matrix.
// NOTE: The column size of the Symat Matrix should be equal to the row size of the passed Matrix.
// If not, exception is thrown.
// The result is returned as Eigen::Matrix.
SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::mul(const SYMAT_MATRIX_TYPE &s_mat)
{
	EIGEN_DYNAMIC_MATRIX_TYPE temp;
	try
	{
		if (!(s_dim == s_mat.dim()))
			throw - 1;

		int t_rows = s_dim, t_cols = s_dim;
		temp.resize(t_rows, t_cols);
		SType sum = 0;
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
	}
	catch (...)
	{
		cout << "\nError: Matrices do not qualify for Matrix multiplication. \n";
		cout << "The number of columns of the Symat Matrix should be equal to\n"
			 << "the number of rows of the passed Matrix.\n";
	}
	return temp;
}

int main()
{
	//4 Eigen Matrix of type float with dimensions 3x3,2x2,3x3 and 3x4;
	MatrixXf mat3f(3, 3), mat2f(2, 2), iden3f(3, 3), mat34f(3, 4);
	mat3f << 1, 2, 3, 1, 2, 3, 1, 2, 3;
	mat2f << 2, 3, 4, 2;
	iden3f << 1, 1, 1, 1, 1, 1, 1, 1, 1;
	mat34f << 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3;

	cout << "\n::OBJECT CREATION::\n";
	//Symmetric matrix S, storing only the upper diognal of the passed matrix
	Symat<float> S1(mat3f);
	cout << "\nPassed Eigen Matrix(3x3) mat3f: \n"
		 << mat3f << endl;
	cout << "Symmetric Matrix S1: \n"
		 << S1;
	//Symmetric matrix from mat2f Eigen Matrix;
	Symat<float> S2(mat2f);
	cout << "Passed Eigen Matrix(2x2) mat2f: \n"
		 << mat2f << endl;
	cout << "Symmetric Matrix S2: \n"
		 << S2;
	//Symmetric matrix from Matrix of dimension 3x4.
	//This will produce error since sqaure matrix is not passed.
	Symat<float> S(mat34f);
	cout << "Error passing 3x4 matrix. Back to main.\n\n";

	cout << "::ADDITION::\n\n";
	/*Addition of Symmetric matrix with Eigen Matrix*/
	//Adding 3x3 matrices
	MatrixXf matAdd = S1.add(mat3f);
	cout << "Add Result S1+mat3f:\n"
		 << matAdd << endl;
	//Adding 3x3 symmetric matrix with 2x2 Eigen Matrix.
	//This will throw exception since dimensions are diffrent.
	matAdd = S1.add(mat2f);
	cout << "Error adding S1+mat2f. Back to main.\n\n";
	/*Addition of Symmetric matrix with other Symmetric Matrix*/
	//Adding 3x3 symmetric matrices
	Symat<float> S1a(iden3f);
	MatrixXf symAdd = S1.add(S1a);
	cout << "Passed Symat Matrix: \n"
		 << S1a;
	cout << "Add result S1+(passed matrix): \n"
		 << symAdd << endl;
	//Adding 3x3 symmetric matrix with 2x2 symmetric matrix.
	//This will throw exception since dimensions are diffrent.
	symAdd = S1.add(S2);
	cout << "Error adding S1+S2. Back to main.\n\n"
		 << endl;

	cout << "::SUBTRACTION::\n\n";
	/*Substracting Eigen Matrix FROM Symmetric matrix*/
	// 3x3 matrices
	MatrixXf matSub = S1.sub(mat3f);
	cout << "Sub Result S1-mat3f:\n"
		 << matSub << endl;
	//Subtracting  2x2 Eigen Matrix FROM 3x3 symmetric matrix .
	// This will throw exception since dimensions are diffrent.
	matSub = S1.sub(mat2f);
	cout << "Error Subtracting S1-mat2f. Back to main.\n\n";
	/*Substraction of Symmetric matrix from other Symmetric Matrix*/
	//3x3 symmetric matrices
	Symat<float> S1b(iden3f);
	MatrixXf symSub = S1.sub(S1b);
	cout << "Passed Symat Matrix: \n"
		 << S1a;
	cout << "Sub. result S1-(passed matrix): \n"
		 << symSub << endl;
	//Subtracting 3x3 symmetric matrix with 2x2 symmetric matrix.
	//This will throw exception since dimensions are diffrent.
	symSub = S1.sub(S2);
	cout << "Error Subtracting S1-S2. Back to main.\n\n";

	cout << "::MULTIPLICATION::\n\n";
	/*Multiplication Of Symmetric Matrix with Eigen::Matrix*/
	//Multiplying 3x3 Symmetric Matrix with 3x4 Eigen Matrix
	MatrixXf matMul = S1.mul(mat34f);
	cout << "Passed Eigen Matrix(3x4): \n"
		 << mat34f << endl;
	cout << "Mul. result S1*(passed matrix) (3x3)x(3x4)=(3x4): \n"
		 << matMul << endl;
	//Multiplying 3x3 Symmetric Matrix with 2x2 Eigen Matrix
	//This will produce error since column size in symmetric matrix is 3
	//and row size in eigen matrix is 2.
	matMul = S1.mul(mat2f);
	cout << "Cannot multiply 3x3 matrix with 2x2 matrix. Back to main.\n\n";
	/*Multiplication Of Symmetric Matrix with another Symmetric Matrix*/
	//3x3 Matrices
	MatrixXf symMul = S1.mul(S1a);
	cout << "Passed Symmetric Matrix(3x3): \n"
		 << S1a;
	cout << "Mul. result of S1*(passed matrix): \n"
		 << symMul << endl;
	//Multiplying 3x3 symmetric with 2x2 symmetric matrix
	//This will produce error.
	symMul = S1.mul(S2);
	cout << "Cannot Multiply 3x3 matrix with 2x2 matrix. Back to main.\n\n";
}
