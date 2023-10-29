#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void dijkstra(ll n, ll k, vector<pll> adj[])
{
    // src is fixed as 1
    vector<priority_queue<ll>> dists(n + 1);
    priority_queue<pll, vector<pll>, greater<pll>> q; // to not skip repeating distances
    q.push({0, 1});
    dists[1].push(0);
    while (!q.empty())
    {
        ll v = q.top().second;
        ll dist_v = q.top().first;
        q.pop();

        if (dist_v > dists[v].top()) // redundant distances in queue
            continue;

        for (auto &edge : adj[v])
        {
            ll adj_v = edge.first;
            ll wt = edge.second;
            ll val = dist_v + wt;
            if (dists[adj_v].size() < k)
            {
                dists[adj_v].push(val);
                q.push({val, adj_v});
            }
            else if (val < dists[adj_v].top())
            {
                dists[adj_v].pop();
                dists[adj_v].push(val);
                q.push({val, adj_v});
            }
        }
    }
    vl ans;
    while (!dists[n].empty())
    {
        ans.eb(dists[n].top());
        dists[n].pop();
    }
    reverse(all(ans));
    for (auto &i : ans)
        cout << i << " ";
}

void solve()
{
    ll n, a, b, c, m, k;
    cin >> n >> m >> k;
    vector<pll> adj[n + 1];
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        adj[a].eb(mp(b, c));
    }
    dijkstra(n, k, adj);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}