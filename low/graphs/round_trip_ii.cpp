#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<bool> vb;

bool dfs(ll node, vl adj[], vb &vis, vb &pathVis, vl &par, vl &ans)
{
    vis[node] = 1;
    pathVis[node] = 1;
    for (auto it : adj[node])
    {
        if (!vis[it])
        {
            par[it] = node;
            if (dfs(it, adj, vis, pathVis, par, ans))
                return true;
        }
        else if (vis[it] && pathVis[it])
        {
            ans.emplace_back(it);
            while (node != it)
            {
                ans.emplace_back(node);
                node = par[node];
            }
            ans.emplace_back(it);
            reverse(ans.begin(), ans.end());
            return true;
        }
    }
    pathVis[node] = 0;
    return false;
}

void isCycle(ll V, vl adj[])
{
    vb vis(V + 1, 0);
    vb pathVis(V + 1, 0);
    vl par(V + 1, -1);
    vl ans;
    for (ll i = 1; i <= V; i++)
    {
        if (!vis[i])
        {
            if (dfs(i, adj, vis, pathVis, par, ans))
            {
                cout << ans.size() << "\n";
                for (auto &i : ans)
                    cout << i << " ";
                cout << "\n";
                return;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    vl adj[n + 1];
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        if (a != b) // not necessary here but for safety
            adj[a].eb(b);
    }
    isCycle(n, adj);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}