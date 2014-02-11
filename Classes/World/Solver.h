/*
 * Solver.h
 *
 *  Created on: 2013-11-30
 *      Author: zp
 */

#ifndef SOLVER_H_
#define SOLVER_H_

class Solver {
private:
	char _data[82];

	int L[3241];
	int R[3241];
	int U[3241];
	int D[3241];
	int C[3241];
	int S[3241];
	int Head;
	bool wasRemoved[325];

	int (*condition[4])(int i, int j, int k);

	void initDLX();
	void remove(int c);
	void resume(int c);
	bool dfs(int k);

public:

	Solver(const char* data);
	char* getResult();
};

#endif /* SOLVER_H_ */
