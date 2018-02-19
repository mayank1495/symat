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
	// template <typename scalar, int rows, int cols>
	// MATRIX_TEMPLATE
	Symat(const EIGEN_DYNAMIC_MATRIX_TYPE &);

	//Overloading () operator to return S(i,j)
	SType operator()(int, int);

	//Functions to add matrices
	//return types: eigenMatrix , Symat Matrix
	//Args: eigenMatrix, Symat Matrix
	// MATRIX_TEMPLATE
	// EIGEN_MATRIX_TYPE add(const EIGEN_MATRIX_TYPE &);

	// MATRIX_TEMPLATE
	// EIGEN_MATRIX_TYPE add(const SYMAT_MATRIX_TYPE &);

	EIGEN_DYNAMIC_MATRIX_TYPE add(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	EIGEN_DYNAMIC_MATRIX_TYPE add(const SYMAT_MATRIX_TYPE &);
	// template <typename scalar, int rows, int cols>
	// void add(const EIGEN_MATRIX_TYPE &); //Symat<X>
	// template <typename scalar, int rows, int cols>
	// EIGEN_MATRIX_TYPE add(const Symat<X> &);
	// // Symat<X> add(const Symat<X> &);

	//Functions to sub matrices
	// MATRIX_TEMPLATE
	EIGEN_DYNAMIC_MATRIX_TYPE sub(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	// MATRIX_TEMPLATE
	EIGEN_DYNAMIC_MATRIX_TYPE sub(const SYMAT_MATRIX_TYPE &);
	// MATRIX_TEMPLATE
	// SYMAT_MATRIX_TYPE sub(const EIGEN_MATRIX_TYPE &);
	// SYMAT_MATRIX_TYPE sub(const SYMAT_MATRIX_TYPE &);

	//Functions to mul matrices
	// MATRIX_TEMPLATE
	EIGEN_DYNAMIC_MATRIX_TYPE mul(const EIGEN_DYNAMIC_MATRIX_TYPE &);
	// MATRIX_TEMPLATE
	EIGEN_DYNAMIC_MATRIX_TYPE mul(const SYMAT_MATRIX_TYPE &);
	// MATRIX_TEMPLATE
	// SYMAT_MATRIX_TYPE mul(const EIGEN_MATRIX_TYPE &);
	// SYMAT_MATRIX_TYPE mul(const SYMAT_MATRIX_TYPE &);
};

//Constructor takes Eigen Matrix as parameter and iniializes the Symat Matrix
//with upper diognal of the Eigen Matrx
// MATRIX_TEMPLATE
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
	// cout << "In constructor..";
}

//Overloading () operator to behave as accessor for S(i,j)
SYMAT_TEMPLATE
SType SYMAT_MATRIX_TYPE::operator()(int i, int j)
{
	if (i > j)
		swap(i, j);
	int idx = ((i * s_dim) + j) - ((i * (i + 1)) / 2);
	// cout<<"\nix:"<<idx<<"; "<<endl;
	return s_vec[idx];
	// cout << "In op..";
}

SYMAT_TEMPLATE
EIGEN_DYNAMIC_MATRIX_TYPE SYMAT_MATRIX_TYPE::add(const EIGEN_DYNAMIC_MATRIX_TYPE &mat)
{
	Matrix<SType, Dynamic, Dynamic> temp;
	temp.resize(s_dim, s_dim);
	// 	// cout<<"k: "<<mat.rows()<<" "<<mat.cols()<<" ,..,.;"<<endl;
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

// SYMAT_TEMPLATE
// MATRIX_TEMPLATE
// EIGEN_MATRIX_TYPE SYMAT_MATRIX_TYPE::add(const EIGEN_MATRIX_TYPE &mat)
// {
// 	// cout<<"k: "<<rows<<" "<<cols<<" ,..,.;"<<endl;
// 	// EIGEN_MATRIX_TYPE temp;
// 	// const int r=mat.rows();
// 	// const int c=mat.rows();
// 	// Matrix<SType,r,c> temp;
// 	Matrix<SType, Dynamic, Dynamic> temp;
// 	temp.resize(s_dim, s_dim);
// 	// cout<<"k: "<<mat.rows()<<" "<<mat.cols()<<" ,..,.;"<<endl;
// 	if (s_dim == mat.rows() && s_dim == mat.cols())
// 	{
// 		for (int i = 0; i < s_dim; i++)
// 		{
// 			for (int j = 0; j < s_dim; j++)
// 			{
// 				temp(i, j) = mat(i, j) + this->operator()(i, j);
// 			}
// 		}
// 		return temp;
// 	}
// }

// template <typename X>
// template <typename scalar, int rows, int cols>
// void Symat<X>::add(const Matrix<scalar, rows, cols> &mat)
// {
//     Symat<X> temp;
//     X k;
//     // cout<<s_dim<<"s.."<<endl;
//     if (s_dim == mat.rows() && s_dim == mat.cols())
//     {
//         // cout<<"in if 1.."<<endl;
//         for (int i = 0; i < s_dim; i++)
//         {
//             // cout<<"in for 1.."<<endl;
//             for (int j = 0; j < s_dim; j++)
//             {
//                 // cout<<"\nin for 2.."<<endl;
//                 // k=mat(i,j);
//                 // cout<<k<<"+"<<this->operator()(i, j)<<"=";
//                 k = (mat(i, j) + this->operator()(i, j));
//                 cout << k << "; ";
//             }
//             cout << endl;
//         }
//         // cout<<"\nenddd..";
//     }
//     // cout<<"here..\n";
// }

int main()
{
	MatrixXf m(3, 3);
	Matrix<float, Dynamic, Dynamic> z;
	z.resize(3, 3);
	m << 1, 2, 3, 1, 2, 3, 1, 2, 3;
	z << 1, 1, 1, 1, 1, 1, 1, 1, 1;
	cout << m << endl
		 << endl;
	cout << z << endl
		 << endl;
	Symat<float> S(m);
	Symat<float> S2(z);
	Matrix<float, Dynamic, Dynamic> kk = S.add(z);
	cout << kk << endl;
	// S2.add(m);
	cout << "in main.." << endl;
}