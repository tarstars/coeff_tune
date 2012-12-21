#include <iostream>
#include <vector>

#include <Eigen/Dense>

using ::std::ostream;
using ::std::cout;
using ::std::endl;
using ::std::vector;

using ::Eigen::MatrixXd;

void calculateRoots(vector<double> coeffs){
  
  if (0 == coeffs.size()) {
    throw "Array with the coefficients of the polynomial is empty!";
  }
  else if (1 == coeffs.size()) {
    throw "No roots to find. Polynomial power is zero";
  }
  
  int poly_power = coeffs.size();
  int matrix_size = poly_power - 1;
  double C1 = coeffs[0];
  
  if (matrix_size < 1) {
    throw "pechal'ka...";
  }
  
  cout << "Polynomial power: " << poly_power << endl;
  cout << "Highest power coefficient: " << C1 << endl;
  
  MatrixXd companion_matrix(matrix_size, matrix_size);
  
  for (int i = 0; i < matrix_size; ++i) {
    for (int j = 0; j < matrix_size - 1; ++j) {
      companion_matrix(i, j) = (int)(i == j + 1);
    }
    
    companion_matrix(i, matrix_size - 1) = (-1)*coeffs[matrix_size - i]/C1;
  }
  
  cout << "Companion matrix:" << endl << companion_matrix << endl;
  
  ::Eigen::EigenSolver<MatrixXd> solver;
  solver.compute(companion_matrix, /* computeEigenvectors = */ false);
  
  cout << endl << "Eigenvalues:" << solver.eigenvalues().transpose() << endl;
}

// using namespace ::Eigen;

// typedef ::std::vector<double> VectorXd;

//  Pretty printing
// ostream&  operator<<(ostream& os, const VectorXd& v) {
  // cout << "zzz" << v.length();
  
  // return os;
// }

int main() {

  // auto a = vector<double>{1, 2, 3};
  
  // cout << a.size() << endl;
  
  calculateRoots(vector<double>{1, -7, 17, -17, 6});
  // int m_size = 3;
  
  // MatrixXd test1(m_size, m_size);
  
  // for (int i = 0; i < m_size; ++i) {
    // for (int j = 0; j < m_size; ++j) {
      // if (i != j) {
        // test1(i, j) = 0;
      // }
      // else {
        // test1(i, j) = 1;
      // }
    // }
  // }
  
  // test1(0, 2) = 1;
  // test1(1, 2) = 2;
  
  // EigenSolver<MatrixXd> solver;
  // solver.compute(test1, /* computeEigenvectors = */ false);
  
  // cout << test1 << endl;
  // cout << "The eigenvalues of A are: " << solver.eigenvalues().transpose() << endl;
  
  // calculateRoots(vector<double>{1, 2, 1});
  
  
  // EigenSolver<MatrixXf> es;
// MatrixXf A = MatrixXf::Random(4,4);
// es.compute(A, /* computeEigenvectors = */ false);
// cout << "The eigenvalues of A are: " << es.eigenvalues().transpose() << endl;
// es.compute(A + MatrixXf::Identity(4,4), false); // re-use es to compute eigenvalues of A+I
// cout << "The eigenvalues of A+I are: " << es.eigenvalues().transpose() << endl;
  
  // test1(0, 0) = 1;
  // test1(1, 1) = 2;
  
  // test1(1, 0) = 0;
  // test1(0, 1) = 0;
  
  // SelfAdjointEigenSolver<MatrixXd> eigensolver(test1);
  
  // if (eigensolver.info() != Success) abort();
  // zzz << 1, 2, 3, 4, 5, 6;
  
  // cout << test1;
  // cout << eigensolver.eigenvalues() << endl;
// Matrix2f A;
// A << 1, 2, 2, 3;
// cout << "Here is the matrix A:\n" << A << endl;
// SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
// if (eigensolver.info() != Success) abort();
// cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() << endl;
// cout << "Here's a matrix whose columns are eigenvectors of A \n"
// << "corresponding to these eigenvalues:\n"
// << eigensolver.eigenvectors() << endl;

  return 0;
}
