#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
#define ll long long
using namespace std;

void swap(vector<string> &strs, ll i, ll j)
{
    string tmp = strs[i];
    strs[i] = strs[j];
    strs[j] = tmp;
}

void f(vector<string> &strs, ll i, vector<string> &ans)
{
    if (i != strs.size())
    {
        for (ll j = i; j < strs.size(); j++)
        {
            swap(strs, i, j);
            f(strs, i + 1, ans);
            swap(strs, i, j);
        }
    }
    else
    {
        stringstream ss;
        for (const string &s : strs)
        {
            ss << s;
        }
        ans.push_back(ss.str());
    }
}

string bao(vector<string> strs)
{
    vector<string> ans;
    f(strs, 0, ans);
    sort(ans.begin(), ans.end());
    return ans[0];
}

string bea(vector<string> &strs)
{
    sort(strs.begin(), strs.end(), [](const string &a, const string &b)
         { return a + b < b + a; });
    stringstream ss;
    for (ll i = 0; i < strs.size(); i++)
    {
        ss << strs[i];
    }
    return ss.str();
}

// random string
string rand_str(ll m, ll v)
{
    ll len = (rand() % m) + 1;
    string ans(len, ' ');
    for (ll i = 0; i < len; i++)
    {
        ans[i] = (char)('a' + (rand() % v));
    }
    return ans;
}

vector<string> rand_str_arr(ll n, ll m, ll v)
{
    ll size = (rand() % n) + 1;
    vector<string> ans(size);
    for (ll i = 0; i < ans.size(); i++)
    {
        ans[i] = rand_str(m, v);
    }
    return ans;
}

signed main()
{
    srand(time(0));
    ll n = 8; // number
    ll m = 5; // length
    ll v = 4; // kind
    ll times = 2001;
    cout << "Test Start!" << endl;
    for (ll i = 1; i < times; i++)
    {
        vector<string> strs = rand_str_arr(n, m, v);
        vector<string> sbao = strs;
        vector<string> sbea = strs;
        string rbao = bao(sbao);
        string rbea = bea(sbea);
        if (rbao != rbea)
        {
            cout << "error!" << endl;
            cout << "bao:" << rbao << ", ele:" << rbea << endl;
        }
    }
    cout << "Test Over!" << endl;

    return 0;
}

// array of non-negative integers, rearrange the numbers to form the largest possible integer, return the result as a string.
string larg_num(vector<ll> &nums)
{
    ll n = nums.size();
    vector<string> strs(n);
    for (ll i = 0; i < n; i++)
    {
        strs[i] = to_string(nums[i]);
    }
    sort(strs.begin(), strs.end(), [](const string &a, const string &b)
         { return b + a < a + b; });

    if (strs[0] == "0")
    {
        return "0";
    }
    stringstream ss;
    for (const string &s : strs)
    {
        ss << s;
    }
    return ss.str();
}

// company plans to interview 2n people, costs[i] = [ac, bc] represents the costs for i to fly to city a/b, return the minimum cost to send n people to a and n people to b.
ll city_cost(vector<vector<ll>> &costs)
{
    ll n = costs.size();
    ll diff[n];

    ll sum = 0;
    for (ll i = 0; i < n; i++)
    {
        diff[i] = costs[i][1] - costs[i][0];
        sum += costs[i][0];
    }

    sort(diff, diff + n);
    ll m = n / 2;
    for (ll i = 0; i < m; i++)
    {
        sum += diff[i];
    }

    return sum;
}

// n oranges, each day you can eat 1, n/2 (n % 2 = 0), or 2n/3 (n % 3) oranges，find the minimum number of days to eat all the oranges.
unordered_map<ll, ll> dp;
ll days(ll n)
{
    if (n < 2)
    {
        return n;
    }
    if (dp.count(n))
    {
        return dp[n];
    }

    ll ans = min(n % 2 + 1 + days(n / 2), n % 3 + 1 + days(n / 3));
    dp[n] = ans;
    return ans;
}

// maximum line segment overlap problem
ll minMeetingRooms(vector<vector<ll>> &mt)
{
    if (mt.empty())
    {
        return 0;
    }

    sort(mt.begin(), mt.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[0] < b[0]; });

    priority_queue<ll, vector<ll>, greater<ll>> etime;

    ll max = 0;
    for (const auto &meeting : mt)
    {
        ll st = meeting[0];
        ll et = meeting[1];

        while (!etime.empty() && etime.top() <= st)
        {
            etime.pop();
        }

        etime.push(et);
        max = std::max(max, (ll)etime.size());
    }

    return max;
}

// courses, each with a duration and a deadline, you cannot take multiple courses at the same time, find the maximum number of courses you can take.
ll schedule(vector<vector<ll>> &courses)
{
}
