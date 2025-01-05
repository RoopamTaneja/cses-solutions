// Xij = 1 if (i,j) is empty 0 otherwise
// E(empty squares) = sum of E(Xij) = sum of P(i, j is empty)
// Since motion of each robot is independent to each other, we can focus on 1 robot at a time
// For each robot, find P(that robot is in (i,j) after n steps)
// P(i, j is empty after n steps) = product of 1 - P(that robot is in (i,j) after n steps) over all robots

// P(that robot is in (i,j) after n steps) :
// dp[k][i][j] : prob of robot to in (i,j) after k steps.
// State transition :
//     dp[k + 1][ni][nj] += dp[k][i][j] / dir;
// where prob I am in ni, nj after this step is contributed by i, j * (1/no of available directions I have to move)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<ld> vld;
typedef vector<vld> vvld;
ll dx[4] = {1, -1, 0, 0};
ll dy[4] = {0, 0, 1, -1};
int main()
{
    ll n;
    cin >> n;
    vvld ans(8, vld(8, 1));
    for (ll a = 0; a < 8; a++)
    {
        for (ll b = 0; b < 8; b++)
        {
            vector<vvld> dp(n + 1, vvld(8, vld(8, 0)));
            dp[0][a][b] = 1; // focussing on robot starting at (a,b)
            for (ll k = 0; k < n; k++)
            {
                for (ll i = 0; i < 8; i++)
                {
                    for (ll j = 0; j < 8; j++)
                    {
                        ll dir = 0;
                        for (ll t = 0; t < 4; t++)
                        {
                            ll ni = i + dx[t], nj = j + dy[t];
                            if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
                                dir++;
                        }
                        for (ll t = 0; t < 4; t++)
                        {
                            ll ni = i + dx[t], nj = j + dy[t];
                            if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
                                dp[k + 1][ni][nj] += dp[k][i][j] / dir;
                        }
                    }
                }
            }
            for (ll i = 0; i < 8; i++)
                for (ll j = 0; j < 8; j++)
                    ans[i][j] *= (1 - dp[n][i][j]);
        }
    }
    ld val = 0;
    for (ll i = 0; i < 8; i++)
        for (ll j = 0; j < 8; j++)
            val += ans[i][j];
    cout << fixed << setprecision(6) << val << "\n";
    return 0;
}