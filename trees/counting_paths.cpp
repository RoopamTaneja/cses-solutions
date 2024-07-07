#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
vvl children;
vl parent;
vvl ances;
vl level;

void dfs_init(ll node)
{
    for (auto &x : children[node])
    {
        if (x == parent[node])
            continue;
        parent[x] = node;
        level[x] = level[node] + 1;
        dfs_init(x);
    }
}

void buildances(ll n)
{
    ll height = ances[0].size();
    for (ll node = 1; node <= n; node++)
        ances[node][0] = parent[node];
    for (ll i = 1; i < height; i++)
    {
        for (ll node = 1; node <= n; node++)
            if (ances[node][i - 1] != -1)
                ances[node][i] = ances[ances[node][i - 1]][i - 1];
    }
}

ll findances(ll node, ll k)
{
    ll height = ances[0].size();
    ll anc = node;
    for (ll i = 0; i < height; i++)
    {
        if (anc == -1)
            break;
        if (k & 1)
            anc = ances[anc][i];
        k >>= 1;
    }
    return anc;
}

ll lca(ll a, ll b)
{
    ll height = ances[0].size();
    if (level[a] > level[b])
        swap(a, b);
    if (level[b] != level[a])
        b = findances(b, level[b] - level[a]);
    if (a == b)
        return a;
    for (ll i = height - 1; i >= 0; i--)
    {
        if (ances[a][i] != ances[b][i])
        {
            a = ances[a][i];
            b = ances[b][i];
        }
    }
    return ances[a][0];
}

bool isLeaf(ll u, vvl &adj)
{
    if (u != 1 && adj[u].size() == 1)
        return true;
    return false;
}

void dfs(ll s, ll e, vvl &adj, vl &dp)
{
    if (isLeaf(s, adj))
        return;
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dfs(u, s, adj, dp);
    }
    for (auto u : adj[s])
    {
        if (u == e)
            continue;
        dp[s] += dp[u];
    }
}

void solve()
{
    ll n, m, a, b;
    cin >> n >> m;
    ll k = log2(n) + 1;
    children.assign(n + 1, vl(0));
    parent.assign(n + 1, -1);
    ances.assign(n + 1, vl(k, -1));
    level.assign(n + 1, 0);
    for (ll i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        children[a].emplace_back(b);
        children[b].emplace_back(a);
    }
    dfs_init(1);
    buildances(n);
    vl dp(n + 1, 0);
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        ll c = lca(a, b);
        dp[a]++, dp[b]++;
        dp[c]--;
        if (parent[c] != -1)
            dp[parent[c]]--;
    }
    dfs(1, 0, children, dp);
    for (ll i = 1; i <= n; i++)
        cout << dp[i] << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}