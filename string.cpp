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

#include "cout.h"
using namespace std;



/*
  The longest parindrome.... imifu.
  http://www.prefield.com/algorithm/
 */
int longest_palindrome(const char *text, int n) {

  int rad[2*n], i, j, k;
  for (i = 0, j = 0; i < 2*n; i += k, j = max(j-k, 0)) {
    while (i-j >= 0 && i+j+1 < 2*n && text[(i-j)/2] == text[(i+j+1)/2]) ++j;
    rad[i] = j;
    for (k = 1; i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k; ++k)
      rad[i+k] = min(rad[i-k], rad[i]-k);
  }
  return *max_element(rad, rad+2*n); // ret. centre of the longest palindrome
}

bool long_parindrome_valid(void) {
  string t = "hogefugagufizifdfdkj";
  if (longest_palindrome(t.c_str(), t.size()) == 7) {
    cout << "longest_palindrome ok." << endl;
  } else {
    cout << "longest_palindrome NG." << endl;
    exit(1);
  }
  return true;
}

struct Trie {
  int value;
  Trie *next[0x100]; // 16 * 16 + 1, including ascii.
  Trie() { fill(next, next+0x100, (Trie*)0); }
};

Trie *trie_find(char *t, Trie *r) {
  for (int i = 0; t[i]; ++i) {
    char c = t[i];
    if (!r->next[(int)c]) r->next[(int)c] = new Trie;
    r = r->next[(int)c];
  }
  return r;
}

bool trie_valid(void) {
  Trie* t = new Trie, *t1;
  t1 = trie_find("suzuki", t);
  t1->value = 3;
  t1 = trie_find("suzukitomo", t);
  t1->value = 5;
  t1 = trie_find("suzuku", t);
  t1->value = 4;

  t1 = trie_find("suzuki", t);
  if (t1->value == 3 && trie_find("suzukitomo", t)->value == 5
      && trie_find("suzuku", t)->value == 4) {
  } else {
    exit(1);
  }
  return 1;
}

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

bool match(const char *text, const char *pattern) {
  switch (*pattern) {
    case '\0': return !*text;
    case '*' : return match(text, pattern+1) ||
                      *text && match(text+1, pattern);
    case '?' : return *text && match(text+1, pattern+1);
    default  : return (*text == *pattern) &&
                      match(text+1, pattern+1);
  }
}

bool match_valid(void) {
  string a = "suzukitomohirodfasdadie";
  string b = "*hiro??as*ie";
  if (match(a.c_str(), b.c_str())) {
    cout << "match ok." << endl;
  } else {
    cout << "match ng." << endl;
    exit(1);
  }
  return true;
}

bool ss_verify(void) {
  string s = "LOVE=3tako+9mikan+12orange";
  for(size_t k=0; k<s.size(); ++k) if (s[k] == '=' || s[k]=='+') s[k] = ' ';
  stringstream ss(s);
  string left, item;
  int n;
  int param[3];
  vector<string> items;
  size_t i=0;
  ss>>left;
  assert(left == "LOVE");
  while(ss>>n>>item) {
    param[i++] = n;
    items.push_back(item);
  }
  if (items[0] == "tako" && items[1] == "mikan" && items[2] == "orange") {
  } else {
    assert(0);
  }
  if (param[0] == 3 && param[1] == 9 && param[2] == 12) {
  } else {
    assert(0);
  }
  return true;
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

  if (!match_valid()) {
    exit(1);
  }
  if (!trie_valid()) {
    cout << "trie ok" << endl;
  }
  if (!long_parindrome_valid()) {
    cout << "long_parindrome ok." << endl;
  }
  if (ss_verify()) {
    cout << "string stream ok." << endl;
  }
  return 0;
}

