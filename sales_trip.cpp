#include <vector>
#include <iostream>
#include <ranges>

using namespace std;

int max_profit(const vector<int> &costs, const vector<int> &sales) {
    
    int TAM = costs.size();
    int maiorLucro = 0;
    for(int i = 0; i < TAM; i++)
    {
        int lucro = 0;
        for(int j = i; j < TAM; j++)
        {
            lucro += sales[j] - costs[j];
             if(lucro > maiorLucro)
                {
                    maiorLucro = lucro;
                }
        }
    }
    return maiorLucro;
}


int sales_trip() {
    cout << endl << "******* SALES_TRIP *******" << endl << endl;

    vector<int> costs = {10, 22, 15, 20, 18, 16, 14, 12, 10};
    vector<int> sales = {17, 12, 21, 15, 25, 40, 34, 20, 5};

    cout << "Max profit = " << max_profit(costs, sales) << endl; // 60

    return 0;
}