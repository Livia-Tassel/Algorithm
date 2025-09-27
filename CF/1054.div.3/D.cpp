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
ll eve;
ll cnt_l(string s, char ch, ll mid)
{
    ll ans = 0, cnt = 0;
    for (ll i = mid - 1; i >= 0; i--)
    {
        if (s[i] == ch)
        {
            ans += mid - i - cnt - 1;
            cnt++;
        }
    }
    return ans;
}
ll cnt_r(string s, char ch, ll mid)
{
    ll ans = 0, cnt = 0;
    for (ll i = mid + 1; i < s.length(); i++)
    {
        if (s[i] == ch)
        {
            ans += i - mid - cnt - 1;
            cnt++;
        }
    }
    return ans;
}
ll fm(string s, char ch, ll chn)
{
    if (chn == 0)
        return -1;

    if (chn % 2 == 1)
    {
        for (ll i = 0, cnt = 0; i < s.length(); i++)
        {
            cnt += (s[i] == ch ? 1 : 0);
            if (cnt == (chn + 1) / 2)
            {
                return i;
            }
        }
    }
    else
    {
        ll dex = -1, flag = 1;
        for (ll i = 0, cnt = 0; i < s.length(); i++)
        {
            cnt += (s[i] == ch ? 1 : 0);
            if (flag && cnt == chn / 2)
            {
                dex = i;
                flag = 0;
                // cout << "ch: " << ch << ", dex: " << dex << endl;
            }
            if (cnt == chn / 2 + 1)
            {
                eve = i;
                return dex;
            }
        }
    }
}
ll check(string s, char ch, ll chn)
{
    ll dex = fm(s, ch, chn);

    if (dex == -1)
        return 0;

    ll ans = 0;
    ans += cnt_l(s, ch, dex) + cnt_r(s, ch, dex);
    if (chn % 2 == 0)
    {
        ans = min(ans, cnt_l(s, ch, eve) + cnt_r(s, ch, eve));
    }
    return ans;
}

ll solve(ll n)
{
    string s;
    cin >> s;
    ll ca = 0, cb = 0;
    for (char ss : s)
        ss == 'a' ? ca++ : cb++;

    // cout << "ca: " << ca << ", cb: " << cb << ", ansa: " << check(s, 'a', ca) << ", ansb: " << check(s, 'b', cb) << endl;
    return min(check(s, 'a', ca), check(s, 'b', cb));
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << solve(n) << endl;
    }
}
