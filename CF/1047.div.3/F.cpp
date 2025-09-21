#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn = 200005;
const int maxv = 400005;

int a[maxn], b[maxn];
int sgt[4 * maxv];
int n;

void update(int nd, int st, int ed, int idx, int val)
{
    if (st == ed)
    {
        sgt[nd] = max(sgt[nd], val);
        return;
    }
    int mid = (st + ed) / 2;
    if (st <= idx && idx <= mid)
    {
        update(2 * nd, st, mid, idx, val);
    }
    else
    {
        update(2 * nd + 1, mid + 1, ed, idx, val);
    }
    sgt[nd] = max(sgt[2 * nd], sgt[2 * nd + 1]);
}

int query(int nd, int st, int ed, int l, int r)
{
    if (r < st || ed < l || l > r)
    {
        return 0;
    }
    if (l <= st && ed <= r)
    {
        return sgt[nd];
    }
    int mid = (st + ed) / 2;
    return max(query(2 * nd, st, mid, l, r), query(2 * nd + 1, mid + 1, ed, l, r));
}

void solve()
{
    cin >> n;
    int max_val = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        max_val = max(max_val, b[i]);
    }
    fill(sgt, sgt + 4 * max_val + 4, 0);

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ll count_l = 0;
        if (a[i] == b[i])
        {
            count_l = i;
        }
        else if (a[i] < b[i])
        {
            count_l = query(1, 1, max_val, b[i], max_val);
        }
        else
        { // a[i] > b[i]
            count_l = query(1, 1, max_val, a[i], max_val);
        }
        ans += count_l * (ll)(n - i + 1);
        update(1, 1, max_val, a[i], i);
    }

    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    } 
    return 0;
}

// brute force O(n^3)
// a[l,...,r], b[l,...,r]
// a_i > p_max, if a_i == b_i, then +1
// a_i <= p_max, if b_i <= p_max, then +1

// contribution
// consider the contribution of position i to total ans.
// ∑∗i = count_l(i) x (n−i+1)
// if a_i == b_i, then +1
// if a_i > b_i && a_i <= p_max, then +1  →  count_l = p, p = max(k∣k < i, a_k ≥ a_i)  →  seg_tree
// if a_i < b_i && b_i <= p_max, then +1  →  count_l = p, p = max(k∣k < i, a_k ≥ b_i)  →  seg_tree