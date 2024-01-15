#include <cstdlib>
#include <iostream>
using namespace std;

class Progression { 
 public:
  Progression(long f = 0) //Constructor
      : first(f), cur(f) {}
  virtual ~Progression(){}; //Destructor
  void printProgression(int n); //Prints the first n values
 protected:
  virtual long firstValue();  
  virtual long nextValue();   
 protected:
  long first; 
  long cur;   
};

void Progression::printProgression(int n) {
  cout << firstValue();                  
  for (int i = 2; i <= n; i++)               
    cout << ' ' << nextValue();
  cout << endl;
}

long Progression::firstValue() {  
  cur = first;
  return cur;
}
long Progression::nextValue() { 
  return ++cur;
}

class AbsoluteProgression : public Progression {
    public:
        AbsoluteProgression(long x = 2, long y = 200);
        virtual long nextValue();
    protected:
        long first, second;
};

AbsoluteProgression::AbsoluteProgression(long x, long y): Progression(y), first(x), second(y) {} //Constructor

long AbsoluteProgression::nextValue() {
    long absVal = abs(first - second);
    first = second;
    second = absVal;
    return second;
}

int main() {
    Progression *x;
    cout << "Absolute progression with default constructor:\n";
    x = new AbsoluteProgression();
    x->printProgression(10);
    cout << "Absolute progression with 3 and 300:\n";
    x = new AbsoluteProgression(3, 300);
    x->printProgression(10);
    return EXIT_SUCCESS;
}