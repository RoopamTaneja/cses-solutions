// CSES : https://cses.fi/problemset/task/1639

#pragma GCC optimize("O3,unroll-loops")

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
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<vector<char>> vvc;

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

// safe_map bfsOfGraph dfsIterOfGraph dfsRecurOfGraph

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

ll edit_dist(string &s1, string &s2)
{
    ll n = s1.size(), m = s2.size();
    vvl dp(n + 10, vl(m + 10, 0));
    for (ll i = 0; i <= n; i++)
    {
        for (ll j = 0; j <= m; j++)
        {
            if (i == 0)
                dp[i][j] = j;
            if (j == 0)
                dp[i][j] = i;
            if (i > 0 && j > 0)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                {
                    dp[i][j] = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }
    }
    return dp[n][m];
}

void solve()
{
    string s, t;
    cin >> s >> t;
    cout << edit_dist(s, t) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}