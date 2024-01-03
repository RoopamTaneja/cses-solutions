#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

pll bfs_farthest(vl &vis, vl adj[], ll S)
{
    vis[S] = 1;
    queue<pll> q;
    q.push(mp(S, 0));
    while (!q.empty())
    {
        pll p = q.front();
        ll node = p.first;
        ll dist = p.second;
        q.pop();
        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                vis[it] = 1;
                q.push(mp(it, dist + 1));
            }
        }
        if (q.empty())
            return p;
    }
    return mp(-1, -1);
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
    vl vis(n + 1, 0), result;
    pll end = bfs_farthest(vis, adj, 1);
    vis.assign(n + 1, 0);
    pll ans = bfs_farthest(vis, adj, end.first);
    cout << ans.second << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}