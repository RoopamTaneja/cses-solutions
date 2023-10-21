// Just LIS + Binary Search

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;
typedef vector<vl> vvl;

ll lis(vl const &arr)
{
    ll n = arr.size();
    vl dp;
    dp.eb(arr[0]);
    for (ll i = 1; i < n; i++)
    {
        if (arr[i] > dp.back())
            dp.eb(arr[i]);
        else
        {
            ll l = lower_bound(dp.begin(), dp.end(), arr[i]) - dp.begin();
            dp[l] = arr[i];
        }
    }
    return dp.size();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, val;
    vl v, seq;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> val;
        v.eb(val);
    }
    cout << lis(v) << "\n";

    return 0;
}
