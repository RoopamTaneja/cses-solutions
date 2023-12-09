#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
#define MAX_SUM 2e5 * 1e9

bool is_possible(vl &v, ll k, ll max_sum)
{
    ll subarr_cnt = 0;
    ll curr_sum = 0;
    for (auto i : v)
    {
        if (i > max_sum)
            return false;
        if (curr_sum + i > max_sum)
        {
            subarr_cnt++;
            curr_sum = 0;
        }
        curr_sum += i;
    }
    if (curr_sum > 0)
        subarr_cnt++;
    return subarr_cnt <= k;
}

int main()
{
    int n, k, entry;
    cin >> n >> k;
    vl v;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    ll l = 1, r = MAX_SUM;
    while (l < r)
    {
        ll mid = (l + r) / 2;
        if (is_possible(v, k, mid) == true)
            r = mid;
        else
            l = mid + 1;
    }
    cout << r << "\n"; // or l both are same
    return 0;
}