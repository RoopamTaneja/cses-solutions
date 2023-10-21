#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;
typedef vector<bool> vb;
vl adj[100010];
stack<ll> recStack;
vb vis(100010, 0);
vb pathVis(100010, 0);
bool dfs(ll node)
{
    vis[node] = 1;
    recStack.push(node);
    pathVis[node] = 1;
    for (auto it : adj[node])
    {
        if (pathVis[it])
        {
            recStack.push(it);
            return true;
        }
        if (!vis[it])
        {
            if (dfs(it) == true)
                return true;
        }
    }
    recStack.pop();
    pathVis[node] = 0;
    return false;
}

bool isCyclic(ll n)
{
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            if (dfs(i))
                return true;
        }
    }
    return false;
}

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].eb(b);
    }
    if (isCyclic(n))
    {
        vl cycle;
        ll start = recStack.top();
        cycle.eb(start);
        recStack.pop();
        while (recStack.top() != start)
        {
            cycle.eb(recStack.top());
            recStack.pop();
        }
        cycle.eb(recStack.top());
        ll ans = cycle.size();
        cout << ans << "\n";
        for (ll i = ans - 1; i >= 0; i--)
            cout << cycle[i] << " ";
        cout << "\n";
    }
    else
        cout << "IMPOSSIBLE\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}