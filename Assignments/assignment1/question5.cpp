#include <cstdlib>
#include <iostream>
using namespace std;

int GCD(int n, int m) {
    while (m != 0) {
        int remainder = n % m; //Gets the mod of the first two numbers 
        n = m; //Sets n the first number to be m which is the second number
        m = remainder; //Sets m the second number to be r which is the mod of the two initial numbers
    }
    return n;
}

int main() {
    int n = 80844;
    int m = 25320;
    int out = GCD(n, m);
    cout << "The GCD of " << n << " and " << m << " is " << out << endl;
}
