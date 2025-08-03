#include <iostream>
#include <queue> // For std::priority_queue
#include <vector>
#include <string>
#include <functional> // For std::greater and std::function
#define ll long long
using namespace std;

void demonstrate_max_heap()
{

    priority_queue<ll> max_heap;

    // O(log N)
    max_heap.push(10);
    max_heap.push(30);
    max_heap.push(20);
    max_heap.push(50);
    max_heap.push(5);

    // O(1)
    cout << "top element: " << max_heap.top() << endl;

    // O(1)
    cout << "heap size: " << max_heap.size() << endl;
    cout << "heap empty? " << max_heap.empty() << endl;

    // O(log N)
    cout << "popping elements: ";
    while (!max_heap.empty())
    {
        cout << max_heap.top() << " ";
        max_heap.pop();
    }
    cout << endl;

    // O(N)
}

void demonstrate_min_heap()
{
    priority_queue<ll, vector<ll>, greater<ll>> min_heap;

    min_heap.push(10);
    min_heap.push(30);
    min_heap.push(20);
    min_heap.push(50);
    min_heap.push(5);

    cout << "top element: " << min_heap.top() << endl;
}

struct person
{
    string name;
    ll score;

    person(string n, ll s) : name(n), score(s) {}

    friend ostream &operator<<(ostream &os, const person &p)
    {
        os << "[" << p.name << ":" << p.score << "]";
        return os;
    }
};

// operator() returns false, p1 before p2
struct ComparePersonMaxHeap
{
    bool operator()(const person &p1, const person &p2) const
    {
        return p1.score < p2.score;
    }
};

struct ComparePersonMinHeap
{
    bool operator()(const person &p1, const person &p2) const
    {
        return p1.score > p2.score;
    }
};

void demonstrate_custom_heap()
{
    priority_queue<person, vector<person>, ComparePersonMaxHeap> custom_max_heap;
    custom_max_heap.push(person("alice", 90));
    custom_max_heap.push(person("bob", 75));
    custom_max_heap.push(person("charlie", 95));
    custom_max_heap.push(person("david", 80));

    cout << "custom Max-Heap (by score): ";
    while (!custom_max_heap.empty())
    {
        cout << custom_max_heap.top() << " ";
        custom_max_heap.pop();
    }
    cout << endl;
}

void demonstrate_lambda_heap()
{
    auto lambda_cmp_max = [](const person &p1, const person &p2)
    {
        return p1.score < p2.score;
    };

    priority_queue<person, vector<person>, function<bool(const person &, const person &)>> lambda_max_heap(lambda_cmp_max);

    lambda_max_heap.push(person("alice", 90));
    lambda_max_heap.push(person("bob", 75));
    lambda_max_heap.push(person("charlie", 95));
    lambda_max_heap.push(person("david", 80));

    cout << "lambda Max-Heap (by score): ";
    while (!lambda_max_heap.empty())
    {
        cout << lambda_max_heap.top() << " ";
        lambda_max_heap.pop();
    }
    cout << endl;
}

signed main()
{
    demonstrate_max_heap();
    demonstrate_min_heap();
    demonstrate_custom_heap();
    demonstrate_lambda_heap();

    return 0;
}