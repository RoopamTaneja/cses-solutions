#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

vl in, out, sub; // inside subtree, outside subtree and subtree size
bool isLeaf(ll u, vl adj[])
{
    if (u != 1 && adj[u].size() == 1)
        return true;
    return false;
}
void dfs_in(ll s, ll e, vl adj[])
{
    if (isLeaf(s, adj))
    {
        in[s] = 0;
        sub[s] = 1;
        return;
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs_in(u, s, adj);
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        in[s] += in[u] + sub[u];
        sub[s] += sub[u];
    }
    sub[s]++;
}

void dfs_out(ll s, ll e, vl adj[], ll n)
{
    if (e < 1) // root
        out[s] = 0;
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        out[u] = (in[s] - in[u] - sub[u]) + out[s] + n - sub[u];
    }
    // out[node] = in[parent] (excl contri of node) + out[parent] + n - sub[u]
    // n - sub[u] -> extending paths to all nodes except own subtree
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs_out(u, s, adj, n);
    }
}

void solve()
{
    ll n, a, b;
    vl v;
    cin >> n;
    vl adj[n + 1];
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    in.resize(n + 1);
    out.resize(n + 1);
    sub.resize(n + 1);
    dfs_in(1, 0, adj);
    dfs_out(1, 0, adj, n);
    for (ll i = 1; i <= n; i++)
        cout << in[i] + out[i] << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}