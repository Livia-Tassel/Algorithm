#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#define ll long long
using namespace std;

struct randomize_set
{
    map<ll, ll> val_to_pos; // (v, pos)
    vector<ll> arr;
    mt19937 rng;

    randomize_set()
    {
        rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    bool insert(ll v)
    {
        if (val_to_pos.count(v))
        {
            return false;
        }
        val_to_pos[v] = arr.size();
        arr.push_back(v);
        return true;
    }

    ll get_random()
    {
        if (arr.empty())
        {
            return -1;
        }

        uniform_int_distribution<ll> dist(0, arr.size() - 1);
        return arr[dist(rng)];
    }

    bool remove(ll v)
    {
        if (!val_to_pos.count(v))
        {
            return false;
        }

        ll pos = val_to_pos[v];
        ll last_val = arr.back();

        arr[pos] = last_val;
        val_to_pos[last_val] = pos;

        val_to_pos.erase(v);
        arr.pop_back();

        return true;
    }
};

void print_set_state(randomize_set &rs)
{
    cout << "  vector state: [";
    for (size_t i = 0; i < rs.arr.size(); ++i)
    {
        cout << rs.arr[i] << (i == rs.arr.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    cout << "  map state: {";
    bool first = true;
    for (auto const &[val, pos] : rs.val_to_pos)
    {
        if (!first)
            cout << ", ";
        cout << val << "->" << pos;
        first = false;
    }
    cout << "}" << endl;
}

signed main()
{
    randomize_set rs;

    cout << "--- elements ---" << endl;
    rs.insert(10);
    rs.insert(20);
    rs.insert(30);
    rs.insert(40);
    print_set_state(rs);

    cout << "\n--- removing element 20 (not the last one) ---" << endl;
    rs.remove(20);
    cout << "state after removing 20:" << endl;
    print_set_state(rs);

    cout << "\n--- removing element 10 ---" << endl;
    rs.remove(10);
    cout << "state after removing 10:" << endl;
    print_set_state(rs);

    cout << "\n--- getting 5 random elements ---" << endl;
    for (ll i = 0; i < 5; ++i)
    {
        cout << "random element: " << rs.get_random() << endl;
    }

    return 0;
}