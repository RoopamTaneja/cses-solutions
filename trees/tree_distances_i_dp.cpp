#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vector<pll> in; // pair -> mx1, mx2
vl out;
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
        in[s] = mp(0, 0);
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
        if (in[u].first + 1 >= in[s].first)
        {
            in[s].second = in[s].first;
            in[s].first = in[u].first + 1;
        }
        else if (in[u].first + 1 > in[s].second)
            in[s].second = in[u].first + 1;
    }
}

void dfs_out(ll s, ll e, vl adj[])
{
    if (e < 1) // root
        out[s] = 0;
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        ll val = in[s].first;
        if (in[s].first == in[u].first + 1)
            val = in[s].second;
        out[u] = 1 + max(val, out[s]);
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs_out(u, s, adj);
    }
}
// out[node] = 1 + max(in[parent] (other than node), out[parent])

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
    dfs_in(1, 0, adj);
    dfs_out(1, 0, adj);
    for (ll i = 1; i <= n; i++)
        cout << max(in[i].first, out[i]) << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}