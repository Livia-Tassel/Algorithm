#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <map>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;

// (i, j), A[i] <= A[j], then max(j - i)
ll max_ramp(const vector<ll> &arr)
{
    ll n = arr.size(), top = 0;
    ll s[n];
    s[top++] = 0;

    for (ll i = 1; i < n; i++)
    {
        if (arr[i] < arr[s[top - 1]])
        {
            s[top++] = i;
        }
    }

    ll ans = 0;
    for (ll i = n - 1; i >= 0; i--)
    {
        while (top > 0 && arr[i] >= arr[s[top - 1]])
        {
            ans = max(ans, i - s[top - 1]);
            top--;
        }
    }

    return ans;
}

// remove duplicate letters to ensure the lexicographically smallest result.
string dup_lex(string str)
{
    ll cnt[256] = {};
    char s[27];
    bool vis[27];
    memset(vis, 0, sizeof(vis));
    for (char ch : str)
    {
        cnt[ch]++;
    }

    ll top = 0;
    for (char ch : str)
    {
        if (!vis[ch])
        {
            while (top > 0 && ch < s[top - 1] && cnt[s[top - 1]] > 0)
            {
                vis[s[--top]] = false;
            }

            s[top++] = ch;
            vis[ch] = true;
        }

        cnt[ch]--;
    }

    string ans = "";
    for (ll i = 0; i < top; i++)
    {
        ans += s[i];
    }
    return ans;
}

// each round, the fish will simultaneously eat to their right the first fish that is smaller than themselves, after how many rounds will the number of fish remain unchanged?
ll big_fish(const vector<ll> &arr)
{
    ll n = arr.size(), ans = 0, top = 0;
    ll s[n][2];

    for (ll i = n - 1, turns; i >= 0; i--)
    {
        turns = 0;
        while (top > 0 && arr[i] > s[top - 1][0])
        {
            turns = max(turns + 1, s[--top][1]);
        }

        s[top][0] = arr[i];
        s[top++][1] = turns;

        ans = max(ans, turns);
    }

    return ans;
}

// 0/1 matrix, count the number of submatrices with all 1s.
ll histogram(const vector<ll> &hist)
{
    ll m = hist.size(), top = 0, ans = 0;
    ll s[m];

    for (ll i = 0, l, len, high; i < m; i++)
    {
        while (top > 0 && hist[i] <= hist[s[top - 1]])
        {
            ll t = s[--top];
            if (hist[t] > hist[i])
            {
                l = (top != 0 ? s[top - 1] : -1);
                len = i - l - 1;
                high = max(l != -1 ? hist[l] : 0, hist[i]);

                ans += (hist[t] - high) * len * (len + 1) / 2;
            }
        }
        s[top++] = i;
    }

    while (top > 0)
    {
        ll t = s[--top];
        ll l = (top != 0 ? s[top - 1] : -1);
        ll len = m - l - 1;
        ll high = l != -1 ? hist[l] : 0;

        ans += (hist[t] - high) * len * (len + 1) / 2;
    }

    return ans;
}

ll submatric(const vector<vector<ll>> &mat)
{
    ll ans = 0;
    ll n = mat.size();
    ll m = mat[0].size();
    vector<ll> hight(m, 0);

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            hight[j] = (mat[i][j] == 0 ? 0 : hight[j] + 1);
        }
        ans += histogram(hight);
    }

    return ans;
}

signed main()
{
    // vector<ll> arr = {3, 1, 4, 2, 5};
    // cout << max_ramp(arr) << endl;

    // cout << dup_lex("cbcdaffdbec") << endl;

    // vector<ll> arr = {8, 3, 1, 5, 6, 7, 2, 4};
    // cout << big_fish(arr) << endl;

    vector<vector<ll>> mat = {{1, 0, 1}, {1, 1, 0}, {1, 1, 0}};
    cout << submatric(mat) << endl;

    return 0;
}