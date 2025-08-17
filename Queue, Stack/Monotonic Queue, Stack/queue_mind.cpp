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

// shortest subarray with a sum greater than or equal to k.
ll sho_sub(const vector<ll> &arr, ll k)
{
    // monotonic queue maintains the possibilities for becoming a left endpoint.
    ll n = arr.size(), h = 0, t = 0, ans = LLONG_MAX;
    ll dq[n + 1], sum[n + 1];
    memset(sum, 0, sizeof(sum));

    for (ll i = 0; i < n; i++)
    {
        // sum[0] = 0
        sum[i + 1] = sum[i] + arr[i];
    }

    for (ll i = 0; i <= n; i++)
    {
        while (h < t && sum[i] - sum[dq[h]] >= k)
        {
            ans = min(ans, i - dq[h++]);
        }

        while (h < t && sum[i] <= sum[dq[t - 1]])
        {
            t--;
        }

        dq[t++] = i;
    }

    return ans != LLONG_MAX ? ans : -1;
}

// points[i] = [xi, yi]; i < j → xi < xj; xj - xi <= k → max(yi + yj + |xi - xj|)
ll poin_max(vector<vector<ll>> &points, ll k)
{
    ll n = points.size(), h = 0, t = 0, ans = LLONG_MIN;
    ll dq[n][2]; // (x, y)

    // yi + yj + |xi - xj| → (xj + yj) + (yi - xi)
    for (ll i = 0, x, y; i < n; i++)
    {
        y = points[i][1], x = points[i][0];
        while (h < t && x - dq[h][0] > k)
        {
            h++;
        }

        if (h < t)
        {
            ans = max(ans, x + y + dq[h][1] - dq[h][0]);
        }

        while (h < t && y - x >= dq[t - 1][1] - dq[t - 1][0])
        {
            t--;
        }

        dq[t][0] = x;
        dq[t++][1] = y;
    }
}

// given n tasks and m workers, each worker can complete at most one task with a value greater than or equal to their strength. you have x pills, each providing the same strength boost,return  the maximum number of tasks that can be completed?
bool f(vector<ll> &task, vector<ll> &ker, ll pil, ll stg, ll tl, ll tr, ll kl, ll kr)
{
    // f returns whether it's possible to complete num tasks, using a greedy approach: matching the strongest workers with the easiest tasks.
    ll dq[10001];
    ll h = 0, t = 0, cnt = 0;

    for (ll i = kl, j = tl; i <= kr; i++)
    {
        while (j <= tr && ker[i] >= task[j])
        {
            dq[t++] = task[j++];
        }

        if (t > h && ker[i] >= dq[h])
        {
            h++;
        }
        else
        {
            cnt++;
            if (cnt > pil)
            {
                return false;
            }

            while (j <= tr && ker[i] + stg >= task[j])
            {
                dq[t++] = task[j++];
            }

            if (t > h)
            {
                t--;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}
ll task_ass(vector<ll> &task, vector<ll> &ker, ll pil, ll stg)
{
    ll n = task.size(), m = ker.size();
    ll l = 0, r = min(n, m), ans = 0;

    sort(task.begin(), task.end());
    sort(ker.begin(), ker.end());

    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (f(task, ker, pil, stg, 0, mid - 1, m - mid, m - 1))
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return ans;
}