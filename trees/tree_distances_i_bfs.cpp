#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

void bfs_dist(vector<bool> &vis, vl adj[], ll S, vl &d)
{
    vis[S] = 1;
    queue<pll> q;
    q.push(mp(S, 0));
    d[S] = 0;
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
                d[it] = dist + 1;
                q.push(mp(it, dist + 1));
            }
        }
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
    vector<bool> vis(n + 1, 0);
    vl dist1(n + 1), dist2(n + 1), distn(n + 1);
    bfs_dist(vis, adj, 1, distn);
    ll end1 = 1, max_dist = 0;
    for (ll i = 1; i <= n; i++)
    {
        if (max_dist < distn[i])
            max_dist = distn[i], end1 = i;
    }
    vis.assign(n + 1, 0);
    bfs_dist(vis, adj, end1, dist1);
    ll end2 = 1;
    max_dist = 0;
    for (ll i = 1; i <= n; i++)
    {
        if (max_dist < dist1[i])
            max_dist = dist1[i], end2 = i;
    }
    vis.assign(n + 1, 0);
    bfs_dist(vis, adj, end2, dist2);
    for (ll i = 1; i < n + 1; i++)
        cout << max(dist1[i], dist2[i]) << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}