#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#define ll long long
using namespace std;

// n stones, two people take turns picking up 1 to m stones, the person who takes the last stone wins.
// n % (m+1) != 0 ? fir : sec
const ll MAXN = 1001;
string dp[MAXN][MAXN];
string bao(ll n, ll m)
{
    if (n < 0)
    {
        return "fir";
    }
    if (n == 0)
    {
        return "sec";
    }
    if (!dp[n][m].empty())
    {
        return dp[n][m];
    }
    string ans = "sec";
    for (ll pick = 1; pick < m + 1; pick++)
    {
        if (bao(n - pick, m) == "sec")
        {
            ans = "fir";
            break;
        }
    }
    dp[n][m] = ans;
    return ans;
}

string bea(ll n, ll m)
{
    return n % (m + 1) != 0 ? "fir" : "sec";
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    random_device rd;
    mt19937 gen(rd());

    ll V = 500;
    ll times = 5000;
    cout << "Test Start!" << endl;
    for (ll i = 0; i < times; i++)
    {
        uniform_int_distribution<> dist(0, V - 1);
        ll n = dist(gen);
        uniform_int_distribution<> m_dist(1, V);
        ll m = m_dist(gen);

        for (ll j = 0; j <= n; ++j)
        {
            for (ll k = 0; k <= m; ++k)
            {
                dp[j][k] = "";
            }
        }

        if (bao(n, m) != bea(n, m))
        {
            cout << "error!" << endl;
            cout << "n = " << n << ", m = " << m << endl;
            cout << "bao(n, m) = " << bao(n, m) << ", bea(n, m) = " << bea(n, m) << endl;
            // break;
        }
    }
    cout << "Test Over!" << endl;
    return 0;
}

// n stones, two players take turns, each turn, player can take p^k stones, p prime and k non-negative, the person who takes the last stone wins.
// n % 6 != 0 ? fir : sec
string bea(ll n)
{
    return n % 6 != 0 ? "fir" : "sec";
}
