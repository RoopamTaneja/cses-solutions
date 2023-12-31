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

void solve()
{
    ll n, entry;
    vl v;
    cin >> n;
    vl adj[n + 1];
    for (ll i = 2; i <= n; i++)
    {
        cin >> entry;
        adj[i].emplace_back(entry);
        adj[entry].emplace_back(i);
    }
    vl cnt(n + 1, 0);
    dfs(1, -1, adj, cnt);
    for (ll i = 1; i <= n; i++)
        cout << cnt[i] - 1 << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}