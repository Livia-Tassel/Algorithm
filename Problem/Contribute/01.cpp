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

// determine whether it is ok to modify the [l, r] interval to make the number of "01" subsequences in s equal to the number of "10" subsequences.
void solve()
{
    ll n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;
    l--;
    r--;

    // Σ{i<j, s[i]=0, s[j]=1} ==  Σ{i<j, s[i]=1, s[j]=0}
    // aᵢ = 1, if s[i] = '1', aᵢ = 0, if s[i] = '0'
    // Σ{i<j} (1 - aᵢ) * aⱼ == Σ{i<j} aᵢ * (1 - aⱼ)
    // Σ{i<j} (aⱼ - aᵢ)
    vl a(n);
    for (ll i = 0; i < n; ++i)
    {
        a[i] = s[i] - '0';
    }

    // for k, (k - (n - 1 - k)) * aₖ = (2k - n + 1) * aₖ, k = 0...n-1
    // Σ(aₖ * (2k - n + 1)) = 0, k = 0...n-1
    vl d(n);
    for (ll k = 0; k < n; ++k)
    {
        d[k] = 2 * k - n + 1;
    }

    vl pad(n + 1, 0); // pre of a[k] * d[k]
    vl pdn(n + 1, 0); // pre of negative number of d[k]
    vl pdp(n + 1, 0); // pre of positive number of d[k]

    for (ll k = 0; k < n; ++k)
    {
        pad[k + 1] = pad[k] + a[k] * d[k];
        pdn[k + 1] = pdn[k] + (d[k] < 0 ? d[k] : 0);
        pdp[k + 1] = pdp[k] + (d[k] > 0 ? d[k] : 0);
    }

    // FixedSum
    ll fs = pad[l] + pad[n] - pad[r + 1]; // [0...l-1] + [r+1...n-1]
    // Target
    ll tar = -fs;

    // [min_sum, max_sum]
    // -7 -5 -3 -1 1 3 5
    ll mns = pdn[r + 1] - pdn[l];
    ll mxs = pdp[r + 1] - pdp[l];

    bool ok = false;
    if (tar >= mns && tar <= mxs)
    {
        // (Target - min_sum) % 2 == 0
        // get -15, -13, -11, -9, -7, -5, -3, -1, 1, 3, 5, 7, 9
        if ((tar - mns) % 2 == 0)
        {
            ok = true;
        }
    }

    if (ok)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}