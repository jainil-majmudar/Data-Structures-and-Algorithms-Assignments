#include <cstdlib>
#include <iostream>
using namespace std;

int minValue() {
    int n, first, x;
    cout << "Input the number of elements in the list, the index of the first element, and the integer value of the minimum:" << endl;
    cin >> n >> first >> x;

    int value, next;
    int array[2][n];
    cout << "Input the node's value, and the node it points to: " << endl;
    for (int i = 0; i < n; i++) { // construct list representation with arrays
        cin >> value >> next;
        array[0][i] = value;
        array[1][i] = next;
    }
    int min = -1;
    int curr = first;
    while (curr != -1) { // while curr is not the tail/end
        if (array[0][curr-1] >= x && (array[0][curr-1] < min || min == -1)) { // if the value is greater than x and less than the min then it changes the min 
            min = array[0][curr-1];
        }
        curr = array[1][curr-1];
    }
    return min;
}

int main() {
  int output = minValue();
  cout << "The minimum value is: " << output << endl;
}
