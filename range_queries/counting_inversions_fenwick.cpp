// Another method for counting inversions of an array in O(n*lg n)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

// fenwick till max(a[i])
// since a[i] goes upto 1e18, we need coordinate compression
vl fw;
ll sum(ll k)
{
    ll s = 0;
    while (k >= 1)
    {
        s += fw[k];
        k -= (k & -k);
    }
    return s;
}
void add(ll k, ll x)
{
    ll n = fw.size() - 1;
    while (k <= n)
    {
        fw[k] += x;
        k += (k & -k);
    }
}
ll inversionCount(vl &v, ll n)
{
    // coordinate compression (mapping v[i] to values from 1 to n)
    vl temp = v;
    sort(temp.begin(), temp.end());
    temp.resize(unique(temp.begin(), temp.end()) - temp.begin());
    for (ll i = 0; i < n; i++)
        v[i] = lower_bound(temp.begin(), temp.end(), v[i]) - temp.begin() + 1;
    // Alternate way of coordinate compression (slower)
    // map<ll, ll> m;
    // for (ll i = 0; i < n; i++)
    //     m[temp[i]] = i + 1;
    // for (ll i = 0; i < n; i++)
    //     v[i] = m[v[i]];
    ll ans = 0;
    fw.assign(temp.size() + 1, 0);
    for (ll i = 0; i < n; i++)
    {
        ans += sum(temp.size()) - sum(v[i]);
        add(v[i], 1);
    }
    return ans;
}

int main()
{
    return 0;
}