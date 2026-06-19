#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<int> memo;

public:
    Solution() : memo(46, -1) {}

    int climbStairs(int n) {
        
        if (n <= 2)
        return n;

    int prev2 = 1;  // dp[1]
    int prev1 = 2;  // dp[2]
    int current;

    for (int i = 3; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;

    }
};

int stairs() {

    cout << endl << "******* STAIRS *******" << endl << endl;

    cout << Solution().climbStairs(1) << endl; // res = 1
    cout << Solution().climbStairs(2) << endl; // res = 2
    cout << Solution().climbStairs(3) << endl; // res = 3
    cout << Solution().climbStairs(4) << endl; // res = 5
    cout << Solution().climbStairs(5) << endl; // res = 8
    cout << Solution().climbStairs(10) << endl; // res = 89
    cout << Solution().climbStairs(45) << endl; // res = 1836311903 (45 eh o limite)

    return 0;
}