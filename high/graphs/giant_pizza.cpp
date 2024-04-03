// First read CPH Pg 160 to 162

// It is worth paying attention to the property of the implication graph:
// if there is an edge a -> b, then there also is an edge neg b -> neg a

// Optional reading : https://cp-algorithms.com/graph/2SAT.html.

// + i => xi and - i => neg xi
// Idea:
// Exactly 2 sat problem
// Take inputs, add edges
// Make SCCs, check if xi and neg xi belong to same SCC
// If not, process from last SCC given by Kosaraju and assign true
// nodes you encounter

// IMP:
// 2*k => xk and 2*k + 1=> neg xk
// Going back => just divide by 2
// Now for any even value z, z^1 == z+1
// And odd value : z^1 == z+1
// So we will use 0-based indexing
// neg xk == xk ^ 1 and xk == neg xk ^ 1
// 0 .. m-1 will map to (0, 1); (2, 3); .. ; (2m-2, 2m-1)

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;
typedef vector<vl> vvl;

void dfs(ll node, vl adj[], ll vis[], vl &st)
{
    vis[node] = 1;
    for (auto it : adj[node])
        if (!vis[it])
            dfs(it, adj, vis, st);

    st.push_back(node);
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
    vl st;
    for (ll i = 0; i < V; i++)
        if (!vis[i])
            dfs(i, adj, vis, st);
    vl adjT[V];
    for (ll i = 0; i < V; i++)
    {
        vis[i] = 0;
        for (auto it : adj[i])
            adjT[it].push_back(i);
    }
    vector<vl> scc;
    while (!st.empty())
    {
        ll node = st.back();
        st.pop_back();
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
    ll n, m;
    cin >> n >> m;
    vl adj[2 * m];
    char ch;
    ll k;
    for (ll i = 0; i < n; i++)
    {
        cin >> ch >> k;
        k--;
        ll a = 2 * k;
        if (ch == '-')
            a = a ^ 1;
        cin >> ch >> k;
        k--;
        ll b = 2 * k;
        if (ch == '-')
            b = b ^ 1;
        ll nega = a ^ 1, negb = b ^ 1;
        adj[nega].eb(b);
        adj[negb].eb(a);
    }
    vvl result = kosaraju(2 * m, adj);
    ll val = result.size();
    vl scc_cnt(2 * m);
    for (ll i = 0; i < val; i++)
    {
        for (auto &j : result[i])
            scc_cnt[j] = i + 1;
    }
    for (ll i = 0; i < 2 * m; i += 2)
    {
        if (scc_cnt[i] == scc_cnt[i + 1])
        {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vl ans(m, -1);
    for (ll i = val - 1; i >= 0; i--)
    {
        for (auto &j : result[i])
        {
            if (ans[j / 2] == -1)
            {
                if (j % 2)
                    ans[j / 2] = 0;
                else
                    ans[j / 2] = 1;
            }
        }
    }
    for (auto &x : ans)
    {
        if (x == 0)
            cout << "- ";
        else
            cout << "+ ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
