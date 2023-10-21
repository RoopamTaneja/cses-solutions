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

void solve()
{
    ll n, entry;
    vl v;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    ll max_s = accumulate(all(v), 0LL) + 1;
    // vector<bool> dp(max_s, 0);
    // dp[0] = 1;
    // for (ll i = 0; i < n; i++)
    // {
    //     for (ll j = max_s - 1; j >= v[i]; j--)
    //     {
    //         dp[j] = dp[j] | dp[j - v[i]];
    //     }
    // }
    // ll count = 0;
    // for (ll i = 0; i < max_s; i++)
    // {
    //     if (dp[i])
    //         count++;
    // }
    // cout << count - 1 << "\n";
    // for (ll i = 1; i < max_s; i++)
    // {
    //     if (dp[i])
    //         cout << i << " ";
    // }
    bitset<100001> dp;
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        dp |= (dp << v[i]);
    }
    cout << dp.count() - 1 << "\n";
    for (ll i = 1; i < max_s; i++)
    {
        if (dp[i])
            cout << i << " ";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}