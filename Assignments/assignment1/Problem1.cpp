#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

/*int LinearSum(vector<int> A, int n) {
  if (n == 1) {
    return A[0];
  }
  return A[n-1] + LinearSum(A, n-1);
}*/

int LinearSum(vector<int> A, int n, int sum = 0) {
  if (n == 0) {
    return sum;
  }
  return LinearSum(A, n-1, sum += A[n-1]);
}

int main() {
  vector<int> A = {1,2,3,4,5};
  //cout << "Without tail recursion " << LinearSum(A, 4) << endl;
  cout << "With tail recursion " << LinearSum(A, 5, 0) << endl;
}