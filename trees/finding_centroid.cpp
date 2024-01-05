#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

bool isLeaf(ll u, vl adj[])
{
    if (u != 1 && adj[u].size() == 1)
        return true;
    return false;
}

void dfs(ll s, ll e, vl adj[], vl &dp)
{
    if (isLeaf(s, adj))
    {
        dp[s] = 1;
        return;
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs(u, s, adj, dp);
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dp[s] += dp[u];
    }
    dp[s]++;
}

ll dfs_centr(ll s, ll e, ll n, vl adj[], vl &sub)
{
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        if (sub[u] > n / 2)
            return dfs_centr(u, s, n, adj, sub);
    }
    return s;
}

// ALITER
// ll centroid(ll s, ll e, ll n, vl adj[], vl &sub)
// {
//     ll new_s = s;
//     while (true)
//     {
//         for (auto u : adj[s])
//         {
//             if (u == e)
//                 continue;
//             if (sub[u] > n / 2)
//             {
//                 new_s = u;
//                 break;
//             }
//         }
//         if (new_s == s)
//             return s;
//         e = s;
//         s = new_s;
//     }
// }

void solve()
{
    ll n, a, b;
    cin >> n;
    vl adj[n + 1];
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vl sub(n + 1, 0);
    dfs(1, 0, adj, sub);
    // cout << centroid(1, 0, n, adj, sub) << "\n";
    cout << dfs_centr(1, 0, n, adj, sub) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}