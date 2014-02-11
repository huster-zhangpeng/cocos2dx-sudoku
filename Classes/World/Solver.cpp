/*
 * solver.cpp
 *
 *  Created on: 2013-11-30
 *      Author: zp
 */

#include "Solver.h"

static int square[9][9] = {
		{0, 0, 0, 1, 1, 1, 2, 2, 2},
		{0, 0, 0, 1, 1, 1, 2, 2, 2},
		{0, 0, 0, 1, 1, 1, 2, 2, 2},
		{3, 3, 3, 4, 4, 4, 5, 5, 5},
		{3, 3, 3, 4, 4, 4, 5, 5, 5},
		{3, 3, 3, 4, 4, 4, 5, 5, 5},
		{6, 6, 6, 7, 7, 7, 8, 8, 8},
		{6, 6, 6, 7, 7, 7, 8, 8, 8},
		{6, 6, 6, 7, 7, 7, 8, 8, 8}
};

static int rowCondition(int i, int j, int k);
static int columnCondition(int i, int j, int k);
static int squareCondition(int i, int j, int k);
static int fillCondition(int i, int j, int k);

int rowCondition(int i, int j, int k) {
	return 1 + i * 9 + k;
}

int columnCondition(int i, int j, int k) {
	return 82 + j * 9 + k;
}

int squareCondition(int i, int j, int k) {
	return 163 + square[i][j] * 9 + k;
}

int fillCondition(int i, int j, int k) {
	return 244 + i * 9 + j;
}

Solver::Solver(const char* data) : Head(0) {
	for(int i = 0; i < 81; i++){
		_data[i] = data[i];
	}
	_data[81] = 0;
	condition[0] = rowCondition;
	condition[1] = columnCondition;
	condition[2] = squareCondition;
	condition[3] = fillCondition;

	initDLX();
}

void Solver::initDLX() {
	int i, j, k, n;
	for (i = 0; i <= 324; i++) {
		L[i] = i - 1;
		R[i] = i + 1;
		U[i] = i;
		D[i] = i;
	}
	L[0] = 324;
	R[324] = 0;
	for (i = 0; i < 325; i++) {
		S[i] = 0;
		wasRemoved[i] = false;
	}

	int cur = 325;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			for (k = 0; k < 9; k++) {
				for (n = 0; n < 4; n++) {
					R[cur] = cur + 1;
					L[cur] = cur - 1;
					C[cur] = condition[n](i, j, k);
					U[cur] = U[C[cur]];
					D[cur] = C[cur];
					D[U[cur]] = cur;
					U[C[cur]] = cur;
					S[C[cur]]++;
					cur++;
				}
				R[cur - 1] = cur - 4;
				L[cur - 4] = cur - 1;
			}

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			char ch = (char) _data[i * 9 + j];
			if (ch != '.') {
				k = ch - '1';
				for (n = 0; n < 4; n++) {
					int column = condition[n](i, j, k);
					if (!wasRemoved[column]) {
						remove(column);
						wasRemoved[column] = true;
					}
				}
			}
		}
	}
}

void Solver::remove(int c) {
	L[R[c]] = L[c];
	R[L[c]] = R[c];
	for (int i = D[c]; i != c; i = D[i]) {
		for (int j = R[i]; j != i; j = R[j]) {
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			--S[C[j]];
		}
	}
}

void Solver::resume(int c) {
	for (int i = U[c]; i != c; i = U[i]) {
		for (int j = L[i]; j != i; j = L[j]) {
			++S[C[j]];
			D[U[j]] = j;
			U[D[j]] = j;
		}
	}
	R[L[c]] = c;
	L[R[c]] = c;
}

bool Solver::dfs(int k) {
	if (k > 325)
		return true;
	int s = 800, c = 0;
	for (int t = R[Head]; t != Head; t = R[t]) {
		if (S[t] < s) {
			s = S[t];
			c = t;
		}
	}
	if (c == 0)
		return true;
	remove(c);
	for (int i = D[c]; i != c; i = D[i]) {
		int t = (i - 325) / 4;
		_data[t / 9] = (char) (t % 9 + '1');
		for (int j = R[i]; j != i; j = R[j]) {
			remove(C[j]);
		}
		if (dfs(k + 1))
			return true;
		for (int j = L[i]; j != i; j = L[j]) {
			resume(C[j]);
		}
	}
	resume(c);
	return false;
}

char* Solver::getResult(){
	dfs(0);
	return _data;
}

