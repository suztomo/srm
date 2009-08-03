#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>
#include <list>
#include <iomanip>
#include "cout.h"

using namespace std;


int precision_sample(void){
  double t = 1.2345678;
  stringstream ss;
  ss << fixed << setprecision(5) << t;

  assert(ss.str() == "1.23457");

  ss.clear();
  ss << scientific << t;

  assert(ss.str() == "1.234571.23457e+00");

  cout << "setprecision ok." << endl;
  return 0;
}

int main() {
  precision_sample();
  return 0;
}
