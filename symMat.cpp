#include <bits/stdc++.h>
#include <Eigen/Dense>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// template <typename X>
// class SymMat
// {
//   private:
//     vector<X> v;

//     /*
//     1. A constructor to make a SymMat from an Eigen::Matrix
//     2. Accessors for S(i,j): S(j,i) should of course return the same as S(i,j)
//     3. Functions for matrix addition:
//         SymMat +/- SymMat
//         SymMat +/- Eigen::Matrix
//     4. Functions for matrix multiplication:
//         SymMat∗SymMat
//         SymMat∗Eigen::Matrix
//     */
//   public:
//     // SymMat(MatrixXi m){
//     //     cout<<"Eh..";
//     // }
//     SymMat(const DenseBase<X>&);
//     void display();
// };

// template <typename Derived>
// SymMat<Derived>::SymMat(const DenseBase<Derived>& m) //const DenseBase<X>&
// {
//     // for (int i = 0; i < m.rows(); i++)
//     //     for (int j = 0; j < m.cols(); j++)
//     //     {
//     //         v.push_back(m(i, j));
//     //     }
//     cout<<"hello..";
// }

// template <typename X>
// void SymMat<X>::display()
// {
//     for (int i = 0; i < v.size(); i++)
//         cout << v[i] << " ";
//     cout<<endl;
// }

// template <typename X, int r, int c>
// class SymMat
// {
//   private:
//     vector<X> v;

//   public:
//     SymMat(Matrix<X, r, c);
//     void display();
// };

// template <typename X, int r, int c>
// SymMat<X>::SymMat(Matrix<x,r,c> m)//const Matrix<X, r, c> &m
// {
//     //  for (int i = 0; i < m.rows(); i++)
//     //     for (int j = 0; j < m.cols(); j++)
//     //     {
//     //         v.push_back(m(i, j));
//     //     }
//     cout<<"hello..";
// }

template <typename a>
class SymMat
{
    vector<a> v;

  public:
    template <typename X, int r, int c>
    SymMat(const Matrix<X, r, c>& m)
    {
        cout << "hello.."<<m.rows()<<m.cols()<<endl;
        // m=m+m;
        cout<<m<<endl;
        cout<<r<<endl;
    }
};

int main()
{
    //Eigen matrix examples;
    Matrix<long long,2,2> m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << m << std::endl;
    cout << m.rows() << endl;
    SymMat<int> s(m);
    // SymMat<int,m.rows(),m.cols() ) s(m);
    // SymMat<int> s(m);
    // s.display();
}