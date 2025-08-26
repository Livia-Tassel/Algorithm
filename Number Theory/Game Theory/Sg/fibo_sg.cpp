#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#define ll long long
using namespace std;

// three piles of stones with quantities a, b, and c, each turn, player can choose one pile and remove a number of stones equal to a fiboes, the player who takes the last stone wins.
ll f[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
ll sg[201];
bool appear[201];
void sg_cnt()
{
    sg[0] = 0;
    for (ll i = 1; i < 201; i++)
    {
        memset(appear, false, sizeof(appear));
        for (ll j = 0; j < 11 && i - f[j] >= 0; j++)
        {
            appear[sg[i - f[j]]] = true;
        }
        for (ll s = 0; s < 201; s++)
        {
            if (!appear[s])
            {
                sg[i] = s;
                break;
            }
        }
    }
}
string fiboes(ll a, ll b, ll c)
{
    return (sg[a] ^ sg[b] ^ sg[c]) != 0 ? "fir" : "sec";
}
signed main()
{
    sg_cnt();
    for (ll i = 0; i < 201; i++)
    {
        cout << sg[i] << " ";
    }
    cout << fiboes(1, 2, 3) << endl;
}