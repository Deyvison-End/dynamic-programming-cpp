#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &array, int start, int finish) {
    
    int pivot = array[start];      
    int i = start - 1;
    int j = finish + 1;
    
    while (true) {
        
        do {
            i++;
        } while (array[i] < pivot);
        
        
        do {
            j--;
        } while (array[j] > pivot);
        
        
        if (i >= j) {
            return j;
        }
        
        
        swap(array[i], array[j]);
    }
   
}

int quickselect(vector<int> &values, int k) {
    
    int start = 0;
    int finish = values.size() - 1;

    
    int target = values.size() - k;

    while (start < finish) {
        int p = partition(values, start, finish);

        if (target <= p) {
            // busca na esquerda
            finish = p;
        } else {
            // busca na direita
            start = p + 1;
        }
    }

    return values[target];
}

class KthLargest {
    int k;
    vector<int> scores;
public:
    KthLargest(int k, vector<int>& nums) : k(k), scores(nums.size()) {
    
       scores = nums;
    }

    int add(int val) {
    
        scores.push_back(val);
        return quickselect(scores,k);
    }

    const vector<int> & values() {
        return scores;
    } 
};


int kthlargest() {
    cout << endl << "******* KTHLARGEST *******" << endl << endl;

    vector<int> nums = {4, 5, 8, 2};
    vector<int> vals = {3, 5, 10, 9, 4};
    KthLargest kthLargest (3, nums);

    for (int v : vals) {
        cout << "Adicionando " << v << ", 3o maior eh " << kthLargest.add(v) << endl;
        for (int x : kthLargest.values()) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
