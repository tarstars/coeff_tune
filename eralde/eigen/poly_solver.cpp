#include <iostream>
#include <vector>

#include <Eigen/Dense>

using ::std::ostream;
using ::std::cout;
using ::std::endl;
using ::std::vector;

using ::Eigen::MatrixXd;

//  Calculates polynomial roots by finding eigenvalue of it's companion matrix.
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

int main() {
  calculateRoots(vector<double>{1, -7, 17, -17, 6});
  
  calculateRoots(vector<double>{1, 2, 1});
  
  calculateRoots(vector<double>{1, 0, 0, 1});
  
  return 0;
}
