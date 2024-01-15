#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

void minAndMax(vector<int>& A, int& min, int& max, int i) {
    if (i == A.size()) {
        return;
    }
    if (A[i] < min) { // sets a number lower than min to min 
        min = A[i];
    }
    if (A[i] > max) { // sets a number higher than max to max 
        max = A[i];
    }
    minAndMax(A, min, max, i + 1);
}

int main() {
    vector<int> A = {1, -2, 0, 6, 66, -7};
    int min = A[0];
    int max = A[0];
    minAndMax(A, min, max, 0);
    cout << "Min " << min << " Max " << max << endl;
    return 0;
}
