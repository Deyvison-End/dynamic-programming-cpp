#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long count_ssk = 0;



bool subsetSumBF(const vector<int> &array, int K, vector<bool> &subset) {

     int n = array.size();
    int total = 1 << n; // 2^n combinações

    for (int mask = 0; mask < total; mask++) {
        int soma = 0;


        for (int i = 0; i < n; i++)
            subset[i] = false;


        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                soma += array[i];
                subset[i] = true;
            }
        }

        if (soma == K)
            return true;
    }

    return false;
}

bool subsetSumBTRec(const vector<int> &array, int n, int k, vector<bool> &subset) {

    if(k == 0){return true;}
	
	if(k < 0 || n < 0){return false;}
	
	
	subset[n] = false;
    if (subsetSumBTRec(array,n - 1, k, subset))
        return true;
        
    subset[n] = true;
    if (subsetSumBTRec(array, n - 1, k - array[n], subset))
        return true;
        
	subset[n] = false;
    return false;
}

bool subsetSumBT(const vector<int> &array, int k, vector<bool> &subset) {
	return subsetSumBTRec(array, (int)array.size(), k, subset);
}



bool subsetSumGreedy(const vector<int> &array, int k, vector<bool> &subset) {

     int n = array.size();
    subset.assign(n, false);

   
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
        idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return array[a] > array[b];
    });

    int soma = 0;

  
    for (int i = 0; i < n; i++)
    {
        int pos = idx[i];

        if (soma + array[pos] <= k)
        {
            soma += array[pos];
            subset[pos] = true;
        }

        if (soma == k)
            return true;
    }

    return false;
    
}



bool subsetSumRecMemo(const vector<int> &array, int n, int k, vector<bool> &subset, vector<vector<int>> &memo) {

    if (k == 0) return true;  
    if (k < 0 || n == 0) return false; 

    
    if (memo[n][k] != -1) {
        return memo[n][k] == 1;
    }

    
    subset[n - 1] = false;
    if (subsetSumRecMemo(array, n - 1, k, subset, memo)) {
        memo[n][k] = 1; 
        return true;
    }

    
    subset[n - 1] = true;
    if (subsetSumRecMemo(array, n - 1, k - array[n - 1], subset, memo)) {
        memo[n][k] = 1; 
        return true;
    }

    
    subset[n - 1] = false;
    memo[n][k] = 0; 
    return false;
}

bool subsetSumMemo(const vector<int> &array, int k, vector<bool> &subset) {
	vector<vector<int>> memo(array.size() + 1, vector<int>(k + 1,  -1));

	return subsetSumRecMemo(array, (int)array.size(), k, subset, memo);
}

bool subsetSumDP(const vector<int> &array, int k, vector<bool> &subset) {

     int n = array.size();
    
    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));


    for (int i = 0; i <= n; i++)
        dp[i][0] = true;


    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= k; s++) {
            dp[i][s] = dp[i - 1][s];  

            if (s >= array[i - 1]) {
                dp[i][s] = dp[i][s] || dp[i - 1][s - array[i - 1]];
            }
        }
    }

    if (!dp[n][k])
        return false;

    // Reconstrução do subconjunto
    subset.assign(n, false);
    int s = k;
    int i = n;

    while (i > 0 && s > 0) {
        if (!dp[i - 1][s]) {
            subset[i - 1] = true;
            s -= array[i - 1];
        }
        i--;
    }

    return true;
}
 
bool check_sum(const vector<int> &array, int sum, const vector<bool> &subset) {
	int cur_sum = 0;

	for (int i = 0; i < (int)array.size(); i++) {
		if (subset[i]) cur_sum += array[i];
	}

	return (cur_sum == sum);
}

void runSubsetSum(const char *name, bool subsetSum(const vector<int> &, int, vector<bool> &), const vector<int> &array, int sum) {
	using namespace std::chrono;

    count_ssk = 0;

	vector<bool> subset(array.size(), false);

	auto start = high_resolution_clock::now();

	bool found = subsetSum(array, sum, subset);

	auto finish = high_resolution_clock::now();
	long elapsed = duration_cast<nanoseconds>(finish - start).count() / 1000;

	bool valid = found && check_sum(array, sum, subset);

	cout << name << ": " << (found ? ( valid ? "YES " : "ERR " ): " NO ");

	cout << "[time: " << elapsed << "us] ";
	cout << "[count: " << count_ssk << "] ";
	if (found) {
		cout << "[ ";
		for (unsigned i = 0; i < array.size(); i++) {
			if (subset[i])
				cout << array[i] << " ";
		}
		cout << "] ";
	}
	cout << endl;

}


int subsetsum() {
	int size = 20;

	vector<int> array(size);

	srand(333);
//	srand(12345);

	for (int i = 0; i < size; i++) {
		cout << (array[i] = 1 + rand() % (size * 5)) << " ";
	}
	cout << endl;

	cout << endl << "******* SUBSETSUM *******" << endl << endl;

	int value = 0;
	for (int i = 0; i < 20; i++) {
		value += (rand() % (size * 6));
		cout << i << ": Trying " << value << " ..." << endl;

		runSubsetSum("Bruteforce   ", subsetSumBF, array, value);
		runSubsetSum("Backtracking ", subsetSumBT, array, value);
		runSubsetSum("Memoization  ", subsetSumMemo, array, value);
		runSubsetSum("Dynamic Prog.", subsetSumDP, array, value);
		runSubsetSum("Greedy       ", subsetSumGreedy, array, value);
	}


	return 0;
}

