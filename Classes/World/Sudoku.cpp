/*
 * Sudoku.cpp
 *
 *  Created on: 2013-11-30
 *      Author: zp
 */

#include "Sudoku.h"
#include "Solver.h"
#include "Puzzels.h"

State Sudoku::state = Running;
bool Sudoku::hasLoaded = false;
bool Sudoku::hasChecked = false;
bool Sudoku::hasFinished = false;

char Sudoku::orinal[9][9];
char Sudoku::result[9][9];
char Sudoku::puzzel[9][9];
bool Sudoku::conflict[9][9];
SudokuNote Sudoku::notes[9][9];
char Sudoku::remain[9] = {0};

int Sudoku::level = 0;
int Sudoku::id = 0;
int Sudoku::remainBlanks = 0;
float Sudoku::usedTimeSec = 0;
int Sudoku::mistakes = 0;
Position Sudoku::position = Position();

void Sudoku::load(int level, const char* & oridata, const char* & puzzeldata) {
	Sudoku::level = level;

	int i, j, k;
	memset(remain, 9, sizeof(remain));
	memset(conflict, false, sizeof(conflict));

	remainBlanks = 81;
	Solver solver(oridata);
	char * ansStr = solver.getResult();
	k = 0;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++) {
			puzzel[i][j] = puzzeldata[k];
			if (puzzel[i][j] != '.') {
				remain[puzzel[i][j] - '1']--;
				remainBlanks--;
			}
			Sudoku::orinal[i][j] = oridata[k];
			result[i][j] = ansStr[k++];
		}

	usedTimeSec = 0.0f;
	mistakes = 0;

	Sudoku::state = Running;
	hasLoaded = true;
	hasFinished = false;
	hasChecked = false;
}

void Sudoku::restart(){
	load(level, puzzels[level][id], puzzels[level][id]);
}

bool Sudoku::isRight(char ch){
	return ch == result[position.x][position.y];
}

bool Sudoku::isOrinal() {
		return orinal[position.x][position.y] != '.';
	}

void Sudoku::setResult(int x, int y, int res){
	puzzel[x][y] = (char)(res + '1');
	remain[ res ]--;
	remainBlanks --;
}

int Sudoku::getResult(){
	return result[position.x][position.y] - '0';
}

int Sudoku::getResult(int x, int y){
	return result[x][y] - '0';
}

void Sudoku::setCurrentPos(int x, int y){
	position.x = x;
	position.y = y;
}

bool Sudoku::isCurPosFilled(){
	return puzzel[position.x][position.y] != '.';
}

bool Sudoku::isFinished(){
	return remainBlanks == 0;
}

bool Sudoku::isReallyFinished(){
	int i, j;
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			if(puzzel[i][j] != result[i][j])
				return false;
	return true;
}

bool Sudoku::isRowFinished(int row){
	for(int y = 0; y < 9; y++)
		if(puzzel[row][y] == '.')
			return false;
	return true;
}

bool Sudoku::isColumnFinished(int column){
	for(int i = 0; i < 9; i++)
		if(puzzel[i][column] == '.')
			return false;
	return true;
}

bool Sudoku::isSquareFinished(int row, int column){
	int sx = row / 3 * 3;
	int sy = column / 3 * 3;
	for(int i = sx; i < sx + 3; i++)
		for(int j = sy; j < sy + 3; j++)
			if(puzzel[i][j] == '.')
				return false;
	return true;
}

void Sudoku::updateConflictAfterFill(int x, int y, char res){
	int i, j;
	for(i = 0; i < 9; i++) {
		if(i != y && puzzel[x][i] == res){
			conflict[x][i] = conflict[x][y] = true;
		}

		if(i != x && puzzel[i][y] == res){
			conflict[i][y] = conflict[x][y] = true;
		}
	}

	int sx = x / 3 * 3;
	int sy = y / 3 * 3;
	for(i = sx; i < sx + 3; i++)
		for(j = sy; j < sy + 3; j++)
			if((i != x || j != y) && puzzel[i][j] == res){
				conflict[i][j] = conflict[x][y] = true;
			}
}

void Sudoku::updateConflictAfterClean(int x, int y, int res){
	int i, j;
	conflict[x][y] = false;
	for(i = 0; i < 9; i++){
		if(i != y && puzzel[x][i] == res){
			conflict[x][i] = hasConflict(x, i);
		}
		if(i != x && puzzel[i][y] == res){
			conflict[i][y] = hasConflict(i, y);
		}
	}

	int sx = x / 3 * 3;
	int sy = y / 3 * 3;
	for(i = sx; i < sx + 3; i++)
		for(j = sy; j < sy + 3; j++)
			if((i != x || j != y) && puzzel[i][j] == res) {
				conflict[i][j] = hasConflict(i, j);
			}
}

int Sudoku::getCurHint(){
	return result[position.x][position.y] - '1';
}

bool Sudoku::hasConflict(int x, int y){
	char ch = puzzel[x][y];
	int m, n;
	for(m = 0; m < 9; m++){
		if(m != y && puzzel[x][m] == ch){
			return true;
		}
		if(m != x && puzzel[m][y] == ch){
			return true;
		}
	}

	int sx = x / 3 * 3;
	int sy = y / 3 * 3;
	for(m = sx; m < sx + 3; m++)
		for(n = sy; n < sy + 3; n++){
			if((m != x || n != y) && puzzel[m][n] == ch){
				return true;
			}
		}
	return false;
}

void Sudoku::erase(){
	erase(position.x, position.y);
}

void Sudoku::erase(int x, int y){
	char ch = puzzel[x][y];
	if(ch == '.')
		return;
	remain[ ch - '1' ] ++;
	puzzel[x][y] = '.';
	remainBlanks ++;
	updateConflictAfterClean(x, y, ch);
	hasChecked = false;
	hasFinished = false;
}
