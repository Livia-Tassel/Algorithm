#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#define ll long long
using namespace std;

// f(i, from, to, other), means 1~i move from → to
// f(i-1, from, other, to) + i move from → to + f(i-1, other, to, from)
void f(ll i, string from, string to, string other)
{
    if (i == 1)
    {
        cout << "bang " << i << " from " << from << " move to " << to << endl;
    }
    else
    {
        f(i - 1, from, other, to);
        cout << "bang " << i << " from " << from << " move to " << to << endl;
        f(i - 1, other, to, from);
    }
}

void hanoi(ll n)
{
    f(n, "left", "mid", "right");
}

signed main()
{
    hanoi(10);
}