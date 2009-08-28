#include <iostream>
using namespace std;

int main() {
  int years = 3000 - 2001 + 1;
  cout << ((365 * years + (1000/4) - (1000/100) + (1000/400)) / 7) << endl;
}
