#include <cstdlib>
#include <iostream>
#include <stdbool.h>
#include <time.h>
using namespace std;

int* BirthdayMaker(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        int birthday = rand() %365 +1; //Generates random integers from 1 to 365
        arr[i] = birthday;
    }
    return arr;
}

int BirthdayCheck(int arr[],int n) {
    bool state = false;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] == arr[j]) {
                return 1;
                state = true;
            }
        }
    }
    if (state == false) {
        return 0;
    }

}

void BirthdayParadox() {
    int e = 100;
    for (int n = 5; n <= 100; n += 5) { //Groups of 5,10,15..100
        int c = 0;
        for (int i = 0; i < 100; i++) {
            int* arr = BirthdayMaker(n);
            int check = BirthdayCheck(arr,n);
            c += check;
            delete[] arr;
        }
        cout << n << "," << c << "," << (float)c/(float)e << endl;
    }
}
int main() {
    srand(time(0));
    BirthdayParadox();
}
