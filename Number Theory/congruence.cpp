#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;

// ((a+b) + (c+d)) % mod = ((a+b) % mod + (c+d) % mod) % mod
// ((a*b) * (c*d)) % mod = ((a*b) % mod * (c*d) % mod) % mod
// (a-b) % mod = (a % mod - b % mod + mod) % mod