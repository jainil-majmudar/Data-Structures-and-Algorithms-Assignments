#include <cstdlib>
#include <iostream>
using namespace std;

template <typename X, typename Y>
class Pair {
private:
    X val1;
    Y val2;

public:
    Pair(X first, Y second) : val1(first), val2(second) {} //Constructor 

    void print() {
        cout << "<" << val1 << ", " << val2 << ">" << endl;
        return;
    }
};

int main() {
    Pair<int, double> p1(1, 7.3);
    p1.print();
    Pair<string, double> p2("hello", 7.7);
    p2.print();
    Pair<float, long> p3(1.2, 777777773);
    p3.print();;
    return 0;
}
