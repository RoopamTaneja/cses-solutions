#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;
const int MOD = 1e9 + 7;

void dijkstra_set(ll V, vector<pll> adj[], ll src, vl &dist, vl &num, vl &minf, vl &maxf)
{
    dist.assign(V, 1e15);
    num.assign(V, 0);
    minf.assign(V, 1e9);
    maxf.assign(V, -1);
    dist[src] = 0;
    num[src] = 1;
    minf[src] = 0;
    maxf[src] = 0;
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
                num[adj_v] = num[v];
                minf[adj_v] = minf[v] + 1;
                maxf[adj_v] = maxf[v] + 1;
                q.insert({dist[adj_v], adj_v});
            }
            else if (dist[v] + wt == dist[adj_v])
            {
                num[adj_v] = (num[adj_v] + num[v]) % MOD;
                minf[adj_v] = min(minf[adj_v], minf[v] + 1);
                maxf[adj_v] = max(maxf[adj_v], maxf[v] + 1);
            }
        }
    }
}

void solve()
{
    ll n, m, a, b, c;
    cin >> n >> m;
    vector<pll> adj[n + 1];
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        adj[a].eb(mp(b, c));
    }
    vl dist, num, minf, maxf;
    dijkstra_set(n + 1, adj, 1, dist, num, minf, maxf);
    cout << dist[n] << " " << num[n] << " " << minf[n] << " " << maxf[n] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}