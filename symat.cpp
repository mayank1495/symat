#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
/*
Eigen matrix M;
Symat S(m);
S.display()--> sym matrix
S(i,j)==S(j,i);
Add/Sub: S1+/-S2  S+/-M
MUL: S1*S2  S*M
*/

//NOT NEEDED ?
#define MATRIX_TEMPLATE template <typename scalar, int rows, int cols>
#define EIGEN_MATRIX_TYPE Matrix<scalar, rows, cols>

#define SYMAT_TEMPLATE template <typename SType>
#define SYMAT_MATRIX_TYPE Symat<SType>
#define EIGEN_DYNAMIC_MATRIX_TYPE Matrix<SType, Dynamic, Dynamic>

// #define SYMAT_MATRIX_TYPE Symat<Stype>

// template <typename SType>
SYMAT_TEMPLATE
class Symat
{

  private:
	//vector to store upper triangle matrix
	vector<SType> s_vec;
	//Variable to store dimension of the symmetric matrix
	int s_dim;
	//Function to check validity
	//??

  public:
	//Default constructor
	Symat() {}

	//Constructor to initialize symmetric matrix from Eigen::Matrix
	Symat(const EIGEN_DYNAMIC_MATRIX_TYPE &);

	//Overloading () operator to return S(i,j)
	SType operator()(int, int) const;

	//Accessor function for s_dim
	int dim() const { return s_dim; }

	//Functions to add matrices
	EIGEN_DYNAMIC_MATRIX_TYPE add(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE add(const SYMAT_MATRIX_TYPE &);

	//Functions to sub matrices
	EIGEN_DYNAMIC_MATRIX_TYPE sub(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE sub(const SYMAT_MATRIX_TYPE &);

	//Functions to mul matrices
	EIGEN_DYNAMIC_MATRIX_TYPE mul(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE mul(const SYMAT_MATRIX_TYPE &);

	//overloading ostream << operator to cout<<S
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

//Constructor takes Eigen Matrix as parameter and iniializes the Symat Matrix
//with upper diognal of the Eigen Matrx
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

//Overloading () operator to behave as accessor for S(i,j)
SYMAT_TEMPLATE
SType SYMAT_MATRIX_TYPE::operator()(int i, int j) const
{
	if (i > j)
		swap(i, j);
	int idx = ((i * s_dim) + j) - ((i * (i + 1)) / 2);

	return s_vec[idx];
}

//Add() Function takes Eigen Matrix as parameter, creates a temp eigen matrix
//and adds symat matrix
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

//Add() function takes Symat matrix as input and adds
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

//Sub() Function takes Eigen Matrix as parameter, creates a temp eigen matrix
//and subs symat matrix
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

//Sub() function takes Symat matrix as input and subs
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

//Mul function takes Eigen matrix and multiples
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

//Mul function takes Symat matrix and multiples
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

// SYMAT_TEMPLATE
// ostream &operator<<(ostream &out, const SYMAT_MATRIX_TYPE &s_mat)
// {
// 	// int dim=s_mat.dim();
// 	for (int i = 0; i < s_mat.s_dim; i++)
// 	{
// 		for (int j = 0; j < s_mat.s_dim; j++)
// 		{
// 			cout << s_mat(i, j) << " ";
// 		}
// 		cout << endl;
// 	}
// 	cout << endl;
// }

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
	cout<<"S:\n"<<S;
	cout<<"S2:\n"<<S2;
	Matrix<float, Dynamic, Dynamic> kk = S.mul(z);
	// MatrixXf kk = S.add(S2);
	cout << kk << endl;
	// S2.add(m);
	cout << "in main.." << endl;
}