#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <cstdlib>
#define ll long long
using namespace std;

// hash table with a setall function.
struct setall_hash
{
    map<ll, pair<ll, ll>> mp;
    ll setall_value;
    ll setall_time;
    ll time_stamp;

    setall_hash() : setall_value(0), setall_time(-1), time_stamp(0) {}

    void insert(ll k, ll v)
    {
        if (mp.count(k))
        {
            pair<ll, ll> &value = mp[k];
            value.first = v;
            value.second = time_stamp++;
        }
        else
        {
            mp[k] = make_pair(v, time_stamp++);
        }
    }

    void setall(ll v)
    {
        setall_time = time_stamp++;
        setall_value = v;
    }

    ll get_value(ll k)
    {
        pair<ll, ll> &value = mp[k];
        if (value.second > setall_time)
        {
            return value.first;
        }
        else
        {
            return setall_value;
        }
    }
};

signed main()
{
    setall_hash sh;
    sh.insert(1, 10);
    sh.insert(2, 20);
    sh.insert(3, 30);

    cout << "1: " << sh.get_value(1) << endl;
    cout << "2: " << sh.get_value(2) << endl;
    cout << "3: " << sh.get_value(3) << endl;

    sh.setall(100);
    cout << "\nsetall(100): " << endl;
    cout << "1: " << sh.get_value(1) << endl;
    cout << "2: " << sh.get_value(2) << endl;
    cout << "3: " << sh.get_value(3) << endl;

    sh.insert(2, 200);
    sh.insert(4, 400);
    cout << "\ninsert(2, 200): " << endl;
    cout << "2: " << sh.get_value(2) << endl; // 200
    cout << "1: " << sh.get_value(1) << endl; // 100
    cout << "4: " << sh.get_value(4) << endl; // 400

    return 0;
}
