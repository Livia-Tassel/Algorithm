#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;

// pass by value: char, int, long, float, double，bool, string
void f(ll a)
{
    a = 100;
}

// pass by reference: class, struct, array
struct number
{
    ll a;
    number(ll val) : a(val) {}
};

void g_1(number *ptr)
{
    // this will not change the original pointer and causing the memory leak
    ptr = nullptr;
}

void g_2(number *ptr)
{
    // this will change the value of the original pointer because of the same address in heap
    ptr->a = 100;
}

void g_3(ll arr[])
{
    arr = nullptr;
}

void g_4(ll arr[])
{
    arr[0] = 100;
}

signed main()
{
    ll a = 10;
    f(a);
    // 10, pass by value, a is not changed
    cout << a << endl;

    number *ptr = new number(10);
    g_1(ptr);
    // 10, pass by reference
    cout << ptr->a << endl;
    g_2(ptr);
    cout << ptr->a << endl;

    ll arr[] = {10, 20, 30};
    g_3(arr);
    cout << arr[0] << endl;
    g_4(arr);
    cout << arr[0] << endl;

    delete ptr;
    ptr = nullptr;
    cout << "Program Finished." << endl;
    return 0;
}