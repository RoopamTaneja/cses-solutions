
// First, we split the graph into SCCs (kosaraju). 
// We then treat each component as a node. So
// then, If the coin collector enters a component, 
// he can collect all the coins in it.

// Since the resulting graph is a DAG, we can use DP to 
// find the maximum coins that can be collected.

// DP : for every incoming edge (u, v) for any SCC node v :
//  ans[v] = max(ans[v], ans[u] + node_val[v])
// where ans[i] = coins collected for a route ending at node i

// Final ans = max(ans[i]) over all scc_nodes i
// (bcoz we don't know optimal ending point)

// This DP handles disconnected SCCs also (yay)

// Time Complexity: O(N+M)

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

void dfs(ll node, vl adj[], ll vis[], stack<int> &st)
{
    vis[node] = 1;
    for (auto it : adj[node])
        if (!vis[it])
            dfs(it, adj, vis, st);

    st.push(node);
}

void dfs2(ll node, vl adjT[], ll vis[], vl &result)
{
    vis[node] = 1;
    result.push_back(node);
    for (auto it : adjT[node])
        if (!vis[it])
            dfs2(it, adjT, vis, result);
}

vector<vl> kosaraju(ll V, vl adj[])
{
    ll vis[V] = {0};
    stack<int> st;

    // first dfs
    for (int i = 1; i < V; i++)
        if (!vis[i])
            dfs(i, adj, vis, st);

    // reversing edges
    vl adjT[V];
    for (ll i = 1; i < V; i++)
    {
        vis[i] = 0;
        for (auto it : adj[i])
            adjT[it].push_back(i);
    }

    // second dfs
    vector<vl> scc;
    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        if (!vis[node])
        {
            vl result;
            dfs2(node, adjT, vis, result);
            scc.emplace_back(result);
        }
    }
    return scc;
}

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    vl kvec(n + 1);
    vl adj[n + 1];
    for (ll i = 1; i <= n; i++)
        cin >> kvec[i];

    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].emplace_back(b);
    }

    vvl result = kosaraju(n + 1, adj);
    vl scc_cnt(n + 1);
    ll val = result.size();
    for (ll i = 0; i < val; i++)
    {
        for (auto &x : result[i])
            scc_cnt[x] = i + 1;
    }
    vl scc_adj[val + 1];
    for (ll i = 1; i <= n; i++)
    {
        for (auto &x : adj[i])
        {
            if (scc_cnt[i] != scc_cnt[x])
                scc_adj[scc_cnt[i]].emplace_back(scc_cnt[x]);
        }
    }

    vl scc_val(val + 1, 0);
    for (ll i = 1; i <= n; i++)
        scc_val[scc_cnt[i]] += kvec[i];

    vl ans = scc_val;
    for (ll i = 1; i <= val; i++)
        for (auto &x : scc_adj[i])
            ans[x] = max(ans[x], ans[i] + scc_val[x]);

    ll fin = -1;
    for (auto &x : ans)
        fin = max(fin, x);
    std::cout << fin << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}