#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;

signed main()
{
    vector<pair<ll, ll>> lines;
    lines.push_back({1, 3});
    lines.push_back({1, 5});
    lines.push_back({2, 4});
    lines.push_back({3, 6});
    lines.push_back({5, 7});

    sort(lines.begin(), lines.end()); // sort by starting point

    ll max_overlap = 0;
    priority_queue<ll, vector<ll>, greater<ll>> end_points; // min-heap for end points

    for (const auto &line : lines)
    {
        end_points.push(line.second);
        while (!end_points.empty() && end_points.top() <= line.first)
        {
            end_points.pop();
        }
        max_overlap = max(max_overlap, (ll)end_points.size());
    }
    cout << max_overlap << endl;

    return 0;
}