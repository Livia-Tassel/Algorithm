#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;
using ll = long long;
using vl = vector<ll>;

vl pows(18);
unordered_map<ll, ll> memo;

// sum_digits from 1 to n
// (logn)^2
ll sd(ll n)
{
    if (n < 0)
        return 0;
    if (n < 10)
        return n * (n + 1) / 2;

    if (memo.count(n))
    {
        return memo[n];
    }

    string s = to_string(n);
    ll d = s.length();
    ll p10 = pows[d - 1];
    ll fd = s[0] - '0';
    ll rem = n % p10;

    ll res = 0;

    res += (d - 1) * 45 * pows[d - 2];
    res += (fd - 1) * fd / 2 * p10;
    res += (fd - 1) * sd(p10 - 1);
    res += fd * (rem + 1);
    res += sd(rem);

    return memo[n] = res;
}

void solve()
{
    ll k;
    cin >> k;

    ll ans = 0, d = 1;
    while (true)
    {
        ll num = 9 * pows[d - 1];
        num *= d;

        if (k > num)
        {
            ll st = pows[d - 1];
            ll ed = pows[d] - 1;
            ans += sd(ed) - sd(st - 1);
            k -= num;
            d++;
        }
        else
        {
            ll con = (k - 1) / d;
            ll st = pows[d - 1];
            ll ed = st + con - 1;

            if (con > 0)
            {
                ans += sd(ed) - sd(st - 1);
            }

            ll rem = (k - 1) % d + 1;
            ll fin = ed + 1;
            string s = to_string(fin);
            for (ll i = 0; i < rem; ++i)
            {
                ans += s[i] - '0';
            }
            break;
        }
    }
    cout << ans << endl;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    pows[0] = 1;
    for (ll i = 1; i < 18; ++i)
    {
        pows[i] = pows[i - 1] * 10;
    }

    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}