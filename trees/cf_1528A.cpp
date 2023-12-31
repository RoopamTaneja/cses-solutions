// See Q on website and MUST read TUTORIAL

#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vector<pll> v;
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
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dp[s].first += max((abs(v[s].first - v[u].first) + dp[u].first),
                           ((abs(v[s].first - v[u].second) + dp[u].second)));
        dp[s].second += max((abs(v[s].second - v[u].first) + dp[u].first),
                            ((abs(v[s].second - v[u].second) + dp[u].second)));
    }
}

void solve()
{
    ll n, a, b;
    cin >> n;
    v.resize(n + 1);
    for (ll i = 1; i <= n; i++)
    {
        cin >> a >> b;
        v[i] = (mp(a, b));
    }
    vl adj[n + 1];
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vector<pll> dp(n + 1);
    dfs(1, 0, adj, dp);
    cout << max(dp[1].first, dp[1].second) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}