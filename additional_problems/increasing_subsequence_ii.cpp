// dp[i] = no of increasing subseq ending at i (value and NOT index)
// dp[i] = (sum of dp[j] (j from 1 to i-1)) + 1 (new subseq starting here)
// ie dp[i] = pref[i-1] + 1 and pref needs to be updated
// Equivalent to dynamic RSQ => fenwick tree
// Ans = sum of dp[i] from i = 1 to max_value => pref(max_value)
// But values <= 1e9 => MLE : Soln : Coordinate compression

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll mod = 1e9 + 7;

vl fw;
ll sum(ll k)
{
    ll sm = 0;
    while (k >= 1)
    {
        sm = (sm + fw[k]) % mod;
        k -= (k & -k);
    }
    return sm;
}

void add(ll k, ll x)
{
    ll n = fw.size() - 1;
    while (k <= n)
    {
        fw[k] = (fw[k] + x) % mod;
        k += (k & -k);
    }
}

int main()
{
    ll n;
    cin >> n;
    vl v(n);
    for (auto &x : v)
        cin >> x;
    vl temp = v;
    sort(temp.begin(), temp.end());                               // O(n lg n)
    temp.resize(unique(temp.begin(), temp.end()) - temp.begin()); // O(n)
    for (ll i = 0; i < n; i++)                                    // O(n lg n)
        v[i] = lower_bound(temp.begin(), temp.end(), v[i]) - temp.begin() + 1;
    ll end = temp.size();
    fw.assign(end + 1, 0);
    for (auto &x : v) // O(n lg n)
    {
        ll val = 1;
        if (x > 1)
            val = (val + sum(x - 1)) % mod;
        add(x, val);
    }
    cout << sum(end) << "\n";
    return 0;
}