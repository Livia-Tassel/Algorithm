#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <numeric>
#include <unordered_map>
#define ll long long
using namespace std;
using vl = vector<ll>;
const ll maxn = 2e5 + 5;
const ll mod = 1e9 + 7;

vl p2(maxn);
void build()
{
    p2[0] = 1;
    for (int i = 1; i < maxn; i++)
        p2[i] = (p2[i - 1] * 2) % mod;
}

void solve()
{
    // sᵥ = Σ{u ∈ subtree(v)}aᵤ
    // sᵥ = Σ{u ∈ subtree(v)} (1 + (aᵤ - 1)) = (Σ1) + (Σ(aᵤ - 1))
    // vert(u) + kᵤ != vert(v) + kᵥ, where kᵤ means the number of vertices whose value is 2.
    ll n;
    cin >> n;
    // ```latex
    // $$
    // \begin{cases}
    // 0 & \text{if } cnt > 2 \\
    // 2^n & \text{if } cnt = 1 \\
    // (2^{\text{depth}_y - \text{depth}_x} + 2^{\text{depth}_y - \text{depth}_x - 1}) \cdot 2^{\text{depth}_v} & \text{if } cnt = 2 \text{ and } \text{depth}_x < \text{depth}_y \\
    // 2^{\text{depth}_v} + 2^{\text{depth}_v} & \text{if } cnt = 2 \text{ and } \text{depth}_x = \text{depth}_y
    // \end{cases}
    // $$

    // ```
}
signed main()
{
    build();
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}