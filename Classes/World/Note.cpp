/*
 * Note.cpp
 *
 *  Created on: 2013-12-5
 *      Author: zp
 */

#include <iso646.h>
#include "Sudoku.h"

static int MASKS[] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};

SudokuNote::SudokuNote() : _data(0) {}

void SudokuNote::add(int n) {
	_data = _data | MASKS[n];
}

void SudokuNote::clear(int n) {
	_data = _data & (~MASKS[n]);
}

void SudokuNote::toggle(int n) {
	_data = _data ^ MASKS[n];
	CCLog("note: %x", _data);
}

void SudokuNote::erase() {
	_data = 0;
}

bool SudokuNote::isEmpty() {
	return !_data;
}

bool SudokuNote::has(int n) {
	return _data & MASKS[n];
}

int SudokuNote::total() {
	int sum = 0;
	for(int i = 1; i <=9; i++) {
		if(_data & MASKS[i]) {
			sum ++;
		}
	}
	return sum;
}
