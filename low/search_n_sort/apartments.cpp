#include <bits/stdc++.h>
using namespace std;

// Datatypes
typedef long long ll;
typedef long double ld;
typedef long int l;
typedef unsigned int ui;

// Vectors
#define pb push_back
#define eb emplace_back
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

// Pairs
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Mathematical Constants
#define _USE_MATH_DEFINES
#define mpi M_PI
#define me M_E
#define mphi 1.618033933 // Golden Ratio

const int MOD = 1e9 + 7;

bool comp(pair<int, int> p1, pair<int, int> p2)
{ // just a sample
    if (p1.second > p2.second)
        return true;
    if (p1.second < p2.second)
        return false;
    if (p1.second == p2.second && p1.first > p2.first)
        return true;
    return false;
}

ll bin_mul(ll a, ll b, ll m)
{
    a %= m;
    ll res = 0;
    while (b > 0)
    {
        if (b & 1)
            res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

ll bin_exp_iter(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

ll pow_no_mod(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

ll floor_sqrt(ll x)
{
    ll ans = 0;
    for (ll k = 1LL << 30; k != 0; k /= 2)
    {
        if ((ans + k) * (ans + k) <= x)
            ans += k;
    }
    return ans;
}

void solve()
{
    int n, entry, m, k;
    int cnt = 0;
    vi a, b;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> entry;
        a.eb(entry);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> entry;
        b.eb(entry);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = n - 1, j = m - 1;
    while (i >= 0 && j >= 0)
    {
        ll diff = a[i] - b[j];
        if (abs(diff) <= k)
        {
            i--;
            j--;
            cnt++;
        }
        else
        {
            if (diff < 0)
                j--;
            else
                i--;
        }
    }
    // int i = 0, j = 0;
    // while (i < n && j < m)
    // {
    //     ll diff = a[i] - b[j];
    //     if (abs(diff) <= k)
    //     {
    //         i++;
    //         j++;
    //         cnt++;
    //     }
    //     else
    //     {
    //         if (diff < 0)
    //             i++;
    //         else
    //             j++;
    //     }
    // }
    cout << cnt << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    // cin >> t;
    t = 1;
    while (t--)
        solve();
    return 0;
}