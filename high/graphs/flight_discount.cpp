#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void dijkstra_set(ll V, vector<pll> adj[], ll src, vl &dist)
{
    dist.assign(V, 1e18);
    dist[src] = 0;
    set<pll> q;
    q.insert({0, src});
    while (!q.empty())
    {
        ll v = q.begin()->second;
        q.erase(q.begin());
        for (auto edge : adj[v])
        {
            ll adj_v = edge.first;
            ll wt = edge.second;
            if (dist[v] + wt < dist[adj_v])
            {
                q.erase({dist[adj_v], adj_v});
                dist[adj_v] = dist[v] + wt;
                q.insert({dist[adj_v], adj_v});
            }
        }
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;
    vector<pll> adj[n + 1], adjRev[n + 1];
    vvl edges(m, vl(3, 0));
    for (ll i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        adj[edges[i][0]].eb(mp(edges[i][1], edges[i][2]));
        adjRev[edges[i][1]].eb(mp(edges[i][0], edges[i][2]));
    }

    vl dist1, distN;
    dijkstra_set(n + 1, adj, 1, dist1);
    dijkstra_set(n + 1, adjRev, n, distN);
    ll ans = 1e18;
    for (ll i = 0; i < m; i++)
        ans = min(ans, dist1[edges[i][0]] + (edges[i][2] / 2) + distN[edges[i][1]]);
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}