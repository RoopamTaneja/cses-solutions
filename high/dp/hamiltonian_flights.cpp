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

const int MOD = 1e9 + 7;
ll hamiltonianRoutes(ll n, vector<ll> adj[])
{                                       // 1-based indexing
    ll dp[(1 << n) + 10][n + 10] = {0}; // no of routes ending at city i covering whole subset s
    dp[1][1] = 1;
    for (ll s = 2; s < (1 << n); s++)
    {
        // only consider subsets that have the first city
        if (!(s & 1)) // necessary to avoid tle due to redundant computations
            continue;
        // also only consider subsets with the last city if it's the full subset
        // ie don't end at last city before reaching all vertices since it's
        // supposed to be our final destination
        if ((s & (1 << (n - 1))) && (s != ((1 << n) - 1))) // necessary to avoid tle due to redundant computations
            continue;
        for (ll i = 1; i <= n; i++)
        {
            if (s & (1 << (i - 1))) // if i is in the mask
            {
                for (auto &v : adj[i])
                {
                    if (s & (1 << (v - 1))) // if v is in the mask
                    {
                        dp[s][i] += dp[s ^ (1 << (i - 1))][v];
                        dp[s][i] %= MOD;
                    }
                }
            }
        }
    }
    return dp[(1 << n) - 1][n] % MOD;
}

/*The loop starts from s=2 because s=1 represents the subset containing only the first city, and this
case is already handled as a base case with dp[1][1] = 1, which means there is one route (the trivial
route) that starts and ends at the first city and only includes the first city.

The base cases for this problem are:

dp[1][1] = 1: As mentioned above, this represents the one trivial route that starts and ends at the first
city and only includes the first city.
dp[s][i] = 0 for all other s and i: Initially, we assume there are no routes for all other subsets and
cities. These values will be updated in the dynamic programming process.
The condition (s & 1) checks whether the first city is in the subset represented by s. If it’s not, we
skip this subset because we’re only interested in routes that start from the first city.

The condition (s & (1 << (n - 1))) & (s != ((1 << n) - 1)) checks whether the last city is in the subset
and whether the subset includes all cities. If the last city is in the subset but not all cities are
included, we skip this subset because we’re only interested in routes that end at the last city after
visiting all other cities.*/

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    vector<ll> adj[n + 1];
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[b].eb(a);
    }
    cout << hamiltonianRoutes(n, adj) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}