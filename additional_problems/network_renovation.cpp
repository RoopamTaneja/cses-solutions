// Remember -> add edges to cover all bridges in graph
// You would boil it down to 2edge connected components
// That would give a tree -> add edges such that
// it stays connected even after removal of some edge
// Say no of leaves = k
// And the ans was ceil(k / 2)
// You needed to connect all leaves
// (can't leave any or else its parent edge on deletion will cause problem)
// To minimise the no of edges, try to connect leaves of different subtrees
// And for that have the size of subtrees to be balanced as possible
// In that optimal case, max subtree size <= floor(k / 2)
// details go into rerooting etc but doesn't matter since DFS order of leaves remains same
// So if u just order leaves as per DFS order, and connect ith leaf to (i + floor(k / 2))th leaf
// Then u will surely reach out to a different subtree and that's enough to ensure connectivity
// If k is odd, connect kth leaf to any other leaf

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

void dfs(ll s, ll e, vl &v, vl adj[])
{
    for (auto &x : adj[s])
    {
        if (x == e)
            continue;
        dfs(x, s, v, adj);
    }
    if (adj[s].size() == 1)
        v.push_back(s);
}

int main()
{
    ll n;
    cin >> n;
    vl adj[n + 1];
    for (ll i = 0; i < n - 1; i++)
    {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vl v;
    dfs(1, -1, v, adj);
    ll k = v.size();
    cout << (k + 1) / 2 << "\n";
    for (ll i = 0; i < k / 2; i++)
        cout << v[i] << " " << v[i + k / 2] << "\n";
    if (k % 2)
        cout << v[k - 1] << " " << v[0] << "\n";
}