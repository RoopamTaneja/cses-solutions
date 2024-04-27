// Once the max-flows have been found and
// we have residual capacities marked
// A - set of nodes reachable from s
// Any edge connecting A and V\A belongs to a cut
// Here since max flow has been found, it belongs to MIN CUT
// So all edges (a, b) of original graph
// st a is reachable from s and b isn't => belongs to min cut

// Edmonds-Karp
// O(VE^2)

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<ll, ll> pll;

ll bfs(ll s, ll t, vl &parent, vl adj[], vvl &cap)
{ // paths of flow = 1
    fill(all(parent), -1);
    parent[s] = -2;
    queue<ll> q;
    q.push(s);
    while (!q.empty())
    {
        ll cur = q.front();
        q.pop();
        for (ll next : adj[cur])
        {
            if (parent[next] == -1 && cap[cur][next] > 0)
            {
                parent[next] = cur;
                if (next == t)
                    return 1;
                q.push(next);
            }
        }
    }
    return 0;
}

void reachable(ll s, vl adj[], vvl &cap, vector<bool> &vis)
{
    queue<ll> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty())
    {
        ll cur = q.front();
        q.pop();
        for (ll next : adj[cur])
        {
            if (!vis[next] && cap[cur][next] > 0)
            {
                vis[next] = 1;
                q.push(next);
            }
        }
    }
}

void solve()
{
    ll n, m, a, b;
    cin >> n >> m;
    ll s = 1, t = n;
    vl parent(n + 1);
    vl adj[n + 1];
    vvl cap(n + 1, vl(n + 1, 0));
    vector<bool> vis(n + 1, 0);
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].eb(b);
        adj[b].eb(a);
        cap[a][b] = 1;
        cap[b][a] = 1;
    }
    ll max_flow = 0;
    while (bfs(s, t, parent, adj, cap))
    {
        max_flow += 1;
        ll cur = t;
        while (cur != s)
        {
            ll prev = parent[cur];
            cap[prev][cur] -= 1;
            cap[cur][prev] += 1;
            cur = prev;
        }
    }
    reachable(s, adj, cap, vis);
    vector<pll> ans;
    for (ll i = 1; i <= n; i++)
    {
        for (auto &j : adj[i])
        {
            if (vis[i] && !vis[j])
                ans.eb(mp(i, j));
        }
    }
    cout << ans.size() << "\n";
    for (auto &p : ans)
        cout << p.first << " " << p.second << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
