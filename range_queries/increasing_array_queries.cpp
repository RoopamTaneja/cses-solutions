#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vl fenwick;
vl fenw_arr;
ll sum_fenwick(ll k)
{
    ll s = 0;
    while (k >= 1)
    {
        s += fenwick[k];
        k -= (k & -k);
    }
    return s;
}
void add_fenwick(ll k, ll x)
{
    ll n = fenwick.size() - 1;
    fenw_arr[k] += x;
    while (k <= n)
    {
        fenwick[k] += x;
        k += (k & -k);
    }
}
void set_fenwick(ll k, ll x)
{
    add_fenwick(k, x - fenw_arr[k]);
}

void solve()
{
    ll n, q;
    cin >> n >> q;
    vl v(n + 1);
    for (ll i = 1; i <= n; i++)
        cin >> v[i];
    vector<vector<pll>> queries(n + 1);
    ll a, b;
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        queries[a].emplace_back(mp(b, i));
    }
    // Like Distinct Values Queries, you handle different queries on basis of their
    // starting index, from largest to smallest
    vl pref(n + 1);
    pref[0] = 0; // Normal prefix sum for quickly finding RSQ later ( Static arrays -> pref :) )
    for (ll i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + v[i];

    vl soln(q, -1);
    fenwick.resize(n + 1, 0);
    fenw_arr.resize(n + 1, 0);
    // Fenwick to store contributions of towering elements
    // As you traverse array from behind, new ones appear and old ones may go => Dynamic array
    // And we'll need sum of different ranges => Dynamic RSQ => Fenwick
    vector<pll> maxes; // Monotonic stack
    for (ll i = n; i > 0; i--)
    {
        while (!maxes.empty() && v[i] >= maxes.back().first) // Next Greater Element
        {
            set_fenwick(maxes.size(), 0); // No more contri
            maxes.pop_back();
        }
        ll len;
        if (maxes.empty())
            len = n + 1 - i;
        else
            len = maxes.back().second - i;
        maxes.push_back(mp(v[i], i));
        set_fenwick(maxes.size(), (ll)v[i] * len); // Set contri value for this element of stack
        for (auto &x : queries[i])
        {
            // binary search :
            // indices of towering elements are in descending order, we need
            // the index <= q_end but as large as possible => First one
            ll q_end = x.first;
            ll s = 0, e = maxes.size() - 1;
            while (s < e)
            {
                ll mid = (s + e) / 2;
                if (maxes[mid].second <= q_end)
                    e = mid;
                else
                    s = mid + 1;
            }
            ll sum1 = sum_fenwick(maxes.size()) - sum_fenwick(s + 1);       // range_sum of contri from current till second last
            ll sum2 = (ll)(q_end - maxes[s].second + 1) * (maxes[s].first); // last's contri may be partial, so found separately
            ll pref_sum = pref[q_end] - pref[i - 1]; // range sum
            soln[x.second] = sum1 + sum2 - pref_sum; // ans = contri - range sum
        }
    }
    for (auto &i : soln)
        cout << i << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}