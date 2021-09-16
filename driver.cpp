#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <ctime>

using namespace std;

//-----------------Part 1-----------------------
//Return LCS length iteratively with the 2D matrix passed as a parameter
int lcs_it(int** C, string X, string Y, int m, int n) {
	for (int i = 0; i <= n; i++) {
		C[0][i] = 0;
	}
	for (int i = 0; i <= m; i++) {
		C[i][0] = 0;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X.at(i - 1) == Y.at(j - 1)) {
				C[i][j] = C[i - 1][j - 1] + 1;
			}
			else if (C[i - 1][j] > C[i][j - 1]) {
				C[i][j] = C[i - 1][j];
			}
			else {
				C[i][j] = C[i][j - 1];
			}
		}
	}
	return C[m][n];
}

//Return the LCS string recursively
string backtrack(int** C, string X, string Y, int m, int n) {
	string lcs = "";
	if (m == 0 || n == 0) {
		return "";
	}else if (X[m - 1] == Y[n - 1]) {
		return backtrack(C, X, Y, m - 1, n - 1) + X[m-1];
	} else if (C[m-1][n] > C[m][n-1]) {
		return backtrack(C, X, Y, m - 1, n);
	} else {
		return backtrack(C, X, Y, m, n - 1);
	}
}

//----------------Part 2 -----------------
//Return LCS length iteratively without 2D matrix as a parameter
int lcs_it_test(string X, string Y, int m, int n) {
	int** C = new int* [m + 1];
	for (int i = 0; i < m + 1; i++) {
		C[i] = new int[n + 1];
	}
	for (int i = 0; i <= n; i++) {
		C[0][i] = 0;
	}
	for (int i = 0; i <= m; i++) {
		C[i][0] = 0;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X.at(i - 1) == Y.at(j - 1)) {
				C[i][j] = C[i - 1][j - 1] + 1;
			}
			else if (C[i - 1][j] > C[i][j - 1]) {
				C[i][j] = C[i - 1][j];
			}
			else {
				C[i][j] = C[i][j - 1];
			}
		}
	}
	return C[m][n];
}

//Return LCS length recursively
int lcs_re(string X, string Y, int m, int n) {
	if (m == 0 || n == 0) {
		return 0;
	}
	if (X[m - 1] == Y[n - 1]) {
		return lcs_re(X, Y, m - 1, n - 1) + 1;
	}
	else {
		return max(lcs_re(X, Y, m, n - 1), lcs_re(X, Y, m - 1, n));
	}
}

//function preforms tests for both part1 and part2
int main() {
	ifstream f1;
	f1.open("input.txt");
	int start_s;
	int stop_s;
	string X;
	string Y;
	getline(f1, X);
	getline(f1, Y);
	int m = X.length();
	int n = Y.length();
  cout << "--------------Part 1----------------" << endl;
  cout << "X is: " << X << endl;
  cout << "\nY is: " << Y << endl;
	int** C = new int* [m + 1];
	for (int i = 0; i < m + 1; i++) {
		C[i] = new int[n + 1];
	}
	int len = lcs_it(C, X, Y, m, n);
  cout << "\nThe LCS string length is: " << len << endl;
	cout << "\nLCS is " << backtrack(C, X, Y, m, n) << endl;
  
  cout << "\n--------------Part 2----------------" << endl;
  int len2 = lcs_it_test(X, Y, m, n);
  cout << "\nThe LCS string length is: " << len2 << endl;

	int reclen = lcs_re(X, Y, m, n);
	cout << "The length of LCS(recursive) is: " << reclen << endl;

	int iterTrial;
	int recTrial;
	cout << "Enter trial number for iterative version: " << endl;
	cin >> iterTrial;
	
  //loop so the size can increase from 1-800 for iterative function
	for (int i = 1; i <= iterTrial; i++){
		start_s = clock();
		lcs_it(C, X, Y, i, i);
		stop_s = clock();
		clog << i << "\t" << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;
	}
	
	cout << "Enter trial number for recursive version (less than 20): " << endl;
	cin >> recTrial;

	//loop so the size can increase from 1-20 for recursive function
	for (int i = 1; i <= recTrial; i++){
		start_s = clock();
		lcs_re( X, Y, i, i);
		stop_s = clock();
		clog << i << "\t" << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;
	}
	 return 0;
}