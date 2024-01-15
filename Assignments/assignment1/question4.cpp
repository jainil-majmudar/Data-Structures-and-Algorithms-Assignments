#include <cstdlib>
#include <iostream>
using namespace std;

int count(double x) {
    int counter = 0;
    while (x >= 2) { 
        x /= 2; //Dividing by 2 and setting the new value to be x
        counter++;
    }
    return counter;
}

int main() {
    double x = 1982.345;
    int out = count(x);
    cout << "The number of times that " << x << " can get divided is " << out << endl;
}
