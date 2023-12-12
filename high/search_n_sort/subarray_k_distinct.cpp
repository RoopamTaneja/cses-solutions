#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;

void solve()
{
    ll n, entry, k;
    vl v;
    cin >> n >> k;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }

    // Q1) No of subarrays with distinct values atmost k
    ll l = 0;
    ll r = 0;
    ll ans = 0;
    unordered_map<ll, ll> m; // prefer map or safe_map instead
    while (r < n)
    {
        m[v[r]]++;
        while (m.size() > k)
        {
            m[v[l]]--;
            if (m[v[l]] == 0)
                m.erase(v[l]);
            l++;
        }
        ans += (r - l + 1);
        r++;
    }
    cout << ans << "\n";

    // Q2) No of subarrays with exactly k distinct
    // Ans = f(k) - f(k-1)

    // Q3) Length of longest subarray with atmost k distinct
    // replace ans += (r-l+1) with ans = max((r-l+1), ans)
    // because with each increment, longest subarray added is of
    // (r-l+1) length
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
