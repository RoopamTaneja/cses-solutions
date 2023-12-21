#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// Datatypes
typedef long long ll;
typedef long double ld;
typedef long int l;
typedef unsigned int ui;

// Vectors
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

// Pairs
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MOD = 1e9 + 7;

void dfs(ll node, vl adj[], ll vis[], stack<ll> &st)
{
    vis[node] = 1;
    for (auto it : adj[node])
        if (!vis[it])
            dfs(it, adj, vis, st);
    st.push(node);
}

vl topoSort(ll V, vl adj[])
{
    ll vis[V + 1] = {0};
    stack<ll> st;
    for (ll i = 1; i <= V; i++)
    {
        if (vis[i] == 0)
        {
            dfs(i, adj, vis, st);
        }
    }
    vl ans;
    while (!st.empty())
    {
        ans.emplace_back(st.top());
        st.pop();
    }
    return ans;
}
vl adj[100001], adjRev[100001]; // global necessary to avoid runtime error

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].eb(b);
        adjRev[b].eb(a);
    }
    vl order = topoSort(n, adj);
    vl dp(n + 1, 0);
    dp[1] = 1;
    for (auto &b : order)
    {
        for (auto &a : adjRev[b])
            dp[b] = (dp[b] + dp[a]) % MOD;
    }
    cout << dp[n] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}