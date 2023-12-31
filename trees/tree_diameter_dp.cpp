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

void dfs(ll s, ll e, vl adj[], vector<pll> &dp, ll &res)
{
    if (isLeaf(s, adj))
    {
        dp[s] = mp(0, 0);
        return;
    }
    vl ans;
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs(u, s, adj, dp, res);
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        ans.push_back(dp[u].first);
    }
    sort(ans.rbegin(), ans.rend());
    if (ans.size() > 0)
    {
        dp[s].first = 1 + ans[0];
        if (ans.size() > 1)
            dp[s].second = 2 + ans[0] + ans[1];
        else
            dp[s].second = 0;
    }
    else
        dp[s] = {0, 0};
    res = max(res, max(dp[s].first, dp[s].second));
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
    vector<pll> dp(n + 1);
    ll res = 0;
    dfs(1, 0, adj, dp, res);
    cout << res << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}