#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <numeric>
#include <unordered_map>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// gcd-plus
ll d, x, y, px, py;
// xa + yb = gcd(a, b)
// log min(a, b)^3
void exgcd(ll a, ll b) // a >= 0, b >= 0
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// x = a^(-1) → (xa) % mod = 1 → xa - ?mod = 1
// exgcd(a, mod) = 1 → x = x, -? = y

// ax + by = c, no solution, return -1; no positive integer solutions, return the minimum positive values of x and y; positive integer solutions, return the number of positive integer solutions, as well as the minimum and maximum positive values of x and y.
void solve(ll a, ll b, ll c)
{
    exgcd(a, b);
    if (c % d != 0)
    {
        cout << -1 << endl;
        return;
    }

    x *= c / d;
    y *= c / d;

    ll xd = b / d, yd = a / d;
    if (x < 0)
    {
        // (1 - x)/xd ↑
        ll tims = (1 - x + xd - 1) / xd;
        x += xd * tims;
        y -= yd * tims;
    }
    else
    {
        // (x - 1)/xd ↓
        ll tims = (x - 1) / xd;
        x -= xd * tims;
        y += yd * tims;
    }

    if (y < 1)
    {
        ll miy = y + yd * ((1 - y + yd - 1) / yd);
        cout << x << " " << miy << endl;
    }
    else
    {
        ll cnt = (y - 1) / yd + 1;
        cout << cnt << " ";

        ll miy = y - yd * ((y - 1) / yd);
        cout << x << " " << miy << " ";

        ll max = x + xd * ((y - 1) / yd);
        cout << max << " " << y << endl;
    }
}

// circle length l, frog A is at position sa and jumps va units per second, while frog B is at sb and jumps vb units per second, both move clockwise, the minimum time required for them to meet.
ll meet(ll l, ll sa, ll sb, ll va, ll vb)
{
    // sa < sb, va > vb
    // (va - vb)t = sb - sa + kl

    // sa > sb, va < vb
    // (vb - va)t = sa - sb + kl

    //  sa < sb, va < vb
    // (vb - va)t = l - (sb - sa) + kl = sa - sb + kl

    // sb < sa, va > vb
    // (va - vb)t = l - (sa - sb) + kl = sb - sa + kl

    ll a, b = l, c;
    if (sa < sb)
    {
        a = va - vb;
        c = sb - sa;
    }
    else
    {
        a = vb - va;
        c = sa - sb;
    }

    if (a < 0)
    {
        a = -a;
        c = l - c;
    }
    exgcd(a, l);

    if (c % d != 0)
    {
        cout << "Impossible";
    }
    else
    {
        x *= c / d;
        ll xd = l / d;
        if (x < 0)
        {
            x += (1 - x + xd - 1) / xd * xd;
        }
        else
        {
            x -= (x - 1) / xd * xd;
        }
        cout << x;
    }
}

// points A(xa, ya) and B(xb, yb), lattice point is a point with integer coordinates, find the number of lattice points on the line segment AB, including A and B.
ll points(ll xa, ll xb, ll ya, ll yb)
{
    // (yb - ya)x + (xa - xb)y = yb.xa - ya.xb
    // x = xa + ((xa -xb)/gcd) * n
    ll g = gcd(abs(xa - xb), abs(ya - yb));
    return g + 1;
}

// robot starts at (0,0) and moves according to n given displacements (dx, dy), forming a counter-clockwise simple polygon, find the number of lattice points inside the polygon, the number of lattice points on its boundary, and the area of the polygon.
void robot()
{
    ll n, egs = 0, area = 0;
    for (ll i = 0, x = 0, y = 0, dx, dy; i < n + 1; i++)
    {
        cin >> dx >> dy;
        egs += gcd(abs(dx), abs(dy));
        area += x * (y + dy) - (x + dx) * y;

        x += dx;
        y += dy;
    }

    area /= 2;
    ll inn = area - egs / 2 + 1;
    cout << egs << " " << area << " " << inn << endl;
}