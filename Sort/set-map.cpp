#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <functional> // For std::hash
#include <utility>    // For std::pair, std::make_pair
#include <stdexcept>  // For std::out_of_range
#define ll long long
using namespace std;

void demonstrate_set()
{
    set<ll> s;
    // O(log N)
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(10); // repeat, fail

    // traversal
    for (ll val : s)
    {
        cout << val << " ";
    }
    cout << endl; // 10 20 30

    cout << "set size: " << s.size() << endl;
    cout << "set empty? " << s.empty() << endl;

    // O(log N)
    ll x;
    cin >> x;
    // count() returns the number of occurrences of x in the set (0 or 1 for set)
    if (s.count(x))
    {
        cout << x << " exists." << endl;
    }
    // find() returns iterator to the element if found, or s.end() if not found
    auto it_found = s.find(x);
    if (it_found != s.end())
    {
        cout << "found " << x << "at (dereferenced) iterator: " << *it_found << endl;
    }

    // O(log N)
    s.erase(x);
    s.erase(--s.end());
    cout << "erasing " << x << ": ";
    for (ll val : s)
    {
        cout << val << " ";
    }
    cout << endl;

    // O(log N)
    it_found = s.find(x);
    if (it_found != s.end())
    {
        s.erase(it_found);
    }
    cout << "erasing " << x << " by iterator: ";
    for (ll val : s)
    {
        cout << val << " ";
    }
    cout << endl;

    // lower_bound/upper_bound
    // O(log N)
    s.insert(15);
    s.insert(25);
    s.insert(35);
    cout << "current set: ";
    for (ll val : s)
    {
        cout << val << " ";
    }
    cout << endl;

    auto lb_it = s.lower_bound(x); // the first element not less than x, else return s.end()
    auto ub_it = s.upper_bound(x); // the first element greater than x, else return s.end()
    cout << "lower_bound(" << x << "): " << *lb_it << endl;
    cout << "upper_bound(" << x << "): " << *ub_it << endl;

    // O(N)
    s.clear();

    // space: O(N)
}

void demonstrate_unordered_set()
{
    // average time: O(1), worst case: O(N)
    unordered_set<string> us;
    us.insert("apple");
    us.insert("banana");
    us.insert("cherry");
    us.insert("apple"); // repeat, fail

    cout << "unordered set elements (order not guaranteed): ";
    for (const string &s : us)
    {
        cout << s << " ";
    }
    cout << endl;

    // O(1)
    cout << "unordered set size: " << us.size() << endl;

    // average: O(1)；worst case: O(N)
    if (us.count("banana"))
    {
        cout << "banana is in the set." << endl;
    }
    auto it_found = us.find("cherry");
    if (it_found != us.end())
    {
        cout << "found cherry." << endl;
    }

    // average: O(1)；worst case: O(N)
    us.erase("banana");
    cout << "unordered set after erasing banana: ";
    for (const string &s : us)
    {
        cout << s << " ";
    }
    cout << endl;

    // space: O(N)
}

void demonstrate_map()
{
    // O(log N)
    map<string, ll> ages;
    ages["alice"] = 30;
    ages["bob"] = 25;
    // O(log N)
    ages.insert({"charlie", 35});
    ages.insert(make_pair("alice", 31)); // key exists, won't update value
    ages["bob"] = 26;                    // key exists, update value

    // O(N)
    cout << "map elements (sorted by key):" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // O(log N)
    // use "[]" to access, the key does not exist, it will insert a new element.
    cout << "alice's age: " << ages["alice"] << endl;
    // use at() to access, the key does not exist, it will throw std::out_of_range exception.
    try
    {
        cout << "david's age: " << ages.at("david") << endl;
    }
    catch (const out_of_range &oor)
    {
        cerr << "error: " << oor.what() << endl;
    }

    // O(log N)
    if (ages.count("bob"))
    {
        cout << "bob is in the map with age: " << ages["bob"] << endl;
    }
    auto it_found = ages.find("charlie");
    if (it_found != ages.end())
    {
        cout << "found charlie, age: " << it_found->second << endl; // 通过 ->second 访问值
    }

    // O(log N)
    ages.erase("bob");
    cout << "map after erasing bob:" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // lower_bound/upper_bound
    // O(log N)
    map<char, ll> cm = {{'a', 1}, {'c', 3}, {'e', 5}, {'g', 7}};
    auto lb_it_char = cm.lower_bound('d'); // returns the key not less than 'd', or cm.end()
    auto ub_it_char = cm.upper_bound('d'); // returns the key greater than 'd', or cm.end()
    cout << "cm lower_bound('d'): " << lb_it_char->first << endl;
    cout << "cm upper_bound('d'): " << ub_it_char->first << endl;

    // space: O(N)
}

void demonstrate_unordered_map()
{
    // average: O(1), worst case: O(N)
    unordered_map<string, ll> ages;
    ages["alice"] = 30;
    ages["bob"] = 25;
    ages.insert({"charlie", 35});
    ages.insert({"alice", 31}); // key exists, won't update value
    ages["bob"] = 26;           // key exists, update value

    cout << "unordered map elements (order not guaranteed by key):" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // average: O(1), worst case: O(N)
    cout << "alice's age: " << ages["alice"] << endl;
    try
    {
        cout << "david's age (using at()): " << ages.at("david") << endl;
    }
    catch (const out_of_range &oor)
    {
        cerr << "error: " << oor.what() << endl;
    }

    // average: O(1), worst case: O(N)
    if (ages.count("bob"))
    {
        cout << "bob is in the map with age: " << ages["bob"] << endl;
    }
    auto it_found = ages.find("charlie");
    if (it_found != ages.end())
    {
        cout << "found charlie, age: " << it_found->second << endl;
    }

    // average: O(1), worst case: O(N)
    ages.erase("bob");
    cout << "unordered map after erasing bob:" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // space: O(N)
}

struct person
{
    string name;
    ll age;
    double height;

    person(string n, ll a, double h) : name(n), age(a), height(h) {}

    friend ostream &operator<<(ostream &os, const person &p)
    {
        os << "[" << p.name << ", " << p.age << " yrs, " << p.height << "m]";
        return os;
    }
};

struct GreaterInt
{
    bool operator()(ll a, ll b) const
    {
        return a > b;
    }
};

struct CompareStringByLength
{
    bool operator()(const string &s1, const string &s2) const
    {
        if (s1.length() != s2.length())
        {
            return s1.length() < s2.length();
        }
        return s1 < s2;
    }
};

struct ComparepersonByAgeDesc
{
    bool operator()(const person &p1, const person &p2) const
    {
        if (p1.age != p2.age)
        {
            return p1.age > p2.age;
        }
        if (p1.name != p2.name)
        {
            return p1.name < p2.name;
        }
        return p1.height < p2.height;
    }
};

struct ComparepersonKeyByAgeDesc
{
    bool operator()(const person &p1, const person &p2) const
    {
        if (p1.age != p2.age)
        {
            return p1.age > p2.age;
        }
        if (p1.name != p2.name)
        {
            return p1.name < p2.name;
        }
        return p1.height < p2.height;
    }
};

template <typename T>
void print_set(const T &s, const string &title)
{
    cout << title << ": { ";
    for (const auto &val : s)
    {
        cout << val << " ";
    }
    cout << "}" << endl;
}

signed main()
{
    demonstrate_set();
    demonstrate_unordered_set();
    demonstrate_map();
    demonstrate_unordered_map();

    set<ll, greater<ll>> s_desc;
    s_desc.insert(10);
    s_desc.insert(50);
    s_desc.insert(20);
    s_desc.insert(5);
    print_set(s_desc, "std::set<ll> (des)");

    set<string, CompareStringByLength> s_str_len;
    s_str_len.insert("apple");  // length 5
    s_str_len.insert("cat");    // length 3
    s_str_len.insert("banana"); // length 6
    s_str_len.insert("dog");    // length 3
    s_str_len.insert("zebra");  // length 5
    print_set(s_str_len, "std::set<string> (length)");
    // { cat dog apple zebra banana }

    map<string, ll> scores = {
        {"alice", 90}, {"bob", 85}, {"charlie", 90}, {"david", 95}};

    vector<pair<string, ll>> vec_scores(scores.begin(), scores.end());

    sort(vec_scores.begin(), vec_scores.end(), [](const pair<string, ll> &p1, const pair<string, ll> &p2)
         {
             if (p1.second != p2.second)
             {
                 return p1.second > p2.second;
             }
             return p1.first < p2.first; });

    for (const auto &p : vec_scores)
    {
        cout << "  " << p.first << " : " << p.second << endl;
    }
    //   david : 95
    //   alice : 90
    //   charlie : 90
    //   bob : 85

    return 0;
}
