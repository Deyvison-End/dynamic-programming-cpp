#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

float solve(const vector<int> &price, const vector<int> &weight, int k) {
    
    int n = price.size();

    
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
        idx[i] = i;

   
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return (float)price[a] / weight[a] > (float)price[b] / weight[b];
    });

    float valorTotal = 0.0;
    int capacidadeRestante = k;

    for (int i = 0; i < n; i++) {
        int id = idx[i];

        if (capacidadeRestante == 0)
            break;

        
        if (weight[id] <= capacidadeRestante) {
            valorTotal += price[id];
            capacidadeRestante -= weight[id];
        }
        else {
            
            float fracao = (float)capacidadeRestante / weight[id];
            valorTotal += price[id] * fracao;
            capacidadeRestante = 0;
        }
    }

    return valorTotal;
}

int mochila() {
    cout << endl << "******* MOCHILA *******" << endl << endl;

    vector<int> precos = {100, 10 , 10, 100, 50};
    vector<int> pesos  = {50, 50, 100, 20, 10};
    int K = 100;

    float res = solve(precos, pesos, K);

    cout << res << endl; // 254

    return 0;
}


