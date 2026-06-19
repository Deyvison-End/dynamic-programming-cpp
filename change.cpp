#include <vector>
#include <climits>
#include <iostream>

using namespace std;

class Solution {

public:

    int coinChange(const vector<int>& coins, int amount) {
        
    const int INF = amount + 1;
    
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int v = 1; v <= amount; v++) {
        for (int coin : coins) {
            if (v - coin >= 0) {
                dp[v] = min(dp[v], 1 + dp[v - coin]);
            }
        }
    }

    return (dp[amount] == INF) ? -1 : dp[amount];
    }

};

int change() {
    cout << endl << "******* CHANGE *******" << endl << endl;

    cout << Solution().coinChange({1, 2}, 10) << endl; // res = 5
    cout << Solution().coinChange({1, 2, 5}, 10) << endl; // res = 2
    cout << Solution().coinChange({1, 2, 5}, 11) << endl; // res = 3
    cout << Solution().coinChange({1, 6, 7, 9, 11}, 13) << endl; // res = 2 (greedy = 3)
    cout << Solution().coinChange({1, 2, 5, 10}, 16) << endl; // res = 3
    cout << Solution().coinChange({1, 2, 7, 10}, 16) << endl; // res = 3 (greedy = 4)
    cout << Solution().coinChange({1, 2, 5, 7, 8}, 30) << endl; // res = 4
    cout << Solution().coinChange({83, 186, 408, 419}, 6249) << endl; // res = 20

    return 0;
}