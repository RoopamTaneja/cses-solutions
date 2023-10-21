#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
 
void bellman_ford(ll V, vvl &edges)
{
    vl dist(V + 1, 0);
    vl parent(V + 1, -1);
    for (int i = 0; i < V - 1; i++)
    {
        for (auto it : edges)
        {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            if (dist[u] + wt < dist[v])
                dist[v] = dist[u] + wt, parent[v] = u;
        }
    }
 
    ll last_aff = -1;
    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        if (dist[u] + wt < dist[v])
            parent[v] = u, last_aff = v;
    }
    if (last_aff == -1)
    {
        cout << "NO\n";
        return;
    }
 
    for (ll i = 0; i < V - 1; i++)
        last_aff = parent[last_aff];
    ll node = last_aff;
    vl cycle;
    cycle.eb(node);
    node = parent[node];
    while (node != last_aff)
    {
        cycle.eb(node);
        node = parent[node];
    }
    cycle.eb(node);
    reverse(all(cycle));
    cout << "YES\n";
    for (auto &i : cycle)
        cout << i << " ";
    cout << "\n";
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
        v.eb(a), v.eb(b), v.eb(c);
        edges.eb(v);
    }
    bellman_ford(n, edges);
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}