#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

void print_binary(ll num)
{
    for (ll i = 63; i >= 0; --i)
    {
        // 1LL means the one is treated as a long long, ensuring that the left shift operation does not overflow.
        cout << (num & (1LL << i) ? '1' : '0');
    }
    cout << endl;
}

signed main()
{
    // two's complement: positive → positive；negative → positive → -1 → inverse
    // eg: -8 → 8 → 1000 → 0111 → 1000
    // value: positive → positive；negative → inverse → +1 → value → sign
    // eg: 1000 → 0111 → 1000 → 8 → -8

    ll a = 0b1000; // 8
    ll b = 0b1111; // 15
    ll c = 0x7;    // 7
    ll d = 0xF;    // 15
    cout << a << " " << b << " " << c << " " << d << endl;
    cout << "Binary Representation:" << endl;
    print_binary(a);
    print_binary(b);
    print_binary(c);
    print_binary(d);

    // >>; >>>
    // Arithmetic Right Shift; Logical Right Shift
    cout << "Arithmetic Right Shift:" << endl;
    print_binary(a >> 1);
    print_binary(b >> 1);
    print_binary(c >> 1);
    print_binary(d >> 1);
    cout << "Logical Right Shift:" << endl;
    print_binary(static_cast<unsigned long long>(a) >> 1);
    print_binary(static_cast<unsigned long long>(b) >> 1);
    print_binary(static_cast<unsigned long long>(c) >> 1);
    print_binary(static_cast<unsigned long long>(d) >> 1);

    // Opposite Number(except for the smallest negative numbers)
    cout << "Opposite Number:" << endl;
    cout << "-a: " << ~a + 1 << ", -b: " << ~b + 1 << ", -c: " << ~c + 1 << ", -d: " << ~d + 1 << endl;
    print_binary(~a + 1);
    print_binary(~b + 1);
    print_binary(~c + 1);
    print_binary(~d + 1);

    // AND, OR, XOR
    cout << "AND:" << endl;
    print_binary(a & b);
    cout << "OR:" << endl;
    print_binary(a | b);
    cout << "XOR:" << endl;
    print_binary(a ^ b);

    return 0;
}