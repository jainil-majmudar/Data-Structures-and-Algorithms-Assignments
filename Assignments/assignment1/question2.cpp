#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    double *dp[10]; //Declaring an array of pointers with a size of 10 so 10 pointers
    for (int i = 0; i < 10; i++) {
        dp[i] = new double; //Allocating memory 
        *dp[i] = 0.0; //Assigning value 0.0 
        cout << "The value at index " << i << " is " << *dp[i] << endl;
    }
    for (int i = 0; i < 10; i++) {
        delete dp[i]; //Deleting the allocated memory
    }
}
