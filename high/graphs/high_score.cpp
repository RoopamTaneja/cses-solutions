#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;
typedef vector<vl> vvl;

void dfs(ll node, vl adj[], vl &vis, vector<bool> &affected, bool &f)
{
    vis[node] = 1;
    if (affected[node])
        f = true;
    for (auto it : adj[node])
        if (!vis[it])
            dfs(it, adj, vis, affected, f);
}

void bellman_ford(ll V, vvl &edges, ll S)
{
    vl dist(V + 1, 1e18);
    dist[S] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for (auto it : edges)
        {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            if (dist[u] != 1e18 && dist[u] + wt < dist[v])
                dist[v] = dist[u] + wt;
        }
    }
    vector<bool> affected(V + 1, 0);
    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        if (dist[u] != 1e18 && dist[u] + wt < dist[v])
            affected[u] = 1;
    }
    vl vis(V + 1, 0);
    vl adjRev[V + 1];
    for (auto it : edges)
        adjRev[it[1]].eb(it[0]);

    bool f = false;
    dfs(V, adjRev, vis, affected, f);
    if (f)
        cout << -1 << "\n";
    else
        cout << -dist[V] << "\n";
}

void solve()
{
    ll n, a, b, c, m;
    cin >> n >> m;
    vvl edges;
    for (ll i = 0; i < m; i++)
    {
        vl v;
        cin >> a >> b >> c;
        v.eb(a), v.eb(b), v.eb(-c);
        edges.eb(v);
    }
    bellman_ford(n, edges, 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}