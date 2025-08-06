#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#define ll long long
using namespace std;

struct randomize_set
{
    map<ll, set<ll>> val_to_pos; // (v, pos_set)
    vector<ll> arr;
    mt19937 rng;

    randomize_set()
    {
        rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
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

    bool insert(ll v)
    {
        val_to_pos[v].insert(arr.size());
        arr.push_back(v);
        return true;
    }

    bool remove(ll v)
    {
        if (val_to_pos.find(v) == val_to_pos.end() || val_to_pos[v].empty())
        {
            return false;
        }

        ll pos = *(val_to_pos[v].begin());
        ll last_val = arr.back();
        ll last_pos = arr.size() - 1;

        arr[pos] = last_val;
        arr.pop_back();
        val_to_pos[v].erase(pos);


        if (pos != last_pos)
        {
            val_to_pos[last_val].erase(last_pos);
            val_to_pos[last_val].insert(pos);
        }

        if (val_to_pos[v].empty())
        {
            val_to_pos.erase(v);
        }

        return true;
    }
};

void print_set_state(const string &title, randomize_set &rs)
{
    cout << title << endl;
    cout << "  vector state: [";
    for (size_t i = 0; i < rs.arr.size(); ++i)
    {
        cout << rs.arr[i] << (i == rs.arr.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    cout << "  map state:    {";
    bool first_val = true;
    for (auto const &[val, pos_set] : rs.val_to_pos)
    {
        if (!first_val)
            cout << ", ";
        cout << val << ":{";
        bool first_pos = true;
        for (ll pos : pos_set)
        {
            if (!first_pos)
                cout << ",";
            cout << pos;
            first_pos = false;
        }
        cout << "}";
        first_val = false;
    }
    cout << "}\n"
         << endl;
}

signed main()
{
    randomize_set rs;

    rs.insert(10);
    rs.insert(20);
    rs.insert(10);
    rs.insert(30);
    rs.insert(40);
    rs.insert(10);
    print_set_state("--- test 1: elements 10, 20, 10, 30, 40, 10 ---", rs);

    rs.remove(20);
    print_set_state("--- test 2: after removing 20 ---", rs);

    rs.remove(40);
    print_set_state("--- test 3: after removing 40 ---", rs);

    rs.remove(10);
    print_set_state("--- test 4: after removing one instance of 10 ---", rs);

    rs.remove(10);
    rs.remove(10);
    print_set_state("--- test 5: after removing all remaining 10s ---", rs);

    cout << "--- test 6: attempting to remove 99 ---" << endl;
    bool result = rs.remove(99);
    cout << "  remove(99) returned: " << (result ? "true" : "false") << endl;
    print_set_state("  state is unchanged:", rs);

    cout << "--- test 7: getting 5 random elements from the final set ---" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "  random element: " << rs.get_random() << endl;
    }

    return 0;
}