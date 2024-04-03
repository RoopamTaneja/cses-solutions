// Read : https://usaco.guide/problems/cses-1160-planets-queries-ii/solution

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

vl succ;
vvl steps;

void buildsteps(ll n)
{
    ll height = steps[0].size();
    for (ll node = 1; node <= n; node++)
        steps[node][0] = succ[node];
    for (ll i = 1; i < height; i++)
    {
        for (ll node = 1; node <= n; node++)
            if (steps[node][i - 1] != -1)
                steps[node][i] = steps[steps[node][i - 1]][i - 1];
    }
}

ll findsteps(ll node, ll k)
{
    ll height = steps[0].size();
    ll anc = node;
    for (ll i = 0; i < height; i++)
    {
        if (anc == -1)
            break;
        if (k & 1)
            anc = steps[anc][i];
        k >>= 1;
    }
    return anc;
}

void solve()
{
    ll n, q, a, b;
    vl v;
    cin >> n >> q;
    succ.assign(n + 1, -1);
    steps.assign(n + 1, vl(__lg(n) + 2, -1));
    vvl before(n + 1); // before[i] stores nodes having a direct edge to i
    for (ll i = 1; i <= n; i++)
    {
        cin >> succ[i];
        before[succ[i]].emplace_back(i);
    }

    vl cycle_id(n + 1, -2);
    // Values in cycle_id :
    // -2 : Not processed this node yet
    // -1 : This node is in a tree
    // >=0 : This node is in some cycle and its value is the ID of that cycle

    vector<map<ll, ll>> cycles;
    // cycles [i] : contains (node no, position of node in that cycle) pairs of ith cycle

    // So for some node x, cycles[cycle_id[x]][x] => position of x in its cycle (wherever it is)

    for (ll i = 1; i <= n; i++)
    {
        if (cycle_id[i] != -2)
            continue;
        vl path;
        path.emplace_back(i);
        ll curr = i;
        while (cycle_id[succ[curr]] == -2)
        {
            curr = succ[curr];
            cycle_id[curr] = -3; // a temporary value to track which nodes already processed
            path.emplace_back(curr);
        }
        // curr is last node of cycle
        map<ll, ll> cyc;
        bool in_cycle = false;
        for (auto &x : path)
        {
            in_cycle = in_cycle || (x == succ[curr]); // inside cycle from next of curr ie first node of cycle
            if (in_cycle)
            {
                cyc[x] = cyc.size();         // position in cycle
                cycle_id[x] = cycles.size(); // cycle_id updated if in cycle
            }
            else
                cycle_id[x] = -1; // not in cycle => non-root node of tree
        }
        cycles.emplace_back(cyc);
    }

    // BFS to get distance of all nodes from the cycle of their component
    vl cyc_dist(n + 1, 0);
    queue<ll> qu;
    // Initialising the queue with one distance nodes
    for (ll i = 1; i <= n; i++)
    {
        if (cycle_id[i] == -1 && cycle_id[succ[i]] >= 0)
        {
            cyc_dist[i] = 1;
            qu.push(i);
        }
    }
    while (!qu.empty())
    {
        ll curr = qu.front();
        qu.pop();
        cyc_dist[curr] = cyc_dist[succ[curr]] + 1;
        for (auto &x : before[curr])
            qu.push(x);
    }

    // Preparing for binary lifting
    buildsteps(n);

    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        ll k = steps[0].size() - 1;

        // Checking same component => Go ahead as much as possible to see if they end in same cycle or not
        // No -> Not reachable
        if (cycle_id[steps[a][k]] != cycle_id[steps[b][k]])
        {
            cout << -1 << "\n";
            continue;
        }

        // Yes same component :

        // some node in a cycle
        if (cycle_id[a] != -1 || cycle_id[b] != -1)
        {
            // if dest not in cycle => not reachable => since we can't go down from root
            if (cycle_id[a] != -1 && cycle_id[b] == -1)
            {
                cout << -1 << "\n";
                continue;
            }

            // else dest in cycle => ans is dist of a to its root (maybe 0 if a is root) + dist from a_root to b
            ll dist = cyc_dist[a];
            ll a_root = findsteps(a, dist);

            // by reference to save time in copying
            map<ll, ll> &cyc = cycles[cycle_id[a_root]];
            ll a_id = cyc[a_root];
            ll b_id = cyc[b];
            ll diff = b_id - a_id;
            if (diff < 0)
                diff = cyc.size() + diff;
            cout << dist + diff << "\n";
        }
        else
        {
            // both in trees
            ll diff = cyc_dist[a] - cyc_dist[b];

            // if b is lower than a => not reachable whether same or different trees
            if (diff < 0)
            {
                cout << -1 << "\n";
                continue;
            }

            // else move that many steps upwards from a
            // you reach b => both were in same tree and b is ancestor
            if (findsteps(a, diff) == b)
                cout << diff << "\n";

            // else you don't reach b => maybe different trees or not ancestor => not reachable
            else
                cout << -1 << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}