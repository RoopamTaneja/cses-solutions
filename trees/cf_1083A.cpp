#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vl w;
bool isLeaf(ll u, vector<pll> adj[])
{
    if (u != 1 && adj[u].size() == 1)
        return true;
    return false;
}

void dfs(ll s, ll e, vector<pll> adj[], vector<pll> &dp)
{
    if (isLeaf(s, adj))
    {
        dp[s] = mp(w[s], w[s]);
        return;
    }
    vl ans;
    for (auto u : adj[s])
    {
        if (u.first == e)
            continue;
        dfs(u.first, s, adj, dp);
    }
    for (auto u : adj[s])
    {
        if (u.first == e)
            continue;
        ans.push_back(dp[u.first].first - u.second);
    }
    sort(ans.rbegin(), ans.rend());
    if (ans.size() > 0)
    {
        dp[s].first = max(w[s], w[s] + ans[0]);
        if (ans.size() > 1)
            dp[s].second = max(w[s], w[s] + ans[0] + ans[1]);
    }
    else
        dp[s] = mp(w[s], w[s]);
}

void solve()
{
    ll n, a, b, c;
    cin >> n;
    w.resize(n + 1);
    for (ll i = 1; i <= n; i++)
        cin >> w[i];
    vector<pll> adj[n + 1];
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b >> c;
        adj[a].emplace_back(mp(b, c));
        adj[b].emplace_back(mp(a, c));
    }
    vector<pll> dp(n + 1);
    ll res = 0;
    dfs(1, 0, adj, dp);
    for (ll i = 1; i <= n; i++)
        res = max(res, max(dp[i].first, dp[i].second));
    cout << res << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}