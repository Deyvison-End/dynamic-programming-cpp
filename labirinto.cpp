#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool validar(const vector<string> &lab, int i, int j) {
	return (i >= 0 && j >= 0 && i < lab.size() && j < lab[i].size());
}

bool acharCaminho(vector<string> &lab, int i, int j) {
	if (!validar(lab, i, j)) return false;


	if (lab[i][j] == '#' || lab[i][j] == 'x') return false;


	if (lab[i][j] == 'd') return true;


	if (lab[i][j] != 'o')
		lab[i][j] = 'x';


	if (acharCaminho(lab, i + 1, j)) return true;
	if (acharCaminho(lab, i - 1, j)) return true;
	if (acharCaminho(lab, i, j + 1)) return true;
	if (acharCaminho(lab, i, j - 1)) return true;

	if (lab[i][j] == 'x')
		lab[i][j] = '.';

	return false;
}

void solve(vector<string> &M) {

	int si = -1, sj = -1;
	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[i].size(); j++) {
			if (M[i][j] == 'o') {
				si = i;
				sj = j;
				break;
			}
		}
		if (si != -1) break;
	}

	
	if (si != -1)
		acharCaminho(M, si, sj);

}

void print(const vector<string> &M) {
	for (auto &s : M) {
		cout << s << endl;
	}
	cout << endl;
}

int labirinto() {
	cout << endl << "******* LABIRINTO *******" << endl << endl;

	vector<string> M1 = {
		".#...",
		"...##",
		".#..#",
		"o##.d",
		"#####"
	};

	vector<string> M2 = {
		"#...o",
		"..###",
		".#...",
		"...#.",
		"###d."
	};

	solve(M1);
	print(M1);

	/* saída valida
	.#...
	xxx##
	x#xx#
	o##xd
	#####
	*/

	solve(M2);
	print(M2);

	/*
	#xxxo
	xx###
	x#xxx
	xxx#x
	###dx
	 */

	return 0;
}