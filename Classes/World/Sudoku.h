/*
 * Sudoku.h
 *
 *  Created on: 2013-11-30
 *      Author: zp
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include "cocos2d.h"
//#include "Note.h"

USING_NS_CC;

enum State {
	Running,
	Note
};

struct Position{
	int x, y;
};

class SudokuNote {
private:

	short _data;

public:

	SudokuNote();
	void add(int n);
	void clear(int n);
	void toggle(int n);
	void erase();
	bool isEmpty();
	bool has(int n);
	int total();

};


class Sudoku {
public:
	static State state;
	static bool hasLoaded;
	static bool hasChecked;
	static bool hasFinished;

	static char orinal[9][9];
	static char result[9][9];
	static char puzzel[9][9];
	static bool conflict[9][9];
	static SudokuNote notes[9][9];
	static char remain[9];

	static int level;
	static int id;
	static int remainBlanks;
	static float usedTimeSec;
	static int mistakes;
	static Position position;

	static void load(int level, const char* & oridata,  const char* & puzzeldata);
	static void restart();
	static bool isRight(char ch);
	static bool isOrinal();
	static void setResult(int x, int y, int res);
	static int getResult();
	static int getResult(int x, int y);
	static void setCurrentPos(int x, int y);
	static bool isCurPosFilled();
	static bool isFinished();
	static bool isReallyFinished();
	static void updateConflictAfterFill(int x, int y, char res);
	static void updateConflictAfterClean(int x, int y, int res);

	static void erase();
	static void erase(int x, int y);
	static int getCurHint();

	static bool isRowFinished(int row);
	static bool isColumnFinished(int column);
	static bool isSquareFinished(int row, int column);

private:

	static bool hasConflict(int x, int y);

};


#endif /* SUDOKU_H_ */
