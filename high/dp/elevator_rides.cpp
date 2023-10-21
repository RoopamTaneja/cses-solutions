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
// Pairs
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MOD = 1e9 + 7;

ll f(ll n, ll x, vl wt)
{
    vector<pll> dp(1 << n, {n + 1, x + 1}); // filling with large impossible value for minimising
    dp[0] = {1, 0};
    for (ll s = 1; s < (1 << n); s++)
    {
        for (ll i = 0; i < n; i++)
        {
            if (s & (1 << i)) // if ith person has used elevator
            {
                pll prev = dp[s ^ (1 << i)];
                if (prev.second + wt[i] <= x)
                    prev.second += wt[i];
                else
                {
                    prev.first++;
                    prev.second = wt[i];
                }
                dp[s] = min(dp[s], prev);
            }
        }
    }
    return dp[(1 << n) - 1].first;
}

void solve()
{
    ll n, val, x;
    vl v;
    cin >> n >> x;
    for (ll i = 0; i < n; i++)
    {
        cin >> val;
        v.eb(val);
    }
    cout << f(n, x, v) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}