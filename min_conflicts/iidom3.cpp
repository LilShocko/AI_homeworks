#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <chrono>
using namespace std;
int N = 8;
vector<int> queens(N);
vector<int> rows(N);
vector<int> d1(2 * N - 1);
vector<int> d2(2 * N - 1);

int calculateConflicts(int row, int col) {
	/*
	N=4

	 (row - col) - X = (-1)*(N - 1)
		X = (row-col) + N - 1
		X = -3 + 4 - 1 = 0
		X = -1 + 4 -1 =2


	 (row + col) + X = (N-1)*2
		X = (N-1)*2 - (row + col)
	 6, 5, 4,3,2,1,0
	 0, 1, 2,3,4,5,6
	 */
	 //cout <<endl<< rows[row] << " " << d1[(row - col) + N - 1] << " " << d2[(N - 1) * 2 - (row + col)]<<endl;
	return rows[row] + d1[(row - col) + N - 1] + d2[(N - 1) * 2 - (row + col)] - 3;
}

int getColWithQueenWithMaxConf() {
	int maxconflicts = 0;
	vector<int> toberandom;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		arr[i] = calculateConflicts(queens[i], i);
		if (arr[i] > maxconflicts) {
			maxconflicts = arr[i];
			toberandom.clear();
		}
		if (arr[i] == maxconflicts) {
			toberandom.push_back(i);
		}
	}
	if (maxconflicts == 0)return -1;
	/*
	for (int i = 0; i < N; i++) {
		if (arr[i] == maxconflicts) {
			toberandom.push_back(i);
		}
	}*/
	return toberandom[rand() % toberandom.size()];
}
int getRowWithMinConflict(int col) {
	vector<int> arr(N);
	vector<int> toberandom;
	int minelem = N + 3;
	for (int i = 0; i < N; i++) {
		arr[i] = calculateConflicts(i, col);
		if (arr[i] < minelem) {
			minelem = arr[i];
			toberandom.clear();
		}
		if (arr[i] == minelem) {
			toberandom.push_back(i);
		}
	}
	/*
	for (int i = 0; i < N; i++) {
		if (arr[i] == minelem) {
			toberandom.push_back(i);
		}
	}*/
	return toberandom[rand() % toberandom.size()];
}
void initqueens() {
	int a = rand() % N;
	int temp;
	queens[0] = a;
	rows[a] = 1;
	d1[(a - 0) + N - 1]++;
	d2[(N - 1) * 2 - (a + 0)]++;
	for (int i = 1; i < N; i++) {
		temp = getRowWithMinConflict(i);
		queens[i] = temp;
		rows[temp]++;
		d1[(temp - i) + N - 1]++;
		d2[(N - 1) * 2 - (temp + i)]++;
	}
}
void fakeinitqueens() {
	for (int i = 0; i < N; i++) {
		queens[i] = i;
		rows[i]++;
		d1[(i - i) + N - 1]++;
		d2[(N - 1) * 2 - (i + i)]++;
	}
}

void minconflict() {
	initqueens();
	int i = 0;
	int col, row;
	while (true) {
		col = getColWithQueenWithMaxConf();
		if (col == -1) {
			cout << i << endl;
			cout << "namerih reshenie i to e: ";
			for (auto i : queens) {
				cout << i << " ";
			}
			return;
		}
		row = getRowWithMinConflict(col);

		rows[queens[col]]--;
		d1[(queens[col] - col) + N - 1]--;
		d2[(N - 1) * 2 - (queens[col] + col)]--;

		queens[col] = row;

		rows[row]++;
		d1[(row - col) + N - 1]++;
		d2[(N - 1) * 2 - (row + col)]++;
		i++;
	}
}
void print_board() {
	vector<vector<int>> matrix(N, vector<int>(N));
	cout << endl;
	for (int i = 0; i < N; i++) {
		matrix[queens[i]][i] = 1;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

int main() {
	srand(time(NULL));
	minconflict();
	print_board();
	/*
	for (auto i : queens) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : rows) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : d1) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : d2) {
		cout << i << " ";
	}

			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

	*/
	return 0;
}

