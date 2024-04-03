#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

void solve()
{
    ll n;
    cin >> n;
    vl succ(n + 1);
    vl ans(n + 1);
    vvl before(n + 1);
    for (ll i = 1; i <= n; i++)
    {
        cin >> succ[i];
        before[succ[i]].emplace_back(i);
    }
    vector<bool> vis(n + 1, false);
    vector<bool> inCyc(n + 1, false);

    // DFS for getting lengths of cycles
    for (ll i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        vis[i] = true;
        ll curr = i;
        vl path;
        path.emplace_back(curr);
        while (!vis[succ[curr]])
        {
            curr = succ[curr];
            vis[curr] = true;
            path.emplace_back(curr);
        }
        curr = succ[curr];

        vl tmp = path;
        ll cyc_len = 1;
        while (!tmp.empty() && tmp.back() != curr)
        {
            cyc_len++;
            tmp.pop_back();
        }
        bool in_cycle = false;
        for (auto &x : path)
        {
            in_cycle = in_cycle || (x == curr);
            if (in_cycle)
            {
                ans[x] = cyc_len;
                inCyc[x] = true;
            }
        }
    }

    // BFS to get distance of all nodes from the cycle of their component
    vl cyc_dist(n + 1, 0);
    queue<ll> qu;
    // Initialising the queue with one distance nodes
    for (ll i = 1; i <= n; i++)
    {
        if (!inCyc[i] && inCyc[succ[i]])
        {
            ans[i] = 1 + ans[succ[i]];
            qu.push(i);
        }
    }
    while (!qu.empty())
    {
        ll curr = qu.front();
        qu.pop();
        ans[curr] = ans[succ[curr]] + 1;
        for (auto &x : before[curr])
            qu.push(x);
    }

    for (ll x = 1; x <= n; x++)
        cout << ans[x] << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}