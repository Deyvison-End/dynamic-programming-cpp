#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <vector>

unsigned long long count_ssm = 0;

using namespace std;



// start e finish: início e final sendo testado agora;
// ini e end: onde são retornados o início e final da melhor sequência
// retorno é a soma da maior sequência
int subseqMaxBF(const vector<int> &array, int & ini, int & end) {
	// TODO
	int maior;
	int soma;
	int TAM = array.size();
	for(int i = 0; i < TAM; i++)
	{
	    soma = 0;
	    if(i == 0){maior = array[i];}
	    for(int j = i; j < TAM; j++)
	    {
	       soma += array[j]; 
	       if(soma > maior)
	       {
	           ini = i; 
	           end = j;
	           maior = soma;
	       }
	    }
	    
	}
	return maior;
}

int subseqMaxMiddle(const vector<int> &array, int start, int middle, int finish, int & ini, int & end) {

	int maxL = 0, maxR = 0;
	int sumL = 0, sumR = 0;

	ini = end = middle;

	for (int i = middle - 1; i >= start; i--) {
		count_ssm ++;
		sumL += array[i];
		if (sumL > maxL) {
			maxL = sumL;
			ini = i;
		}
	}

	for (int i = middle + 1; i <= finish; i++) {
		count_ssm ++;
		sumR += array[i];
		if (sumR > maxR) {
			maxR = sumR;
			end = i;
		}
	}

	return maxL + maxR + array[middle];
}

int subseqMaxDC_Rec(const vector<int> &array, int start, int finish, int & ini, int & end) {
	
    if (start == finish) {
        ini = start;
        end = finish;
        return array[start];
    }

    int meio = (start + finish) / 2;

    int iniL, endL;
    int iniR, endR;
    int iniM, endM;

    int somaEsq  = subseqMaxDC_Rec(array, start, meio, iniL, endL);
    int somaDir  = subseqMaxDC_Rec(array, meio + 1, finish, iniR, endR);
    int somaMeio = subseqMaxMiddle(array, start, meio, finish, iniM, endM);

    if (somaEsq >= somaDir && somaEsq >= somaMeio) {
        ini = iniL;
        end = endL;
        return somaEsq;
    }
    else if (somaDir >= somaEsq && somaDir >= somaMeio) {
        ini = iniR;
        end = endR;
        return somaDir;
    }
    else {
        ini = iniM;
        end = endM;
        return somaMeio;
    };
}

int subseqMaxDC(const vector<int> &array, int & ini, int & end) {
	
	int len = (int)array.size();
	return subseqMaxDC_Rec(array, 0, len - 1, ini, end);
}

int seqMax(const vector<int> &array, int pos, int & ini) {

	if (pos < 0) return 0;
	int sum, iniPrev;

	count_ssm ++;
	int x = array[pos];
	int sumPrev = x + seqMax(array, pos - 1, iniPrev);

	if ( x >= sumPrev) {		
		sum = array[pos];
		ini = pos;
	} else {
		sum = sumPrev;
		ini = iniPrev;
	}

	return sum;
}

int subseqMaxRec(const vector<int> &array, int & ini, int & end) {
	
	int sum = 0;
	int len = (int)array.size();
	ini = end = -1;

	count_ssm = 0;

	for (int i = 0; i < len; i++) {
		int _ini, _sum;
		_sum = seqMax(array, i, _ini);

		if (_sum > sum) {
			sum = _sum;
			ini = _ini;
			end = i;
		}
	}

	return sum;
}



int seqMaxMemo(const vector<int> &array, int pos, int & ini, vector<int> &SUM, vector<int> &INI) {

      if (pos < 0) return 0;


    if (SUM[pos] != -1) {
        ini = INI[pos];
        return SUM[pos];
    }

    count_ssm++;

    int x = array[pos];
    int iniPrev;
    int sumPrev = x + seqMaxMemo(array, pos - 1, iniPrev, SUM, INI);

    int sum;

    if (x >= sumPrev) {        
        sum = x;
        ini = pos;
    } else {                   
        sum = sumPrev;
        ini = iniPrev;
    }

    
    SUM[pos] = sum;
    INI[pos] = ini;

    return sum;

}

int subseqMaxMemo(const vector<int> &array, int & ini, int & end) {
	
	int sum = 0;
	int len = (int)array.size();
	ini = end = -1;

	count_ssm = 0;

	for (int i = 0; i < len; i++) {
		int _ini, _sum;
		_sum = seqMax(array, i, _ini);

		if (_sum > sum) {
			sum = _sum;
			ini = _ini;
			end = i;
		}
	}

	return sum;
}


void runSubseqMax(const char * name, int subseqmax(const vector<int> &, int&, int&), const vector<int> & array, bool printSeq) {
	using namespace std::chrono;

	count_ssm = 0;

	int ini = 0, end = 0;

	auto start = high_resolution_clock::now();

	int max = subseqmax(array, ini, end);

	auto finish = high_resolution_clock::now();
	long elapsed = duration_cast<nanoseconds>(finish-start).count() / 1000;

	cout << name << ": " << max << " ";


	cout << "[time: "<< setw(6) << setfill(' ') << elapsed << "us] ";
	cout << "[count: " << setw(6) << setfill(' ') << count_ssm << "] ";

	if (printSeq) {
		cout << "[ ";
		for (int i = ini; i <= end; i++) cout << array[i] << " ";
		cout << "] ";
	}

	cout << endl;
}


int subseqmax() {
	bool printSeq = true;
	int size = 30;

	srand(12345);

	vector<int> array(size);

	cout << endl << "******* SUBSEQMAX *******" << endl << endl;

	for (int i = 0; i < 10; i++) {

		for (int j = 0; j < size; j++) {
			array[j] = (rand() % (3 * size)) - (rand() % (4 * size));
		}

		cout <<"Test " << i << ": ";
		if (printSeq) {
			for (auto v : array) cout << v << " ";
		}
		cout << endl;

		runSubseqMax("Bruteforce     ", subseqMaxBF, array, printSeq);
		runSubseqMax("Divide&Conquer ", subseqMaxDC, array, printSeq);
		runSubseqMax("Recursive      ", subseqMaxRec, array, printSeq);
		runSubseqMax("Memoization    ", subseqMaxMemo, array, printSeq);
	}

	return 0;
}