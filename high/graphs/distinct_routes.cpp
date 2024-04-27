// Max Flow : Edmonds Karp : O(mn^2)
// My method of finding a path => DFS => O(m+n) for one path, at max O(m) paths
// So O(m^2 + mn) for printing
// Overall : O(m^2 + mn^2) or just O(mn^2)

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair

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

void solve()
{
    ll n, m, a, b;
    cin >> n >> m;
    ll s = 1, t = n;
    vl parent(n + 1);
    vector<pair<ll, bool>> og[n + 1];
    vl adj[n + 1];
    vvl cap(n + 1, vl(n + 1, 0));
    vector<bool> vis(n + 1, 0);
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        og[a].eb(mp(b, false));
        adj[a].eb(b);
        adj[b].eb(a);
        cap[a][b] = 1;
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
    cout << max_flow << "\n";
    // Finding max no of edge disjoint paths as max flow
    // In such paths, all edges are critical (residual = 0)
    // Start from s and look for all edges with cap = 0
    // A bool to ensure the same edges are not counted again in different paths (edge disjoint)
    // All zero edge paths will pakka end at dest
    vvl ans;
    for (ll i = 0; i < max_flow; i++)
    {
        vl path;
        path.eb(1);
        ll node = 1;
        while (node != n)
        {
            for (auto &p : og[node])
            {
                if (cap[node][p.first] == 0 && p.second == false)
                {
                    path.eb(p.first);
                    p.second = true;
                    node = p.first;
                    break;
                }
            }
        }
        ans.eb(path);
    }
    for (auto &path : ans)
    {
        cout << path.size() << "\n";
        for (auto &x : path)
            cout << x << " ";
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}