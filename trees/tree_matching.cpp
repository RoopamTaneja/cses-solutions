#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

bool isLeaf(ll u, vl adj[])
{
    if (u != 1 && adj[u].size() == 1)
        return true;
    return false;
}

void dfs(ll s, ll e, vl adj[], vector<pll> &dp)
{
    if (isLeaf(s, adj))
    {
        dp[s] = mp(0, 0);
        return;
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs(u, s, adj, dp);
    }
    ll val = 1e9;
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        ll term = max(dp[u].first, dp[u].second);
        dp[s].first += term;
        val = min(val, term - dp[u].first);
    }
    dp[s].second = 1 + dp[s].first - val;
}

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
    vector<pll> dp(n + 1, mp(0, 0));
    dfs(1, 0, adj, dp);
    cout << max(dp[1].first, dp[1].second) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}