#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#define ll long long
using namespace std;

// n piles of stones, each turn, one player chooses a non-empty pile and removes a positive number of stones from it, the player who takes the last stone wins.
// ^ != 0 ? fir : sec
ll st[1001];
string nim(ll n)
{
    ll ans = 0;
    // a a 0
    // b b 0
    // c c 0
    // 1 0 1  →  subtract positive
    // x x x
    // x x x
    // x x x
    for (ll i = 0; i < n; i++)
    {
        ans ^= st[i];
    }
    return ans != 0 ? "fir" : "sec";
}

// nim game, but the player who takes the last stone loes.
// if all the piles only have one stone, !(n & 1) ? fir : sec;
// else ^ != 0 ? fir : sec