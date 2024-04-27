// Either convert to max flow and use max flow algo
// Or use a matching specific algo (like Hopcroft Karp)
// Here : Max Flow : Edmonds Karp - O(VE^2)

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

void solve()
{
    ll n, m, k, a, b;
    cin >> n >> m >> k;
    // add a source and sink
    ll s = 0, t = n + m + 1;
    vl parent(n + m + 2);
    vl adj[n + m + 2];
    vvl cap(n + m + 2, vl(n + m + 2, 0));
    vector<bool> vis(n + m + 2, 0);
    set<pll> st;
    // set for handling multiple edges between same pair of nodes
    for (ll i = 0; i < k; i++)
    {
        cin >> a >> b;
        st.insert(mp(a, b));
    }
    for (auto &p : st)
    {
        a = p.first;
        b = p.second;
        adj[a].eb(n + b);
        adj[n + b].eb(a);
        cap[a][n + b] = 1;
    }
    for (ll i = 1; i <= n; i++)
    {
        adj[s].eb(i);
        adj[i].eb(s);
        cap[s][i] = 1;
    }
    for (ll i = n + 1; i <= n + m; i++)
    {
        adj[i].eb(t);
        adj[t].eb(i);
        cap[i][t] = 1;
    }
    ll max_flow = 0;
    // finding all paths which contribute a flow = 1
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
    // all such paths are of length 3 and all 3 will have capacity 0 (critical edges)
    // so we will look for edges originally between set of boys and girls (which had capacity 1 initially)
    // and now have capacity = 0 => are critical => are part of (exactly) one flow of final network
    // all these edges are part of the max flow or max matching
    vector<pll> ans;
    for (ll i = 1; i <= n; i++)
    {
        for (auto &j : adj[i])
        {
            if (cap[i][j] == 0 && j > 0)
                ans.eb(mp(i, j - n));
        }
    }
    cout << max_flow << "\n";
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
