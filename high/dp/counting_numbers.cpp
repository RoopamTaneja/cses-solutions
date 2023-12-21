#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[20][10][2][2]; // dp[no_of_digits][last_dig][tight][started]
void reset()
{
    for (ll i = 0; i < 20; i++)
        for (ll j = 0; j < 10; j++)
            for (ll k = 0; k < 2; k++)
                for (ll l = 0; l < 2; l++)
                    dp[i][j][k][l] = -1;
}

ll f(ll n, ll last_dig, bool tight, bool started, string &num)
{
    if (n == 0) // number complete
        return 1;
    if (last_dig != -1 && dp[n][last_dig][tight][started] != -1)
        return dp[n][last_dig][tight][started]; // subproblem is already solved

    ll curr_dig = num[num.size() - n] - '0';
    ll ub = 9;
    if (tight)
        ub = curr_dig;

    ll ans = 0;
    for (ll dig = 0; dig <= ub; dig++)
    {
        if ((dig == last_dig) && started)
            continue; // consecutive digits AND NOT consec leading zeroes

        // diff from last digit or case of consecutive leading zeroes
        ans += f(n - 1, dig, (tight && (dig == ub)), (started || (dig != 0)), num);
    }
    return dp[n][last_dig][tight][started] = ans;
}

// TC : O(10^2 * (no of digits))

void solve()
{
    ll a, b;
    cin >> a >> b;
    string s1 = to_string(a - 1);
    string s2 = to_string(b);
    reset();
    ll ans2 = f(s2.size(), -1, 1, 0, s2);
    if (a == 0)
        cout << ans2 << "\n";
    else
    {
        reset();
        ll ans1 = f(s1.size(), -1, 1, 0, s1);
        cout << ans2 - ans1 << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}