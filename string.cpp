#define _GLIBCXX_DEBUG
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>
#include <list>

using namespace std;

vector<string> splitAll(string s, string t) {
  vector<string> v;
  for (size_t p = 0; (p = s.find(t)) != s.npos; ) {
    v.push_back(s.substr(0, p));
    s = s.substr(p + t.size());
  }
  v.push_back(s);
  return v;
}

int sscanf_valid(void) {
  int year, day, hour, minute;
  char month_c[10];
  string str = "January 01, 2001 12:04";
  sscanf(str.c_str(), "%s %d, %d %d:%d", month_c, &day, &year, &hour, &minute);
  string month(month_c);
  if (month == "January" && day == 1 && year == 2001 && hour == 12 && minute == 4) {
    return 1;
  }
  return 0;
}
int main() {
  vector<int> vi(3, 0);
  vector<string> vs;
  string t = "rarara | rarere | rere";
  vs = splitAll(t, " | ");
  vector<string> vs2;
  vs2.push_back("rarara");
  vs2.push_back("rarere");
  vs2.push_back("rere");
  if (vs == vs2) {
    cout << "splitAll ok." << endl;
  } else {
    cout << "splitAll NG." << endl;
    exit(1);
  }

  if (sscanf_valid()) {
    cout << "sscanf ok." << endl;
  } else {
    cout << "sscanf ng." << endl;
    exit(1);
  }

  return 0;
}
