// BEGIN CUT HERE
#define _GLIBCXX_DEBUG
// END CUT HERE
#line $NEXTLINENUMBER$ "$FILENAME$"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>
#include <list>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
#define Fill(a, b) memset((a), (b), sizeof(a))
#define REP(a, b) for (size_t (a) = 0; (a)<(size_t)(b); ++(a))
#define sz size()
#define Tr(c, i) for(typeof((c).begin()) i= (c).begin(); (i) != (c).end(); ++(i))
#define All(c) (c).begin(), (c).end()
#define Present(c, x) ((c).find(x) != (c).end()) // for Map or Set
#define CPresent(c, x) (find(All(c), x) != end()) // for vector

class $CLASSNAME$ {
public:
  $RC$ $METHODNAME$($METHODPARMS$) {
    $RC$ ret;
    return ret;
  }
};
$TESTCODE$


